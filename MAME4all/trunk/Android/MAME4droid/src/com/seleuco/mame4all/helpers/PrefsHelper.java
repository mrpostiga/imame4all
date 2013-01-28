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

package com.seleuco.mame4all.helpers;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.preference.PreferenceManager;

import com.seleuco.mame4all.MAME4all;
import com.seleuco.mame4all.input.InputHandler;

public class PrefsHelper implements OnSharedPreferenceChangeListener
{
	final static public String PREF_ROMsDIR = "PREF_ROMsDIR";
	
	final static public String PREF_GLOBAL_ASMCORES = "PREF_GLOBAL_ASMCORES";
	final static public String PREF_GLOBAL_VIDEO_RENDER_MODE = "PREF_GLOBAL_VIDEO_RENDER_MODE";
	final static public String PREF_GLOBAL_SOUND_THREADED = "PREF_GLOBAL_SOUND_THREADED";
	final static public String PREF_GLOBAL_SHOW_FPS = "PREF_GLOBAL_SHOW_FPS";
	final static public String PREF_GLOBAL_SHOW_INFOWARNINGS = "PREF_GLOBAL_SHOW_INFOWARNINGS";	
	final static public String PREF_GLOBAL_DEBUG = "PREF_GLOBAL_DEBUG";
	final static public String PREF_GLOBAL_IDLE_WAIT = "PREF_GLOBAL_IDLE_WAIT"; 
		
	final static public String PREF_PORTRAIT_SCALING_MODE = "PREF_PORTRAIT_SCALING_MODE_2";
	final static public String PREF_PORTRAIT_FILTER_TYPE = "PREF_PORTRAIT_FILTER_2";
	final static public String PREF_PORTRAIT_TOUCH_CONTROLLER = "PREF_PORTRAIT_TOUCH_CONTROLLER";
	final static public String PREF_PORTRAIT_BITMAP_FILTERING = "PREF_PORTRAIT_BITMAP_FILTERING";
	
	final static public String PREF_LANDSCAPE_SCALING_MODE = "PREF_LANDSCAPE_SCALING_MODE_2";
	final static public String PREF_LANDSCAPE_FILTER_TYPE = "PREF_LANDSCAPE_FILTER_2";
	final static public String PREF_LANDSCAPE_TOUCH_CONTROLLER = "PREF_LANDSCAPE_TOUCH_CONTROLLER";
	final static public String PREF_LANDSCAPE_BITMAP_FILTERING = "PREF_LANDSCAPE_BITMAP_FILTERING";
	final static public String PREF_LANDSCAPE_CONTROLLER_TYPE = "PREF_LANDSCAPE_CONTROLLER_TYPE";
		
	final static public String  PREF_DEFINED_KEYS = "PREF_DEFINED_KEYS";
	
	final static public String  PREF_DEFINED_CONTROL_LAYOUT = "PREF_DEFINED_CONTROL_LAYOUT";
	
	final static public String  PREF_TRACKBALL_SENSITIVITY = "PREF_TRACKBALL_SENSITIVITY";
	final static public String  PREF_TRACKBALL_NOMOVE = "PREF_TRACKBALL_NOMOVE";
	final static public String  PREF_ANIMATED_INPUT = "PREF_ANIMATED_INPUT";
	final static public String  PREF_TOUCH_DZ = "PREF_TOUCH_DZ";
	final static public String  PREF_CONTROLLER_TYPE = "PREF_CONTROLLER_TYPE";
	final static public String  PREF_INPUT_EXTERNAL = "PREF_INPUT_EXTERNAL";
	final static public String  PREF_ANALOG_DZ = "PREF_ANALOG_DZ";
	final static public String  PREF_VIBRATE = "PREF_VIBRATE";
	
	final static public String  PREF_TILT_SENSOR = "PREF_TILT_SENSOR";
	final static public String  PREF_TILT_DZ = "PREF_TILT_DZ";
	final static public String  PREF_TILT_SENSITIVITY = "PREF_TILT_SENSITIVITY";
	
