/*
 * This file is part of MAME4droid.
 *
 * Copyright (C) 2013 David Valdeita (Seleuco)
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
 * Note that people who make modified versions of MAME4idroid are not
 * obligated to grant this special exception for their modified versions; it
 * is their choice whether to do so. The GNU General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 *
 * MAME4droid is dual-licensed: Alternatively, you can license MAME4droid
 * under a MAME license, as set out in http://mamedev.org/
 */

package com.seleuco.mame4droid.prefs;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceManager;
import android.preference.PreferenceScreen;

import com.seleuco.mame4droid.Emulator;
import com.seleuco.mame4droid.R;
import com.seleuco.mame4droid.helpers.PrefsHelper;
import com.seleuco.mame4droid.input.ControlCustomizer;
import com.seleuco.mame4droid.input.InputHandler;
import com.seleuco.mame4droid.input.InputHandlerExt;

public class UserPreferences extends PreferenceActivity implements OnSharedPreferenceChangeListener {
	
	private SharedPreferences settings;

	protected ListPreference mPrefGlobalVideoRenderMode;
	protected ListPreference mPrefResolution;
	protected ListPreference mPrefSpeed;	
	protected ListPreference mPrefPortraitMode;
    protected ListPreference mPrefLandsMode;
	protected ListPreference mPrefPortraitFilterType;
    protected ListPreference mPrefLandsFilterType;
    protected ListPreference mPrefControllerType;
    protected ListPreference mPrefExtInput;
    protected ListPreference mPrefAutomap;
    protected ListPreference mPrefAnalogDZ;
    protected ListPreference mPrefGamepadDZ;
    protected ListPreference mPrefTiltDZ;
    protected ListPreference mPrefTiltNeutral;
    protected ListPreference mPrefFrameSkip;
    protected ListPreference mPrefSound;
    protected ListPreference mPrefStickType;
    protected ListPreference mPrefNumButtons;
    protected ListPreference mPrefSizeButtons;
    protected ListPreference mPrefVideoThPr;
    protected ListPreference mPrefMainThPr;
    protected ListPreference mPrefSoundLantency;
    protected ListPreference mPrefAutofire;
    protected ListPreference mPrefVSync;
    protected ListPreference mPrefFilterCat;
    protected ListPreference mPrefFilterDrvSrc;
    protected ListPreference mPrefFilterManuf;
    protected ListPreference mPrefFilterYGTE;
    protected ListPreference mPrefFilterYLTE;  
    protected EditTextPreference mPrefFilterkeyword;
    
