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

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

import android.content.Intent;
import android.content.res.Configuration;
import android.net.Uri;
import android.os.Environment;
import android.view.Display;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import android.widget.FrameLayout.LayoutParams;

import com.seleuco.mame4all.Emulator;
import com.seleuco.mame4all.HelpActivity;
import com.seleuco.mame4all.MAME4all;
import com.seleuco.mame4all.input.InputHandler;
import com.seleuco.mame4all.prefs.UserPreferences;
import com.seleuco.mame4all.views.EmulatorView;
import com.seleuco.mame4all.views.EmulatorViewHW;
import com.seleuco.mame4all.views.InputView;
import com.seleuco.mame4all.R;

public class MainHelper {
	
	final static public  int SUBACTIVITY_USER_PREFS = 1;
	final static public  int SUBACTIVITY_HELP = 2;
	final static public  int BUFFER_SIZE = 1024*48;
	
	final static public  String ROMS_DIR = "/ROMs/MAME4all/";
	final static public  String MAGIC_FILE = "dont-delete-00001.bin";
	
	protected MAME4all mm = null;
	
	public MainHelper(MAME4all value){
		mm = value;
	}
	
	public String getLibDir(){	
		String cache_dir, lib_dir;
		try {
			cache_dir = mm.getCacheDir().getCanonicalPath();				
			lib_dir = cache_dir.replace("cache", "lib");
		} catch (Exception e) {
			e.printStackTrace();
			lib_dir = "/data/data/com.seleuco.mame4all/lib";
		}
		return lib_dir;
	}
	
	public String getResDir()
	{
		String res_dir;
		try {
			res_dir = Environment.getExternalStorageDirectory().getCanonicalPath()+ROMS_DIR;
		} catch (IOException e) {
			
			e.printStackTrace();
			res_dir = "/sdcard"+ROMS_DIR;
		}

		return res_dir;
	}
	
	public boolean ensureResDir(){
		File res_dir = new File(getResDir());
		
		boolean created = false;
		
		if(res_dir.exists() == false)
		{
			if(!res_dir.mkdirs())
			{
				mm.getDialogHelper().setErrorMsg("Can't find/create:\n '"+getResDir()+"'");
				mm.showDialog(DialogHelper.DIALOG_ERROR);
				return false;				
			}
			else
			{
               created= true;
			}
		}
		
		String str_sav_dir = getResDir()+"saves/";
		File sav_dir = new File(str_sav_dir);
		if(sav_dir.exists() == false)
		{
			
			if(!sav_dir.mkdirs())
			{
				mm.getDialogHelper().setErrorMsg("Can't find/create:\n'"+str_sav_dir+"'");
				mm.showDialog(DialogHelper.DIALOG_ERROR);
				return false;				
			}
		}
		
		if(created )
		{
			
			mm.getDialogHelper().setInfoMsg("Created: \n'"+getResDir()+"'\nPut your zipped ROMs on it!.\n\nMAME4droid uses only 'gp2x wiz 0.37b11 MAME romset'. Google it or use clrmame.dat file included  to convert romsets from other MAME versions. See  help.");
			mm.showDialog(DialogHelper.DIALOG_INFO);

		}
		
		return true;		
	}
	
