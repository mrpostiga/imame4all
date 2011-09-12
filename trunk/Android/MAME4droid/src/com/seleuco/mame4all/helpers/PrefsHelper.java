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

package com.seleuco.mame4all.helpers;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.preference.PreferenceManager;

import com.seleuco.mame4all.MAME4all;
import com.seleuco.mame4all.input.InputHandler;

public class PrefsHelper implements OnSharedPreferenceChangeListener
{
	
	final static public String PREF_GLOBAL_VIDEO_RENDER_MODE = "PREF_GLOBAL_VIDEO_RENDER_MODE";
	final static public String PREF_GLOBAL_SOUND_THREADED = "PREF_GLOBAL_SOUND_THREADED";
	final static public String PREF_GLOBAL_SHOW_FPS = "PREF_GLOBAL_SHOW_FPS";
	final static public String PREF_GLOBAL_FPS_LIMIT = "PREF_GLOBAL_FPS_LIMIT";
	final static public String PREF_GLOBAL_DEBUG = "PREF_GLOBAL_DEBUG";
	
	final static public String PREF_PORTRAIT_SCALING_MODE = "PREF_PORTRAIT_SCALING_MODE";
	final static public String PREF_PORTRAIT_TOUCH_CONTROLLER = "PREF_PORTRAIT_TOUCH_CONTROLLER";
	final static public String PREF_PORTRAIT_BITMAP_FILTERING = "PREF_PORTRAIT_BITMAP_FILTERING";
	
	final static public String PREF_LANDSCAPE_SCALING_MODE = "PREF_LANDSCAPE_SCALING_MODE";
	final static public String PREF_LANDSCAPE_TOUCH_CONTROLLER = "PREF_LANDSCAPE_TOUCH_CONTROLLER";
	final static public String PREF_LANDSCAPE_BITMAP_FILTERING = "PREF_LANDSCAPE_BITMAP_FILTERING";
	final static public String PREF_LANDSCAPE_CONTROLLER_TYPE = "PREF_LANDSCAPE_CONTROLLER_TYPE";
		
	final static public String  PREF_DEFINED_KEYS = "PREF_DEFINED_KEYS";
	
	final static public String  PREF_TRACKBALL_SENSITIVITY = "PREF_TRACKBALL_SENSITIVITY";
	final static public String  PREF_TRACKBALL_NOMOVE = "PREF_TRACKBALL_NOMOVE";
	final static public String  PREF_ANIMATED_INPUT = "PREF_ANIMATED_INPUT";
	final static public String  PREF_TOUCH_DZ = "PREF_TOUCH_DZ";
	
	final static public int  PREF_RENDER_NORMAL = 1;
	final static public int  PREF_RENDER_THREADED = 2;
	final static public int  PREF_RENDER_HW = 3;
	
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
		return Integer.valueOf(getSharedPreferences().getString(PREF_PORTRAIT_SCALING_MODE,"3")).intValue();	
	}
	
	public int getLandscapeScaleMode(){
		return Integer.valueOf(getSharedPreferences().getString(PREF_LANDSCAPE_SCALING_MODE,"3")).intValue();	
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
	
	public int getLandscapeControllerType(){
		/*
		return Integer.valueOf(getSharedPreferences().getString(PREF_LANDSCAPE_CONTROLLER_TYPE,"1")).intValue();
		*/
		return 2;
	}

	/*
	public boolean isPortraitCropX(){
		//HVGA 480x320 -> No crop
		Display d = mm.getWindowManager().getDefaultDisplay();
		boolean def = true;
		if((d.getHeight()==480 && d.getWidth()==320) || (d.getHeight()==320 && d.getWidth()==480))
		    def = false;//Esta guarreria la hago por culpa de los tontos que no ven la opcion de crop
		
		return getSharedPreferences().getBoolean(PREF_PORTRAIT_CROP_X,def);
	}
    */
	
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
		//TODO; Poner el modo en funcion de si es honycomb a acelerated!
		return Integer.valueOf(getSharedPreferences().getString(PREF_GLOBAL_VIDEO_RENDER_MODE,"2")).intValue();	
	}
	
	public boolean isSoundfThreaded(){
		return getSharedPreferences().getBoolean(PREF_GLOBAL_SOUND_THREADED,true);
	}

	public boolean isFPSShowed(){
		return getSharedPreferences().getBoolean(PREF_GLOBAL_SHOW_FPS,false);
	}
	
	public boolean isFPSLimit(){
		return getSharedPreferences().getBoolean(PREF_GLOBAL_FPS_LIMIT,false);
	}
	
	public boolean isDebugEnabled(){
		return getSharedPreferences().getBoolean(PREF_GLOBAL_DEBUG,false);
	}

	public boolean isAnimatedInput(){
		return getSharedPreferences().getBoolean(PREF_ANIMATED_INPUT,true);
	}
	
	public boolean isTouchDZ(){
		return getSharedPreferences().getBoolean(PREF_TOUCH_DZ,true);
	}
}
