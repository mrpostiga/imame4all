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
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.MotionEvent;

import com.seleuco.mame4all.Emulator;
import com.seleuco.mame4all.GLRenderer;
import com.seleuco.mame4all.MAME4all;
import com.seleuco.mame4all.helpers.PrefsHelper;


public class EmulatorViewGL extends GLSurfaceView implements IEmuView{
	
	protected int scaleType = PrefsHelper.PREF_ORIGINAL;
		
	protected MAME4all mm = null;
	
	protected GLRenderer render = null;

	public Renderer getRender() {
		return render;
	}

	public int getScaleType() {
		return scaleType;
	}

	public void setScaleType(int scaleType) {
		this.scaleType = scaleType;
	}

	public void setMAME4all(MAME4all mm) {
		this.mm = mm;
		render.setMAME4all(mm);
	}
	
	public EmulatorViewGL(Context context) {
		super(context);
		init();
	}

	public EmulatorViewGL(Context context, AttributeSet attrs) {
		super(context, attrs);
		init();
	}
	
	protected void init(){
		this.setKeepScreenOn(true);
		this.setFocusable(true);
		this.setFocusableInTouchMode(true);
		this.requestFocus();
		render = new GLRenderer();
		//setDebugFlags(DEBUG_CHECK_GL_ERROR | DEBUG_LOG_GL_CALLS);
		setRenderer(render);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
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

}