	final static public int  PREF_RENDER_NORMAL = 1;
	final static public int  PREF_RENDER_THREADED = 2;
	final static public int  PREF_RENDER_GL = 3;	
	final static public int  PREF_RENDER_HW = 4;
	
	final static public int  PREF_DIGITAL = 1;
	final static public int  PREF_ANALOG_FAST = 2;
	final static public int  PREF_ANALOG_PRETTY = 3;

	final static public int  PREF_INPUT_DEFAULT = 1;
	final static public int  PREF_INPUT_ICADE = 2;
	final static public int  PREF_INPUT_ICP = 3;
	
	final public static int PREF_ORIGINAL = 1;
	final public static int PREF_15X = 2;	
	final public static int PREF_20X = 3;
	final public static int PREF_25X = 4;	
	final public static int PREF_SCALE = 5;
	final public static int PREF_STRETCH = 6;

	final public static int PREF_FILTER_NONE = 1;
	final public static int PREF_FILTER_SCANLINE_1 = 2;	
	final public static int PREF_FILTER_SCANLINE_2 = 3;
	final public static int PREF_CRT_1 = 4;	
	final public static int PREF_CRT_2 = 5;
	
	protected MAME4all mm = null;
	
	public PrefsHelper(MAME4all value){
		mm = value;
	}

	public void onSharedPreferenceChanged(SharedPreferences sharedPreferences,
			String key) {
	}
	
	public void resume() {
		Context context = mm.getApplicationContext();
		SharedPreferences prefs =
			  PreferenceManager.getDefaultSharedPreferences(context);
			prefs.registerOnSharedPreferenceChangeListener(this);
	}	

	public void pause() {

		Context context = mm.getApplicationContext();
		SharedPreferences prefs =
			  PreferenceManager.getDefaultSharedPreferences(context);
			prefs.unregisterOnSharedPreferenceChangeListener(this);
	}
	
	protected SharedPreferences getSharedPreferences(){
		Context context = mm.getApplicationContext();
		return PreferenceManager.getDefaultSharedPreferences(context);
	}

	public int getPortraitScaleMode(){
		return Integer.valueOf(getSharedPreferences().getString(PREF_PORTRAIT_SCALING_MODE,"5")).intValue();	
	}
	
	public int getLandscapeScaleMode(){
		return Integer.valueOf(getSharedPreferences().getString(PREF_LANDSCAPE_SCALING_MODE,"5")).intValue();	
	}

	public int getPortraitOverlayFilterType(){
		return Integer.valueOf(getSharedPreferences().getString(PREF_PORTRAIT_FILTER_TYPE,"1")).intValue();	
	}
	
	public int getLandscapeOverlayFilterType(){
		return Integer.valueOf(getSharedPreferences().getString(PREF_LANDSCAPE_FILTER_TYPE,"1")).intValue();	
	}	
	
	public boolean isPortraitTouchController(){
		return getSharedPreferences().getBoolean(PREF_PORTRAIT_TOUCH_CONTROLLER,true);
	}
		
	public boolean isPortraitBitmapFiltering(){
		return getSharedPreferences().getBoolean(PREF_PORTRAIT_BITMAP_FILTERING,false);
	}	

	public boolean isLandscapeTouchController(){
		return getSharedPreferences().getBoolean(PREF_LANDSCAPE_TOUCH_CONTROLLER,true);
	}
		
	public boolean isLandscapeBitmapFiltering(){
		return getSharedPreferences().getBoolean(PREF_LANDSCAPE_BITMAP_FILTERING,false);
	}
	
