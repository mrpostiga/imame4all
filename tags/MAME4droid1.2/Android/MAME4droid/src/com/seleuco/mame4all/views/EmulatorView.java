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

package com.seleuco.mame4all.views;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.SurfaceHolder.Callback;

import com.seleuco.mame4all.Emulator;
import com.seleuco.mame4all.MAME4all;
import com.seleuco.mame4all.helpers.PrefsHelper;


public class EmulatorView extends SurfaceView implements Callback{
	

	protected int scaleType = PrefsHelper.PREF_ORIGINAL;
	
	protected MAME4all mm = null;

	public int getScaleType() {
		return scaleType;
	}

	public void setScaleType(int scaleType) {
		this.scaleType = scaleType;
	}

	public void setMAME4all(MAME4all mm) {
		this.mm = mm;
	}
	
	public EmulatorView(Context context) {
		super(context);
		init();
	}

	public EmulatorView(Context context, AttributeSet attrs) {
		super(context, attrs);
		init();
	}

	public EmulatorView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		init();

	}
	
	protected void init(){
		this.getHolder().addCallback(this);		
		this.setFocusable(true);
		this.setFocusableInTouchMode(true);
		this.requestFocus();
	}
		
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
   
		int widthSize = 1;
		int heightSize = 1;
		
	
		if (scaleType == PrefsHelper.PREF_STRETCH)// FILL ALL
		{
			widthSize = MeasureSpec.getSize(widthMeasureSpec);
			heightSize = MeasureSpec.getSize(heightMeasureSpec);
		} else {
			
			int emu_w = Emulator.getEmulatedWidth();
		    int emu_h = Emulator.getEmulatedHeight();
		    
		    
		    if(scaleType == PrefsHelper.PREF_15X)
		    {
		    	emu_w = (int)(emu_w * 1.5f);
		    	emu_h = (int)(emu_h * 1.5f);
		    }
		    
		    if(scaleType == PrefsHelper.PREF_20X)
		    {
		    	emu_w = emu_w * 2;
		    	emu_h = emu_h * 2;
		    }
		    
		    if(scaleType == PrefsHelper.PREF_25X)
		    {
		    	emu_w = (int)(emu_w * 2.5f);
		    	emu_h = (int)(emu_h * 2.5f);
		    }
		    
			int w = emu_w;
			int h = emu_h;

			widthSize = MeasureSpec.getSize(widthMeasureSpec);
			heightSize = MeasureSpec.getSize(heightMeasureSpec);
						
			if(heightSize==0)heightSize=1;
			if(widthSize==0)widthSize=1;

			float scale = 1.0f;

			if (scaleType == PrefsHelper.PREF_SCALE)
				scale = Math.min((float) widthSize / (float) w,
						(float) heightSize / (float) h);

			w = (int) (w * scale);
			h = (int) (h * scale);

			float desiredAspect = (float) emu_w / (float) emu_h;

			widthSize = Math.min(w, widthSize);
			heightSize = Math.min(h, heightSize);

			float actualAspect = (float) (widthSize / heightSize);

			if (Math.abs(actualAspect - desiredAspect) > 0.0000001) {

				boolean done = false;

				// Try adjusting emu_width to be proportional to emu_height
				int newWidth = (int) (desiredAspect * heightSize);

				if (newWidth <= widthSize) {
					widthSize = newWidth;
					done = true;
				}

				// Try adjusting emu_height to be proportional to emu_width
				if (!done) {
					int newHeight = (int) (widthSize / desiredAspect);
					if (newHeight <= heightSize) {
						heightSize = newHeight;
					}
				}
			}
		}

		setMeasuredDimension(widthSize, heightSize);
	}
		
	@Override
	protected void onSizeChanged(int w, int h, int oldw, int oldh) {

		super.onSizeChanged(w, h, oldw, oldh);
		Emulator.setWindowSize(w, h);		
	}

	//@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		//Emulator.setHolder(holder);		
	}

	//@Override
	public void surfaceCreated(SurfaceHolder holder) {
		//Thread.currentThread().setPriority(Thread.MAX_PRIORITY);
		Emulator.setHolder(holder);		
	}

	//@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		Emulator.setHolder(null);		
	}
	
	@Override
	public boolean onTrackballEvent(MotionEvent event) {
		return mm.getInputHandler().onTrackballEvent(event);
	}

}