	public void copyFiles(){
		
		try {
			
			File fm = new File(getResDir()+ File.separator + "saves/" + MAGIC_FILE);
			if(fm.exists())
				return;
			
			fm.createNewFile();
			
			// Create a ZipInputStream to read the zip file
			BufferedOutputStream dest = null;
			InputStream fis = mm.getResources().openRawResource(R.raw.roms);
			ZipInputStream zis = new ZipInputStream(

			new BufferedInputStream(fis));
			// Loop over all of the entries in the zip file
			int count;
			byte data[] = new byte[BUFFER_SIZE];
			ZipEntry entry;
			while ((entry = zis.getNextEntry()) != null) {
				if (!entry.isDirectory()) {

					String destination = this.getResDir();
					String destFN = destination + File.separator + entry.getName();
					// Write the file to the file system
					FileOutputStream fos = new FileOutputStream(destFN);
					dest = new BufferedOutputStream(fos, BUFFER_SIZE);
					while ((count = zis.read(data, 0, BUFFER_SIZE)) != -1) {
						dest.write(data, 0, count);
					}
					dest.flush();
					dest.close();
				}
				else
				{
					File f = new File(getResDir()+ File.separator + entry.getName());
					f.mkdirs();
				}
				
			}
			zis.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public int getscrOrientation() {
		Display getOrient = mm.getWindowManager().getDefaultDisplay();
		//int orientation = getOrient.getOrientation();
		
		int orientation  = mm.getResources().getConfiguration().orientation;


		// Sometimes you may get undefined orientation Value is 0
		// simple logic solves the problem compare the screen
		// X,Y Co-ordinates and determine the Orientation in such cases
		if (orientation == Configuration.ORIENTATION_UNDEFINED) {

			Configuration config = mm.getResources().getConfiguration();
			orientation = config.orientation;

			if (orientation == Configuration.ORIENTATION_UNDEFINED) {
				// if emu_height and widht of screen are equal then
				// it is square orientation
				if (getOrient.getWidth() == getOrient.getHeight()) {
					orientation = Configuration.ORIENTATION_SQUARE;
				} else { // if widht is less than emu_height than it is portrait
					if (getOrient.getWidth() < getOrient.getHeight()) {
						orientation = Configuration.ORIENTATION_PORTRAIT;
					} else { // if it is not any of the above it will defineitly
								// be landscape
						orientation = Configuration.ORIENTATION_LANDSCAPE;
					}
				}
			}
		}
		return orientation; // return values 1 is portrait and 2 is Landscape
							// Mode
	}
	
	public void reload() {

	    Intent intent = mm.getIntent();

	    mm.overridePendingTransition(0, 0);
	    intent.addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
	    mm.finish();

	    mm.overridePendingTransition(0, 0);
	    mm.startActivity(intent);
	}
	
	public void updateVideoRender(){
		
			EmulatorView emuView =  mm.getEmuView();
			EmulatorViewHW emuView_HW = mm.getEmuViewHW();
			
			if(mm.getPrefsHelper().getVideoRenderMode() == PrefsHelper.PREF_RENDER_HW )
			{	        
				mm.getWindow().setFlags(
		                WindowManager.LayoutParams.FLAG_HARDWARE_ACCELERATED,
		                WindowManager.LayoutParams.FLAG_HARDWARE_ACCELERATED);
				
				emuView.setVisibility(View.GONE);
				emuView_HW.setVisibility(View.VISIBLE);
				
			}
			else
			{
				if(emuView_HW!=null)
				  emuView_HW.setVisibility(View.GONE);
				
				emuView.setVisibility(View.VISIBLE);	

			}
			
			if(Emulator.getVideoRenderMode() != mm.getPrefsHelper().getVideoRenderMode() 
			     && (Emulator.getVideoRenderMode() == PrefsHelper.PREF_RENDER_HW  || 
			         mm.getPrefsHelper().getVideoRenderMode() == PrefsHelper.PREF_RENDER_HW)
		      )
			{
				Emulator.setVideoRenderMode(mm.getPrefsHelper().getVideoRenderMode());
				reload();
			}
			else
			{
			    Emulator.setVideoRenderMode(mm.getPrefsHelper().getVideoRenderMode());
			}    
					
	}

	
	public void updateMAME4all(){
		
		EmulatorView emuView =  mm.getEmuView();
		EmulatorViewHW emuView_HW = mm.getEmuViewHW();
		InputView inputView =  mm.getInputView();
		InputHandler inputHandler = mm.getInputHandler();
		PrefsHelper prefsHelper = mm.getPrefsHelper();
		
		String definedKeys = prefsHelper.getDefinedKeys();
		final String[] keys = definedKeys.split(":");
		for(int i=0;i<keys.length;i++)
			InputHandler.keyMapping[i]=Integer.valueOf(keys[i]).intValue();
		
		Emulator.setValue(Emulator.FPS_SHOWED_KEY, prefsHelper.isFPSShowed() ? 1 : 0);
		Emulator.setDebug(prefsHelper.isDebugEnabled());
		Emulator.setThreadedSound(prefsHelper.isSoundfThreaded());
		Emulator.setFrameLimit(prefsHelper.isFPSLimit());
		
		updateVideoRender();
		
		inputHandler.setTrackballSensitivity( prefsHelper.getTrackballSensitivity());
		inputHandler.setTrackballEnabled(!prefsHelper.isTrackballNoMove());
				
		int state = mm.getInputHandler().getInputHandlerState();
		
		if(this.getscrOrientation() == Configuration.ORIENTATION_PORTRAIT)
		{
			emuView.setScaleType(prefsHelper.getPortraitScaleMode());
			if(emuView_HW!=null)
			   emuView_HW.setScaleType(prefsHelper.getPortraitScaleMode());	
			Emulator.setFrameFiltering(prefsHelper.isPortraitBitmapFiltering());
			
			if(state == InputHandler.STATE_SHOWING_CONTROLLER && !prefsHelper.isPortraitTouchController())
				inputHandler.changeState();
				
			if(state == InputHandler.STATE_SHOWING_NONE && prefsHelper.isPortraitTouchController())
			    inputHandler.changeState();	
			
			state = mm.getInputHandler().getInputHandlerState();
			
			if(state == InputHandler.STATE_SHOWING_NONE)
			{	
				inputView.setVisibility(View.GONE);
			}	
			else
			{	
			    inputView.setVisibility(View.VISIBLE);
			}   

			if(state == InputHandler.STATE_SHOWING_CONTROLLER)
			{			    	
			   	inputView.setImageDrawable(mm.getResources().getDrawable(R.drawable.back_portrait));				
			   	inputHandler.readControllerValues(R.raw.controller_portrait);
			}
			
			//Emulator.setEmuSize(prefshelper.isPortraitCropX(), prefshelper.isPortraitCropY());
		}
		else
		{
			emuView.setScaleType(mm.getPrefsHelper().getLandscapeScaleMode());
			if(emuView_HW!=null)
			   emuView_HW.setScaleType(mm.getPrefsHelper().getLandscapeScaleMode());
			Emulator.setFrameFiltering(mm.getPrefsHelper().isLandscapeBitmapFiltering());
			
			if(state == InputHandler.STATE_SHOWING_CONTROLLER && !prefsHelper.isLandscapeTouchController())
				inputHandler.changeState();
			
			if(state == InputHandler.STATE_SHOWING_NONE && prefsHelper.isLandscapeTouchController())
			    inputHandler.changeState();	
			
			state = mm.getInputHandler().getInputHandlerState();
			
		    inputView.bringToFront();
		    LayoutParams lp  = (LayoutParams) emuView.getLayoutParams();
			lp.gravity = Gravity.CENTER;
			lp.leftMargin = 0;
			
			if(state == InputHandler.STATE_SHOWING_NONE)
			{	
				inputView.setVisibility(View.GONE);
			}	
			else
			{	
			    inputView.setVisibility(View.VISIBLE);
			}   

			if(state == InputHandler.STATE_SHOWING_CONTROLLER)
			{			    	
			    		
				int i = prefsHelper.getLandscapeControllerType();
				
				if(i==1)										
				{				   	
					/*
					inputView.setImageDrawable(mm.getResources().getDrawable(R.drawable.controller_fs1));
			    									
				   	//inputHandler.readControllerValues(R.raw.controller_fs1);
						
					lp.gravity = Gravity.CENTER | Gravity.RIGHT;
					
					//150 480x320 800x480
                    //
					
					//lp.leftMargin = 220; //TODO calcular
										
					lp.leftMargin = (int)((mm.getWindowManager().getDefaultDisplay().getWidth() / 480f) * 140);
					
				   	emuView.setLayoutParams(lp);				   	
				   	emuView.bringToFront();
				   	*/
				}
				else
				{
					inputView.setImageDrawable(null);
			   	    inputHandler.readControllerValues(R.raw.controller_landscape);			   	    
				}
			}

		}
		
		int op = inputHandler.getOpacity();
		if (op != -1 && (state == InputHandler.STATE_SHOWING_CONTROLLER) )
			inputView.setAlpha(op);


		inputView.requestLayout();
		
		if(emuView_HW!=null)
		  emuView_HW.requestLayout();
  				
		emuView.requestLayout();
		inputView.invalidate();
		emuView.invalidate();
		
		if(emuView_HW!=null)	
		  emuView_HW.invalidate();
		
		Emulator.ensureScreenDrawed();				
	}
	
	public void showDonate(){		
		Intent browserIntent = new Intent("android.intent.action.VIEW",Uri.parse("https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=seleuco%2enicator%40gmail%2ecom&lc=US&item_name=Seleuco%20Nicator&item_number=ixxxx4all&no_note=0&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%3aNonHostedGuest"));  
		mm.startActivity(browserIntent);
	}
	
	public void showSettings(){
		Intent i = new Intent(mm, UserPreferences.class);
		mm.startActivityForResult(i, MainHelper.SUBACTIVITY_USER_PREFS);
	}
	
	public void showHelp(){
		Intent i2 = new Intent(mm, HelpActivity.class);
		mm.startActivityForResult(i2, MainHelper.SUBACTIVITY_HELP);		
	}
	
	public void activityResult(int requestCode, int resultCode, Intent data) {
		
		if(requestCode == SUBACTIVITY_USER_PREFS)
		{	
            updateMAME4all();
		}   
	}
	
}