	public String getDefinedKeys(){
		
		SharedPreferences p = getSharedPreferences();
		
		StringBuffer defaultKeys = new StringBuffer(); 
		
		for(int i=0; i< InputHandler.defaultKeyMapping.length;i++)
			defaultKeys.append(InputHandler.defaultKeyMapping[i]+":");
			
		return p.getString(PREF_DEFINED_KEYS, defaultKeys.toString());
		
	}
	
	public int getTrackballSensitivity(){
		//return Integer.valueOf(getSharedPreferences().getString(PREF_TRACKBALL_SENSITIVITY,"3")).intValue();	
		return getSharedPreferences().getInt(PREF_TRACKBALL_SENSITIVITY,3);
	}
	
	public boolean isTrackballNoMove(){
		return getSharedPreferences().getBoolean(PREF_TRACKBALL_NOMOVE,false);
	}

	public int getVideoRenderMode(){
		return Integer.valueOf(getSharedPreferences().getString(PREF_GLOBAL_VIDEO_RENDER_MODE,"2")).intValue();	
	}
	
	public boolean isSoundfThreaded(){
		return getSharedPreferences().getBoolean(PREF_GLOBAL_SOUND_THREADED,true);
	}

	public boolean isFPSShowed(){
		return getSharedPreferences().getBoolean(PREF_GLOBAL_SHOW_FPS,false);
	}
	
	public boolean isDebugEnabled(){
		return getSharedPreferences().getBoolean(PREF_GLOBAL_DEBUG,false);
	}

	public boolean isIdleWait(){
		return getSharedPreferences().getBoolean(PREF_GLOBAL_IDLE_WAIT,true);
	}
	
	public boolean isAnimatedInput(){
		return getSharedPreferences().getBoolean(PREF_ANIMATED_INPUT,true);
	}
	
	public boolean isTouchDZ(){
		return getSharedPreferences().getBoolean(PREF_TOUCH_DZ,true);
	}
	
	public boolean isASMCores(){
		return getSharedPreferences().getBoolean(PREF_GLOBAL_ASMCORES,true);
	}
	
	public boolean isShowInfoWarnings(){
		return getSharedPreferences().getBoolean(PREF_GLOBAL_SHOW_INFOWARNINGS,true);
	}
	
	public int getControllerType(){
		return Integer.valueOf(getSharedPreferences().getString(PREF_CONTROLLER_TYPE,"2")).intValue();	
	}
	
	public int getInputExternal(){
		return Integer.valueOf(getSharedPreferences().getString(PREF_INPUT_EXTERNAL,"1")).intValue();	
	}
	
	public int getAnalogDZ(){
		return Integer.valueOf(getSharedPreferences().getString(PREF_ANALOG_DZ,"1")).intValue();	
	}
	
	public boolean isVibrate(){
		return getSharedPreferences().getBoolean(PREF_VIBRATE,true);
	}
	
	public String getROMsDIR(){
		return getSharedPreferences().getString(PREF_ROMsDIR,null);
	}
	
	public void setROMsDIR(String value){
		//PreferenceManager.getDefaultSharedPreferences(this);
		SharedPreferences.Editor editor =  getSharedPreferences().edit();
		editor.putString(PREF_ROMsDIR, value);
		editor.commit();
	}
	
	public String getDefinedControlLayout(){
		return getSharedPreferences().getString(PREF_DEFINED_CONTROL_LAYOUT,null);
	}
	
	public void setDefinedControlLayout(String value){
		SharedPreferences.Editor editor =  getSharedPreferences().edit();
		editor.putString(PREF_DEFINED_CONTROL_LAYOUT, value);
		editor.commit();
	}
	
	public boolean isTiltSensor(){
		return getSharedPreferences().getBoolean(PREF_TILT_SENSOR,false);
	}
	
	public int getTiltSensitivity(){	
		return getSharedPreferences().getInt(PREF_TILT_SENSITIVITY,6);
	}
	
	public int getTiltDZ(){
		return Integer.valueOf(getSharedPreferences().getString(PREF_TILT_DZ,"3")).intValue();	
	}		
	
}