	@Override
	protected void onCreate(Bundle savedInstanceState) {

		super.onCreate(savedInstanceState);
				
		addPreferencesFromResource(R.xml.userpreferences);
		
		settings = PreferenceManager.getDefaultSharedPreferences(this);
		
		mPrefGlobalVideoRenderMode = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_GLOBAL_VIDEO_RENDER_MODE);
		mPrefResolution = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_GLOBAL_RESOLUTION);
		mPrefSpeed = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_GLOBAL_SPEED);
        mPrefPortraitMode = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_PORTRAIT_SCALING_MODE);
        mPrefLandsMode = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_LANDSCAPE_SCALING_MODE);
        mPrefPortraitFilterType = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_PORTRAIT_FILTER_TYPE);
        mPrefLandsFilterType = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_LANDSCAPE_FILTER_TYPE);        
        mPrefControllerType = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_CONTROLLER_TYPE);
        mPrefExtInput = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_INPUT_EXTERNAL);
        mPrefAutomap = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_AUTOMAP_OPTIONS);
        mPrefAnalogDZ = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_ANALOG_DZ); 
        mPrefGamepadDZ = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_GAMEPAD_DZ);
        mPrefTiltDZ = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_TILT_DZ);
        mPrefTiltNeutral = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_TILT_NEUTRAL);
        mPrefFrameSkip = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_GLOBAL_FRAMESKIP);
        mPrefSound = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_GLOBAL_SOUND);
        mPrefStickType = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_STICK_TYPE);
        mPrefNumButtons = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_NUMBUTTONS);
        mPrefSizeButtons = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_BUTTONS_SIZE);        
        mPrefVideoThPr = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_VIDEO_THREAD_PRIORITY);
        mPrefMainThPr = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_MAIN_THREAD_PRIORITY);
        mPrefSoundLantency = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_SOUND_LATENCY);
        mPrefAutofire = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_AUTOFIRE);
        mPrefVSync = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_GLOBAL_VSYNC);
        		
		mPrefFilterCat = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_FILTER_CATEGORY);	
		populateList(Emulator.FILTER_NUM_CATEGORIES,Emulator.FILTER_CATEGORIES_ARRAY,mPrefFilterCat);
		
		mPrefFilterDrvSrc = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_FILTER_DRVSRC);
		populateList(Emulator.FILTER_NUM_DRIVERS_SRC,Emulator.FILTER_DRIVERS_SRC_ARRAY,mPrefFilterDrvSrc);
        
		mPrefFilterManuf = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_FILTER_MANUF);
		populateList(Emulator.FILTER_NUM_MANUFACTURERS,Emulator.FILTER_MANUFACTURERS_ARRAY,mPrefFilterManuf);
		
		mPrefFilterYGTE = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_FILTER_YGTE);
		populateList(Emulator.FILTER_NUM_YEARS,Emulator.FILTER_YEARS_ARRAY,mPrefFilterYGTE);
		mPrefFilterYLTE = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_FILTER_YLTE);
		populateList(Emulator.FILTER_NUM_YEARS,Emulator.FILTER_YEARS_ARRAY,mPrefFilterYLTE);
		
		mPrefFilterkeyword = (EditTextPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_FILTER_KEYWORD);
	}
	
	protected void populateList(int key1, int key2, ListPreference lp){
        int i = 0;
		int n = 0; 
		CharSequence[] cs = null;
		CharSequence[] csv = null;
		
		n = Emulator.getValue(key1);
		cs = new String[n+1];
		csv = new String[n+1];
		cs[0] = "All";
		csv[0] = "-1";
		while(i<n)
		{			
			i++;
			cs[i] =Emulator.getValueStr(key2,i);
			csv[i] = i+"";		
		}
		lp.setEntries(cs);
		lp.setEntryValues(csv);	
	}
	
	  @Override
	    protected void onResume() {
	        super.onResume();
	        
	        // Setup the initial values
	        //mCheckBoxPreference.setSummary(sharedPreferences.getBoolean(key, false) ? "Disable this setting" : "Enable this setting");
	        mPrefGlobalVideoRenderMode.setSummary("Current value is '" + mPrefGlobalVideoRenderMode.getEntry()+"'");
	        mPrefResolution.setSummary("Current value is '" + mPrefResolution.getEntry()+"'");
	        mPrefSpeed.setSummary("Current value is '" + mPrefSpeed.getEntry()+"'");
	        mPrefPortraitMode.setSummary("Current value is '" + mPrefPortraitMode.getEntry()+"'"); 
	        mPrefLandsMode.setSummary("Current value is '" + mPrefLandsMode.getEntry()+"'"); 
	        mPrefPortraitFilterType.setSummary("Current value is '" + mPrefPortraitFilterType.getEntry()+"'"); 
	        mPrefLandsFilterType.setSummary("Current value is '" + mPrefLandsFilterType.getEntry()+"'"); 	        
	        mPrefControllerType.setSummary("Current value is '" + mPrefControllerType.getEntry()+"'");
	        mPrefExtInput.setSummary("Current value is '" + mPrefExtInput.getEntry()+"'");
	        mPrefAutomap.setSummary("Current value is '" + mPrefAutomap.getEntry()+"'");
	        mPrefAnalogDZ.setSummary("Current value is '" + mPrefAnalogDZ.getEntry()+"'");
	        mPrefGamepadDZ.setSummary("Current value is '" + mPrefGamepadDZ.getEntry()+"'");
	        mPrefTiltDZ.setSummary("Current value is '" + mPrefTiltDZ.getEntry()+"'");
	        mPrefTiltNeutral.setSummary("Current value is '" + mPrefTiltNeutral.getEntry()+"'");
	        mPrefFrameSkip.setSummary("Current value is '" + mPrefFrameSkip.getEntry()+"'");
	        mPrefSound.setSummary("Current value is '" + mPrefSound.getEntry()+"'");
	        mPrefStickType.setSummary("Current value is '" + mPrefStickType.getEntry()+"'");
	        mPrefNumButtons.setSummary("Current value is '" + mPrefNumButtons.getEntry()+"'");
	        mPrefSizeButtons.setSummary("Current value is '" + mPrefSizeButtons.getEntry()+"'");
	        mPrefVideoThPr.setSummary("Current value is '" + mPrefVideoThPr.getEntry()+"'");
	        mPrefMainThPr.setSummary("Current value is '" + mPrefMainThPr.getEntry()+"'");
	        mPrefSoundLantency.setSummary("Current value is '" + mPrefSoundLantency.getEntry()+"'");
	        mPrefAutofire.setSummary("Current value is '" + mPrefAutofire.getEntry()+"'");
	        mPrefVSync.setSummary("Current value is '" + mPrefVSync.getEntry()+"'");
	        mPrefFilterCat.setSummary("Current value is '" + mPrefFilterCat.getEntry()+"'");
	        mPrefFilterDrvSrc.setSummary("Current value is '" + mPrefFilterDrvSrc.getEntry()+"'");
	        mPrefFilterManuf.setSummary("Current value is '" + mPrefFilterManuf.getEntry()+"'");
	        mPrefFilterYGTE.setSummary("Current value is '" + mPrefFilterYGTE.getEntry()+"'");
	        mPrefFilterYLTE.setSummary("Current value is '" + mPrefFilterYLTE.getEntry()+"'");   
	        mPrefFilterkeyword.setSummary("Current value is '" + mPrefFilterkeyword.getText()+"'"); 
	        // Set up a listener whenever a key changes            
	        getPreferenceScreen().getSharedPreferences().registerOnSharedPreferenceChangeListener(this);
	    }

	    @Override
	    protected void onPause() {
	        super.onPause();

	        // Unregister the listener whenever a key changes            
	        getPreferenceScreen().getSharedPreferences().unregisterOnSharedPreferenceChangeListener(this);    
	    }
	    
	    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
	        // Let's do something a preference values changes
	    	/*
	        if (key.equals(KEY_CHECKBOX_PREFERENCE)) {
	          mCheckBoxPreference.setSummary(sharedPreferences.getBoolean(key, false) ? "Disable this setting" : "Enable this setting");
	        }
	        else*/ 
	        if (key.equals(PrefsHelper.PREF_PORTRAIT_SCALING_MODE)) 
	        {
	            mPrefPortraitMode.setSummary("Current value is '" + mPrefPortraitMode.getEntry()+"'"); 
	        }
	        else if(key.equals(PrefsHelper.PREF_LANDSCAPE_SCALING_MODE))
	        {
	        	mPrefLandsMode.setSummary("Current value is '" + mPrefLandsMode.getEntry()+"'");	
	        }
	        if (key.equals(PrefsHelper.PREF_PORTRAIT_FILTER_TYPE)) 
	        {
	        	mPrefPortraitFilterType.setSummary("Current value is '" + mPrefPortraitFilterType.getEntry()+"'"); 
	        }
	        else if(key.equals(PrefsHelper.PREF_LANDSCAPE_FILTER_TYPE))
	        {
	        	mPrefLandsFilterType.setSummary("Current value is '" + mPrefLandsFilterType.getEntry()+"'");	
	        }	        
	        else if(key.equals(PrefsHelper.PREF_CONTROLLER_TYPE))
	        {	
	            mPrefControllerType.setSummary("Current values is '" + mPrefControllerType.getEntry()+"'");
	        }
	        else if(key.equals(PrefsHelper.PREF_GLOBAL_VIDEO_RENDER_MODE))
	        {		        	
				mPrefGlobalVideoRenderMode.setSummary("Current value is '" + mPrefGlobalVideoRenderMode.getEntry()+"'"); 
	        }
	        else if(key.equals(PrefsHelper.PREF_GLOBAL_RESOLUTION))
	        {	
	        	mPrefResolution.setSummary("Current value is '" + mPrefResolution.getEntry()+"'"); 
	        }	
	        else if(key.equals(PrefsHelper.PREF_GLOBAL_SPEED))
	        {	
	        	mPrefSpeed.setSummary("Current value is '" + mPrefSpeed.getEntry()+"'"); 
	        }	        
	        else if(key.equals(PrefsHelper.PREF_INPUT_EXTERNAL))
	        {	
	        	try{InputHandlerExt.resetAutodetected();}catch(Error e){};
	        	mPrefExtInput.setSummary("Current value is '" + mPrefExtInput.getEntry()+"'"); 
	        }
	        else if(key.equals(PrefsHelper.PREF_AUTOMAP_OPTIONS))
	        {	
	        	try{InputHandlerExt.resetAutodetected();}catch(Error e){};
	        	mPrefAutomap.setSummary("Current value is '" + mPrefAutomap.getEntry()+"'"); 
	        }	        
	        else if(key.equals(PrefsHelper.PREF_ANALOG_DZ))
	        {	
	        	mPrefAnalogDZ.setSummary("Current value is '" + mPrefAnalogDZ.getEntry()+"'"); 
	        }
	        else if(key.equals(PrefsHelper.PREF_GAMEPAD_DZ))
	        {	
	        	mPrefGamepadDZ.setSummary("Current value is '" + mPrefGamepadDZ.getEntry()+"'"); 
	        }	        
	        else if(key.equals(PrefsHelper.PREF_TILT_DZ))
	        {	
	        	mPrefTiltDZ.setSummary("Current value is '" + mPrefTiltDZ.getEntry()+"'"); 
	        }
	        else if(key.equals(PrefsHelper.PREF_TILT_NEUTRAL))
	        {	
	        	mPrefTiltNeutral.setSummary("Current value is '" + mPrefTiltNeutral.getEntry()+"'"); 
	        }	        
		    else if(key.equals(PrefsHelper.PREF_GLOBAL_FRAMESKIP))
		    {	
		    	mPrefFrameSkip.setSummary("Current value is '" + mPrefFrameSkip.getEntry()+"'"); 
		    }
		    else if(key.equals(PrefsHelper.PREF_GLOBAL_SOUND))
		    {	
		    	mPrefSound.setSummary("Current value is '" + mPrefSound.getEntry()+"'"); 
	        }
		    else if(key.equals(PrefsHelper.PREF_STICK_TYPE))
		    {	
		    	mPrefStickType.setSummary("Current value is '" + mPrefStickType.getEntry()+"'"); 
		    }
		    else if(key.equals(PrefsHelper.PREF_NUMBUTTONS))
		    {	
		    	mPrefNumButtons.setSummary("Current value is '" + mPrefNumButtons.getEntry()+"'"); 
		    }
		    else if(key.equals(PrefsHelper.PREF_BUTTONS_SIZE))
		    {	
		    	mPrefSizeButtons.setSummary("Current value is '" + mPrefSizeButtons.getEntry()+"'"); 
		    }	 
		    else if(key.equals(PrefsHelper.PREF_VIDEO_THREAD_PRIORITY))
		    {	        
	            mPrefVideoThPr.setSummary("Current value is '" + mPrefVideoThPr.getEntry()+"'");
		    }
			else if(key.equals(PrefsHelper.PREF_MAIN_THREAD_PRIORITY))
			{    
	            mPrefMainThPr.setSummary("Current value is '" + mPrefMainThPr.getEntry()+"'");
			}
		    else if(key.equals(PrefsHelper.PREF_SOUND_LATENCY))
		    {
	            mPrefSoundLantency.setSummary("Current value is '" + mPrefSoundLantency.getEntry()+"'");
		    }    
		    else if(key.equals(PrefsHelper.PREF_AUTOFIRE))
		    {
		    	mPrefAutofire.setSummary("Current value is '" + mPrefAutofire.getEntry()+"'");
		    }  	
		    else if(key.equals(PrefsHelper.PREF_GLOBAL_VSYNC))
		    {
		    	mPrefVSync.setSummary("Current value is '" + mPrefVSync.getEntry()+"'");
		    } 	  
		    else if(key.equals(PrefsHelper.PREF_FILTER_CATEGORY))
		    {
		    	mPrefFilterCat.setSummary("Current value is '" + mPrefFilterCat.getEntry()+"'");
		    }
		    else if(key.equals(PrefsHelper.PREF_FILTER_DRVSRC))
		    {
		    	mPrefFilterDrvSrc.setSummary("Current value is '" + mPrefFilterDrvSrc.getEntry()+"'");
		    } 
		    else if(key.equals(PrefsHelper.PREF_FILTER_MANUF))
		    {
		    	mPrefFilterManuf.setSummary("Current value is '" + mPrefFilterManuf.getEntry()+"'");
		    } 	 
		    else if(key.equals(PrefsHelper.PREF_FILTER_YGTE))
		    {
		    	mPrefFilterYGTE.setSummary("Current value is '" + mPrefFilterYGTE.getEntry()+"'");
		    } 
		    else if(key.equals(PrefsHelper.PREF_FILTER_YLTE))
		    {
		    	mPrefFilterYLTE.setSummary("Current value is '" + mPrefFilterYLTE.getEntry()+"'");
		    } 
		    else if(key.equals(PrefsHelper.PREF_FILTER_KEYWORD))
		    {
		    	mPrefFilterkeyword.setSummary("Current value is '" + mPrefFilterkeyword.getText()+"'");
		    } 	        
	    }

		@Override
		public boolean onPreferenceTreeClick(PreferenceScreen preferenceScreen,
				Preference pref) {
			
			if (pref.getKey().equals("defineKeys")) {
				startActivityForResult(new Intent(this, DefineKeys.class), 1);
			}
			else if (pref.getKey().equals("changeRomPath")) {
				 AlertDialog.Builder builder = new AlertDialog.Builder(this);
			    	builder.setMessage("Are you sure? (app restart needed)")
		    	       .setCancelable(false)
		    	       .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
		    	           public void onClick(DialogInterface dialog, int id) {
		    					SharedPreferences.Editor editor =  settings.edit();
		    					editor.putString(PrefsHelper.PREF_ROMsDIR, null);
		    					editor.commit();
		    					Emulator.setNeedRestart(true);
		    	                //android.os.Process.killProcess(android.os.Process.myPid());  
		    	           }
		    	       })
		    	       .setNegativeButton("No", new DialogInterface.OnClickListener() {
		    	           public void onClick(DialogInterface dialog, int id) {
		    	                dialog.cancel();
		    	           }
		    	       });
			    	Dialog dialog = builder.create();
			    	dialog.show();				
			}
			else if (pref.getKey().equals("defaultsKeys")) {

				 AlertDialog.Builder builder = new AlertDialog.Builder(this);
			    	builder.setMessage("Are you sure to restore?")
		    	       .setCancelable(false)
		    	       .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
		    	           public void onClick(DialogInterface dialog, int id) {
		    					SharedPreferences.Editor editor =  settings.edit();
		    					
		    					StringBuffer definedKeysStr = new StringBuffer(); 
		    					
		    					for(int i=0; i< InputHandler.defaultKeyMapping.length;i++)
		    					{	
		    						InputHandler.keyMapping[i] = InputHandler.defaultKeyMapping[i];
		    						definedKeysStr.append(InputHandler.defaultKeyMapping[i]+":");
		    					}
		    					editor.putString(PrefsHelper.PREF_DEFINED_KEYS, definedKeysStr.toString());
		    					editor.commit();
		    					//finish();
		    				
		    	           }
		    	       })
		    	       .setNegativeButton("No", new DialogInterface.OnClickListener() {
		    	           public void onClick(DialogInterface dialog, int id) {
		    	                dialog.cancel();
		    	           }
		    	       });
			    	Dialog dialog = builder.create();
			    	dialog.show();
			}
			else if (pref.getKey().equals("customControlLayout")) {
				ControlCustomizer.setEnabled(true);
				finish();
			}
			else if (pref.getKey().equals("defaultControlLayout")) {

				 AlertDialog.Builder builder = new AlertDialog.Builder(this);
			    	builder.setMessage("Are you sure to restore?")
		    	       .setCancelable(false)
		    	       .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
		    	           public void onClick(DialogInterface dialog, int id) {
		    					SharedPreferences.Editor editor =  settings.edit();
		    					editor.putString(PrefsHelper.PREF_DEFINED_CONTROL_LAYOUT, null);
		    					editor.putString(PrefsHelper.PREF_DEFINED_CONTROL_LAYOUT_P, null);
		    					editor.commit();
		    	           }
		    	       })
		    	       .setNegativeButton("No", new DialogInterface.OnClickListener() {
		    	           public void onClick(DialogInterface dialog, int id) {
		    	                dialog.cancel();
		    	           }
		    	       });
			    	Dialog dialog = builder.create();
			    	dialog.show();
			}	
			else if (pref.getKey().equals("restoreFilters")) {

				 AlertDialog.Builder builder = new AlertDialog.Builder(this);
			    	builder.setMessage("Are you sure to restore?")
		    	       .setCancelable(false)
		    	       .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
		    	           public void onClick(DialogInterface dialog, int id) {
		    	        	SharedPreferences.Editor editor =  settings.edit();
		    	       		editor.putBoolean(PrefsHelper.PREF_FILTER_FAVORITES, false);
		    	    		editor.putBoolean(PrefsHelper.PREF_FILTER_CLONES, false);		
		    	    		editor.putBoolean(PrefsHelper.PREF_FILTER_NOTWORKING, false);
		    	    		editor.putString(PrefsHelper.PREF_FILTER_YGTE, "-1");
		    	    		editor.putString(PrefsHelper.PREF_FILTER_YLTE, "-1");
		    	    		editor.putString(PrefsHelper.PREF_FILTER_MANUF, "-1");
		    	    		editor.putString(PrefsHelper.PREF_FILTER_CATEGORY,"-1");
		    	    		editor.putString(PrefsHelper.PREF_FILTER_DRVSRC, "-1");	
		    	    		editor.putString(PrefsHelper.PREF_FILTER_KEYWORD, "");			
		    	    		editor.commit();
		    	    		finish();
		    	    		startActivity(getIntent());
		    	           }
		    	       })
		    	       .setNegativeButton("No", new DialogInterface.OnClickListener() {
		    	           public void onClick(DialogInterface dialog, int id) {
		    	                dialog.cancel();
		    	           }
		    	       });
			    	Dialog dialog = builder.create();
			    	dialog.show();
			}				
			
			return super.onPreferenceTreeClick(preferenceScreen, pref);
		}
	    
		@Override
		protected void onActivityResult(int requestCode, int resultCode, Intent data) {
			super.onActivityResult(requestCode, resultCode, data);
			
			if (resultCode == RESULT_OK && requestCode == 0) {
				setResult(RESULT_OK, data);
			} 
			else if (requestCode == 1) {
				SharedPreferences.Editor editor =  settings.edit();
					
				StringBuffer definedKeysStr = new StringBuffer(); 
				
				for(int i=0; i< InputHandler.keyMapping.length;i++)
					definedKeysStr.append(InputHandler.keyMapping[i]+":");
				
				editor.putString(PrefsHelper.PREF_DEFINED_KEYS, definedKeysStr.toString());
				editor.commit();
				return;
			}
			finish();
		}
}
