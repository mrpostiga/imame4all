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

package com.seleuco.mame4all.prefs;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceManager;
import android.preference.PreferenceScreen;

import com.seleuco.mame4all.helpers.PrefsHelper;
import com.seleuco.mame4all.input.ControlCustomizer;
import com.seleuco.mame4all.input.InputHandler;
import com.seleuco.mame4all.R;

public class UserPreferences extends PreferenceActivity implements OnSharedPreferenceChangeListener {
	
	private SharedPreferences settings;

	protected ListPreference mPrefGlobalVideoRenderMode;
	protected ListPreference mPrefPortraitMode;
    protected ListPreference mPrefLandsMode;
	protected ListPreference mPrefPortraitFilterType;
    protected ListPreference mPrefLandsFilterType;
    protected ListPreference mPrefControllerType;
    protected ListPreference mPrefExtInput;
    protected ListPreference mPrefAnalogDZ;
    protected ListPreference mPrefTiltDZ;

	@Override
	protected void onCreate(Bundle savedInstanceState) {

		super.onCreate(savedInstanceState);
		
		
		addPreferencesFromResource(R.xml.userpreferences);
		
		settings = PreferenceManager.getDefaultSharedPreferences(this);
		
		mPrefGlobalVideoRenderMode = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_GLOBAL_VIDEO_RENDER_MODE);
        mPrefPortraitMode = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_PORTRAIT_SCALING_MODE);
        mPrefLandsMode = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_LANDSCAPE_SCALING_MODE);
        mPrefPortraitFilterType = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_PORTRAIT_FILTER_TYPE);
        mPrefLandsFilterType = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_LANDSCAPE_FILTER_TYPE);        
        mPrefControllerType = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_CONTROLLER_TYPE);
        mPrefExtInput = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_INPUT_EXTERNAL);
        mPrefAnalogDZ = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_ANALOG_DZ);        
        mPrefTiltDZ = (ListPreference)getPreferenceScreen().findPreference(PrefsHelper.PREF_TILT_DZ);
	}
	
	  @Override
	    protected void onResume() {
	        super.onResume();
	        
	        // Setup the initial values
	        //mCheckBoxPreference.setSummary(sharedPreferences.getBoolean(key, false) ? "Disable this setting" : "Enable this setting");
	        mPrefGlobalVideoRenderMode.setSummary("Current value is '" + mPrefGlobalVideoRenderMode.getEntry()+"'"); 
	        mPrefPortraitMode.setSummary("Current value is '" + mPrefPortraitMode.getEntry()+"'"); 
	        mPrefLandsMode.setSummary("Current value is '" + mPrefLandsMode.getEntry()+"'"); 
	        mPrefPortraitFilterType.setSummary("Current value is '" + mPrefPortraitFilterType.getEntry()+"'"); 
	        mPrefLandsFilterType.setSummary("Current value is '" + mPrefLandsFilterType.getEntry()+"'"); 	        
	        mPrefControllerType.setSummary("Current value is '" + mPrefControllerType.getEntry()+"'");
	        mPrefExtInput.setSummary("Current value is '" + mPrefExtInput.getEntry()+"'");
	        mPrefAnalogDZ.setSummary("Current value is '" + mPrefAnalogDZ.getEntry()+"'");
	        mPrefTiltDZ.setSummary("Current value is '" + mPrefTiltDZ.getEntry()+"'");
	        
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
	        else if(key.equals(PrefsHelper.PREF_INPUT_EXTERNAL))
	        {	
	        	mPrefExtInput.setSummary("Current value is '" + mPrefExtInput.getEntry()+"'"); 
	        }
	        else if(key.equals(PrefsHelper.PREF_ANALOG_DZ))
	        {	
	        	mPrefAnalogDZ.setSummary("Current value is '" + mPrefAnalogDZ.getEntry()+"'"); 
	        }
	        else if(key.equals(PrefsHelper.PREF_TILT_DZ))
	        {	
	        	mPrefTiltDZ.setSummary("Current value is '" + mPrefTiltDZ.getEntry()+"'"); 
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
			    	builder.setMessage("Are you sure to change? (needs app restart)")
		    	       .setCancelable(false)
		    	       .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
		    	           public void onClick(DialogInterface dialog, int id) {
		    					SharedPreferences.Editor editor =  settings.edit();
		    					editor.putString(PrefsHelper.PREF_ROMsDIR, null);
		    					editor.commit();
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
