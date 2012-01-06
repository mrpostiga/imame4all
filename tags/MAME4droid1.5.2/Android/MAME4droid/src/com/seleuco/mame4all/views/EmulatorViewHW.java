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

import java.util.ArrayList;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

import com.seleuco.mame4all.Emulator;
import com.seleuco.mame4all.MAME4all;
import com.seleuco.mame4all.helpers.PrefsHelper;


public class EmulatorViewHW extends View implements IEmuView{
	
	
	protected int scaleType = PrefsHelper.PREF_ORIGINAL;
	
	protected MAME4all mm = null;
	
	protected int i = 0;
	protected int fps = 0;
	protected long millis;

	public int getScaleType() {
		return scaleType;
	}

	public void setScaleType(int scaleType) {
		this.scaleType = scaleType;
	}

	public void setMAME4all(MAME4all mm) {
		this.mm = mm;
	}
	
	public EmulatorViewHW(Context context) {
		super(context);
		init();
	}

	public EmulatorViewHW(Context context, AttributeSet attrs) {
		super(context, attrs);
		init();
	}

	public EmulatorViewHW(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		init();
	}
	
	protected void init(){
		this.setKeepScreenOn(true);
		this.setFocusable(true);
		this.setFocusableInTouchMode(true);
		this.requestFocus();
	}
		
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
		ArrayList<Integer> l = mm.getMainHelper().measureWindow(widthMeasureSpec, heightMeasureSpec, scaleType);
		setMeasuredDimension(l.get(0).intValue(),l.get(1).intValue());
	}
		
	@Override
	protected void onSizeChanged(int w, int h, int oldw, int oldh) {

		super.onSizeChanged(w, h, oldw, oldh);
		Emulator.setWindowSize(w, h);
	}
	
	@Override
	public boolean onTrackballEvent(MotionEvent event) {
		return mm.getInputHandler().onTrackballEvent(event);
	}
	
	@Override
	public void draw(Canvas canvas) {
		super.draw(canvas);
		i++;

		if(Emulator.getScreenBuffer()==null)
			return;

		canvas.concat(Emulator.getMatrix());
        
		/*
		Emulator.getScreenBuffer().rewind();			
		Emulator.getEmuBitmap().copyPixelsFromBuffer(Emulator.getScreenBuffer());
			
		Emulator.getEmuBitmap().getPixels(px, 0, Emulator.getEmulatedWidth(), 0, 0, Emulator.getEmulatedWidth(), Emulator.getEmulatedHeight());
		*/

		canvas.drawBitmap(Emulator.getScreenBuffPx(), 0, Emulator.getEmulatedWidth(), 0, 0,Emulator.getEmulatedWidth(), Emulator.getEmulatedHeight(), false, null);
		
					
		//canvas.drawBitmap(Emulator.getEmuBitmap(), 0, 0, Emulator.getEmuPaint());
			
		if(Emulator.isDebug())
		{
		    canvas.drawText("HW "+canvas.isHardwareAccelerated()+" fps:"+fps, 5, 40, Emulator.getDebugPaint());		  
		    if(System.currentTimeMillis() - millis >= 1000) {fps = i; i=0;millis = System.currentTimeMillis();} 		
		}	
	}
}
