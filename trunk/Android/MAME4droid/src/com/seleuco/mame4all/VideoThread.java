/*
 * This file is part of MAME4droid.
 *
 * Copyright (C) 2011 David Valdeita (Seleuco)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * In addition, as a special exception, Seleuco
 * gives permission to link the code of this program with
 * the MAME library (or with modified versions of MAME that use the
 * same license as MAME), and distribute linked combinations including
 * the two.  You must obey the GNU General Public License in all
 * respects for all of the code used other than MAME.  If you modify
 * this file, you may extend this exception to your version of the
 * file, but you are not obligated to do so.  If you do not wish to
 * do so, delete this exception statement from your version.
 */

package com.seleuco.mame4all;


import java.nio.ByteBuffer;

import com.seleuco.mame4all.helpers.PrefsHelper;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.util.Log;

public class VideoThread implements Runnable {

	protected Thread thread = null;
	protected int i = 0;
	protected int fps = 0;
	protected long millis;
	protected Canvas canvas = null;
	protected boolean run = false;
    protected MAME4all mm = null;
    
	public void setMAME4all(MAME4all mm) {
		this.mm = mm;		
	}

	public VideoThread() {		
	}
	
	public void start(){
	   if(run) stop();
	   run = true;   		   
	   if(thread==null)
	   {
		   //Log.d("Thread Video", "Nueva Thread");
		   thread = new Thread(this, "video-Thread");
		   //thread.setPriority(Thread.MAX_PRIORITY);
	   }	
	   ////Log.d("Thread Video", "Start Nueva Thread");
	   thread.start();
	}
	
	public void stop(){
		if(run)
		{
			run = false;
			synchronized(this){
			    this.notify();
			}
		
			try {
				//Log.d("Thread Video", "Antes join");
				thread.join();
				//Log.d("Thread Video", "Despues join");
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			thread = null;

			//Log.d("Thread Video", "thread "+thread);
		}		
	}
	
	@Override
	public void run() {

		while (run) 
		{	
			//Log.d("Thread Video", "running "+run);
			
			try{
				synchronized(this)
				{			
					try {		
						//Log.d("Thread Video", "Espero "+run);
						if(!run)break;
						wait();
						//Log.d("Thread Video", "Me despierto "+run);
						if(!run)break;
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
				
				//Log.d("Thread Video", "Recupero "+run);
				
				ByteBuffer bf = Emulator.getScreenBuffer();
				Bitmap bmp = Emulator.getEmuBitmap();				
				
				//Log.d("Thread Video", "salgo Recupero "+bf+" "+bmp);
				
				if(bf==null || bmp ==null)
					continue;
		        		
				if(Emulator.getVideoRenderMode() == PrefsHelper.PREF_RENDER_HW)
				{	
					bf.rewind();			
					bmp.copyPixelsFromBuffer(bf);						
					
					bmp.getPixels(Emulator.getScreenBuffPx(), 0, Emulator.getEmulatedWidth(), 0, 0, Emulator.getEmulatedWidth(), Emulator.getEmulatedHeight());
					
					mm.getEmuView().postInvalidate();
				}
				else
				{					
					//Log.d("Thread Video", "Lock "+run);
					canvas = Emulator.lockCanvas();
									
					if(canvas==null)
					   continue;
									
					bf.rewind();			
					bmp.copyPixelsFromBuffer(bf);
					i++;
					//canvas.drawBitmap(emuBitmap, null, frameRect, Emulator.getFramePaint());
					canvas.concat(Emulator.getMatrix());			
					canvas.drawBitmap(bmp, 0, 0, Emulator.getEmuPaint());
														
					if(Emulator.isDebug())
					{
					   canvas.drawText("Threaded fps:"+fps+ " w:"+Emulator.getWindow_width()+" h:"+Emulator.getWindow_height(), 5,  40, Emulator.getDebugPaint());			  
					   if(System.currentTimeMillis() - millis >= 1000) {fps = i; i=0;millis = System.currentTimeMillis();} 
					}
					
					//Log.d("Thread Video", "UnLock "+run);
					Emulator.unlockCanvas(canvas);
					//Log.d("Thread Video", "FIN UnLock "+run);
				}							
			}
			catch(Exception t)
			{				
				//Log.d("Thread Video", "FIN UnLock "+run,t);
				Log.getStackTraceString(t);
			}
			
			
		}
		//Log.d("Thread Video", "FIN THREAD "+run);
	}
	
	synchronized public void update() {
		//Log.d("Thread Video", "Hago update");
		this.notify();
	}

}
