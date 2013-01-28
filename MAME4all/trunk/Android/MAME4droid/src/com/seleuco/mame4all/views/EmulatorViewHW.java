/*
 * This file is part of MAME4droid.
 *
 * Copyright (C) 2011-2013 David Valdeita (Seleuco)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses>.
 *
 * Linking MAME4droid statically or dynamically with other modules is
 * making a combined work based on MAME4droid. Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * In addition, as a special exception, the copyright holders of MAME4droid
 * give you permission to combine MAME4droid with free software programs
 * or libraries that are released under the GNU LGPL and with code included
 * in the standard release of MAME under the MAME License (or modified
 * versions of such code, with unchanged license). You may copy and
 * distribute such a system following the terms of the GNU GPL for MAME4droid
 * and the licenses of the other code concerned, provided that you include
 * the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of MAME4droid are not
 * obligated to grant this special exception for their modified versions; it
 * is their choice whether to do so. The GNU General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 *
 * MAME4droid is dual-licensed: Alternatively, you can license MAME4droid
 * under a MAME license, as set out in http://mamedev.org/
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
