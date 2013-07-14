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

package com.seleuco.mame4droid.input;

import android.annotation.TargetApi;
import android.os.Build;
import android.provider.Settings;
import android.util.SparseIntArray;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnGenericMotionListener;
import android.widget.Toast;

import com.seleuco.mame4droid.Emulator;
import com.seleuco.mame4droid.MAME4droid;
import com.seleuco.mame4droid.helpers.DialogHelper;
import com.seleuco.mame4droid.helpers.PrefsHelper;

@TargetApi(Build.VERSION_CODES.HONEYCOMB_MR1) 
public class InputHandlerExt extends InputHandler implements OnGenericMotionListener  {
	
	protected int MAX_DEVICES	= 4;
	protected int MAX_KEYS	= 250;
	
	protected float MY_PI	= 3.14159265f;
	protected int oldinput[] = new int[MAX_DEVICES], newinput[] = new int[MAX_DEVICES];
	
	protected int deviceIDs [] = new int[MAX_DEVICES];
	public  static int numDevs = 0;
	
	protected int [][]deviceMappings = new int[MAX_KEYS][MAX_DEVICES];
	
	protected static SparseIntArray banDev = new SparseIntArray(50);
	
	protected boolean isShield = false;
	
	public static void resetAutodetected(){
		numDevs = 0;
		banDev.clear();
	}
	
	public InputHandlerExt(MAME4droid value) {
		super(value);
		
		//vemos dispositivos!
		/*
		int ids[] = InputDevice.getDeviceIds();
		for(int i=0; i< ids.length; i++)
		{
			InputDevice id = InputDevice.getDevice(ids[i]);
			System.out.println("name: "+id.getName());
			System.out.println(id.toString());
		}
		
		for(int i=0; i < MAX_DEVICES; i++)
		{
			for(int j=0; j < MAX_KEYS; j++)
			{
				deviceMappings[j][i] = -1;
			}
		}*/
		
		InputHandlerExt.resetAutodetected();
	}
	
	final public float rad2degree(float r){
		   return ((r * 180.0f) / MY_PI);
	}
	
	protected float processAxis(InputDevice.MotionRange range, float axisvalue){
		float absaxisvalue = Math.abs(axisvalue);
		float deadzone = range.getFlat();
		//System.out.println("deadzone: "+deadzone);
		//deadzone = Math.max(deadzone, 0.2f);
		if(absaxisvalue <= deadzone ){
			return 0.0f;
		}
		float nomralizedvalue;
		if(axisvalue < 0.0f){
			nomralizedvalue = absaxisvalue / range.getMin();
		}else{
			nomralizedvalue = absaxisvalue / range.getMax();
		}
		
		return nomralizedvalue;
	}
		
	@Override
	public boolean onGenericMotion(View view, MotionEvent event) {
	      if (((event.getSource() & InputDevice.SOURCE_CLASS_JOYSTICK) == 0)
	 	         || (event.getAction() != MotionEvent.ACTION_MOVE)) {
	 	          return false;
	 	     }
          int historySize = event.getHistorySize();
          for (int i = 0; i < historySize; i++) {
             processJoystickInput(event,i);
          }

          processJoystickInput(event,-1);
          return true;
  
	}
	
	final public float getAxisValue(int axis, MotionEvent event, int historyPos ){
		float value = 0.0f;
		InputDevice device = event.getDevice();
		if(device!=null)
		{
		    InputDevice.MotionRange range = device.getMotionRange(axis, event.getSource());
		    if (range != null) {
		         float axisValue;
		         if (historyPos >= 0) {
		             axisValue = event.getHistoricalAxisValue(axis, historyPos);
		         } else {
		             axisValue = event.getAxisValue(axis);
		         }
		         value = this.processAxis(range, axisValue);
		    	 //System.out.print("x: "+x);
		    }
	    }		
		return value;
	}
	
	final public float  getAngle(float x, float y){
		float ang = rad2degree((float)Math.atan(y / x));
		ang -= 90.0f;
		if (x < 0.0f)
			ang -= 180.0f;
		ang = Math.abs(ang);
		   return ang;
	}
	
	final public float  getMagnitude(float x, float y){
		return (float) Math.sqrt((x * x) + (y * y));
	}
	
	protected void processJoystickInput(MotionEvent event, int historyPos){
	 
		int ways = mm.getPrefsHelper().getStickWays();
		if(ways==-1)ways = Emulator.getValue(Emulator.NUMWAYS);
		boolean b = Emulator.isInMAME() && Emulator.getValue(Emulator.IN_MENU)==0;
		
		int dev = getDevice(event.getDevice());
		int joy = dev!= -1 ? dev : 0;
	    
	    newinput[joy] = 0;
	    
	    float deadZone = 0.2f;
	    
		switch(mm.getPrefsHelper().getGamepadDZ())
	    {
	       case 1: deadZone = 0.01f;break;
	       case 2: deadZone = 0.15f;break;
	       case 3: deadZone = 0.2f;break;
	       case 4: deadZone = 0.3f;break;
	       case 5: deadZone = 0.5f;break;
	    }
		
		//System.out.println("DEAD ZONE IS "+deadZone);
	    
	    float x = 0.0f;
	    float y = 0.0f;
	    float mag = 0.0f;
		
	    for(int i= 0; i < 2; i++)
	    {
			if(i==0)
			{
				x = getAxisValue(MotionEvent.AXIS_X, event, historyPos );
				y = getAxisValue(MotionEvent.AXIS_Y, event, historyPos );
			}
			else
			{
				x = getAxisValue(MotionEvent.AXIS_HAT_X, event, historyPos );
				y = getAxisValue(MotionEvent.AXIS_HAT_Y, event, historyPos );
			}
	    	
			mag =  getMagnitude(x,y);	
			
	    	if(mag>=deadZone)
			{
				if(i==0)
	    		   Emulator.setAnalogData(joy,x,y * -1.0f);
							
		 		float v =  getAngle(x,y);
		 		
		 		if(ways==2 && b)
		 		{
		            if ( v < 180  ){
		                newinput[joy] |= RIGHT_VALUE;					
		 			}
		 			else if ( v >= 180  ){
		 				newinput[joy] |= LEFT_VALUE;
		 			}
		 		}
		 		else if(ways==4 || !b)
		 		{
		 			if( v >= 315 || v < 45){
		 				newinput[joy] |= DOWN_VALUE;	
		 			}
		 			else if ( v >= 45 && v < 135){
		 				newinput[joy] |= RIGHT_VALUE;						
		 			}
		 			else if ( v >= 135 && v < 225){
		 				newinput[joy] |= UP_VALUE;
		 			}
		 			else if ( v >= 225 && v < 315 ){
		 				newinput[joy] |= LEFT_VALUE;
		 			}						
		 		}
		        else
		        {
		 			if( v >= 330 || v < 30){
		 				newinput[joy] |= DOWN_VALUE;						
		 			}
		 			else if ( v >= 30 && v <60  )  {
		 				newinput[joy] |= DOWN_VALUE;
		 				newinput[joy] |= RIGHT_VALUE;						
		 			}
		 			else if ( v >= 60 && v < 120  ){
		 				newinput[joy] |= RIGHT_VALUE;						
		 			}
		 			else if ( v >= 120 && v < 150  ){
		 				newinput[joy] |= RIGHT_VALUE;
		 				newinput[joy] |= UP_VALUE;
		 			}
		 			else if ( v >= 150 && v < 210  ){
		 				newinput[joy] |= UP_VALUE;
		 			}
		 			else if ( v >= 210 && v < 240  ){
		 				newinput[joy] |= UP_VALUE;
		 				newinput[joy] |= LEFT_VALUE;						
		 			}
		 			else if ( v >= 240 && v < 300  ){
		 				newinput[joy] |= LEFT_VALUE;
		 			}
		 			else if ( v >= 300 && v < 330  ){
		 				newinput[joy] |= LEFT_VALUE;
		 				newinput[joy] |= DOWN_VALUE;
		 			}
		        }
			}
			else
			{
				if(i==0)
				   Emulator.setAnalogData(joy,0,0);
			}
	    }
	    
	    x = getAxisValue(MotionEvent.AXIS_Z, event, historyPos );
	    y = getAxisValue(MotionEvent.AXIS_RZ, event, historyPos ) * -1;
	    
		mag =  getMagnitude(x,y);	
		
		if(mag>=deadZone)
		{
	 		float v =  getAngle(x,y);
	 		
			if( v >= 330 || v < 30){
	        	newinput[joy] |= Y_VALUE;
	        }
	        else if ( v >= 30 && v <60  )  {
	        	newinput[joy] |= Y_VALUE;newinput[joy] |= B_VALUE;
	        }
	        else if ( v >= 60 && v < 120  ){
	        	newinput[joy] |= B_VALUE;
	        }
	        else if ( v >= 120 && v < 150  ){
	        	newinput[joy] |= B_VALUE;newinput[joy] |= X_VALUE;
	        }
	        else if ( v >= 150 && v < 210  ){
	        	newinput[joy] |= X_VALUE;
	        }
	        else if ( v >= 210 && v < 240  ){
	        	newinput[joy] |= X_VALUE;newinput[joy] |= A_VALUE;
	        }
	        else if ( v >= 240 && v < 300  ){
	        	newinput[joy] |= A_VALUE;
	        }
	        else if ( v >= 300 && v < 330  ){
	        	newinput[joy] |= A_VALUE;newinput[joy] |= Y_VALUE;
	        }
		}
		
	    x = getAxisValue(MotionEvent.AXIS_LTRIGGER, event, historyPos );
	    //System.out.println("x:"+x);
	    if(x>=0.25f)
	    {
	    	newinput[joy] |= L1_VALUE;
	    }
	    y = getAxisValue(MotionEvent.AXIS_RTRIGGER, event, historyPos );
	    //System.out.println("y:"+y);
	    if(y>=0.25f)
	    {
	    	newinput[joy] |= R1_VALUE;
	    }    
		
		pad_data[joy] &= ~ (oldinput[joy] & ~newinput[joy]);
		pad_data[joy] |= newinput[joy];
		
		Emulator.setPadData(joy,pad_data[joy]);
		
		oldinput[joy] = newinput[joy];
	}
	
	public boolean onKey(View vw, int keyCode, KeyEvent event) {
		
	  
	  if(ControlCustomizer.isEnabled())
	  {
			 if(keyCode == KeyEvent.KEYCODE_BACK)
			 {	 
				 mm.showDialog(DialogHelper.DIALOG_FINISH_CUSTOM_LAYOUT);
			 }	 
			 return true;
	   }
         
	   if(mm.getPrefsHelper().getInputExternal() == PrefsHelper.PREF_INPUT_ICADE || mm.getPrefsHelper().getInputExternal() == PrefsHelper.PREF_INPUT_ICP)
	   {	 
			this.handleIcade(event);
			return true;
	    }
				
		int dev = getDevice(event.getDevice());
		
		//System.out.println(event.getDevice().getName()+" "+dev+" "+" "+event.getKeyCode());
		//System.out.println("IME:"+Settings.Secure.getString(mm.getContentResolver(), Settings.Secure.DEFAULT_INPUT_METHOD));
		
		if(dev==-1)
		{
			if(isShield && event.getKeyCode()==KeyEvent.KEYCODE_BACK)
			{
				handlePADKey(10, event);
				return true;
			}
			
			return  super.onKey(vw, keyCode, event);
		}
		
		int v = deviceMappings[event.getKeyCode()][dev];
		
		if(v != -1)
		{
		    if(v==L2_VALUE)
		    { 
			    if(event.getAction()==KeyEvent.ACTION_UP)
			    {
			    	if(Emulator.getValue(Emulator.IN_MENU)!=0)
				    {
				        Emulator.setValue(Emulator.EXIT_GAME_KEY, 1);		    	
				    	try {Thread.sleep(100);} catch (InterruptedException e) {}
						Emulator.setValue(Emulator.EXIT_GAME_KEY, 0);									    	
				    }	    	
				    else if(!Emulator.isInMAME())
					{	
					   mm.showDialog(DialogHelper.DIALOG_EXIT);
					}  
			        else
			        {
			           if(mm.getPrefsHelper().isWarnOnExit())
			        	  mm.showDialog(DialogHelper.DIALOG_EXIT_GAME);
			           else
			           {
					        Emulator.setValue(Emulator.EXIT_GAME_KEY, 1);		    	
					    	try {Thread.sleep(100);} catch (InterruptedException e) {}
							Emulator.setValue(Emulator.EXIT_GAME_KEY, 0);			        	   
			           }
			        }
			    }
			}
			else if(v==R2_VALUE)
			{
				if( event.getAction()==KeyEvent.ACTION_UP) 
				    mm.showDialog(DialogHelper.DIALOG_OPTIONS);
			}
			else
			{
				int action = event.getAction();
				if(action == KeyEvent.ACTION_DOWN)
					pad_data[dev] |= v;
				else if(action == KeyEvent.ACTION_UP)
					pad_data[dev] &= ~ v;
				Emulator.setPadData(dev,pad_data[dev]);
			}
			return true;			
		}

		return false;
	}
	
	public void setInputListeners(){ 
		
		super.setInputListeners();
		                
		mm.getEmuView().setOnGenericMotionListener(this);
		mm.getInputView().setOnGenericMotionListener(this);
	}
	
	protected int getDevice(InputDevice device){
		
		if(mm.getPrefsHelper().getInputExternal() != PrefsHelper.PREF_INPUT_USB_AUTO)
		{
			return -1;
		}
		
		if(device==null)
			return -1;
			
		for(int i=0; i<numDevs; i++)
		{
			if(deviceIDs[i]==device.getId())
				return i;
		}
		
		return detectDevice(device);
	}
	
	protected void mapDPAD(){
		deviceMappings[KeyEvent.KEYCODE_DPAD_UP][numDevs] = UP_VALUE;
		deviceMappings[KeyEvent.KEYCODE_DPAD_DOWN][numDevs] = DOWN_VALUE;
		deviceMappings[KeyEvent.KEYCODE_DPAD_LEFT][numDevs] = LEFT_VALUE;
		deviceMappings[KeyEvent.KEYCODE_DPAD_RIGHT][numDevs] = RIGHT_VALUE;		
	}
	
	protected void mapL1R1(){
		if(mm.getPrefsHelper().getAutomapOptions() == PrefsHelper.PREF_AUTOMAP_L1L2_AS_L2R2)
		{
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = R2_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = L2_VALUE;			
		}
		else if(mm.getPrefsHelper().getAutomapOptions() == PrefsHelper.PREF_AUTOMAP_L1L2_AS_SELECTSTART)
		{
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = START_VALUE;			
		}
		else
		{
		   deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = L1_VALUE;
		   deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = R1_VALUE;
		}
	}
	
	protected void mapTHUMBS(){
		if(mm.getPrefsHelper().getAutomapOptions() == PrefsHelper.PREF_AUTOMAP_THUMBS_AS_L2R2)
		{
		   deviceMappings[KeyEvent.KEYCODE_BUTTON_THUMBL][numDevs] = R2_VALUE;
		   deviceMappings[KeyEvent.KEYCODE_BUTTON_THUMBR] [numDevs]= L2_VALUE;
		}
		else if(mm.getPrefsHelper().getAutomapOptions() == PrefsHelper.PREF_AUTOMAP_THUMBS_AS_SELECTSTART){
		   deviceMappings[KeyEvent.KEYCODE_BUTTON_THUMBL][numDevs] = SELECT_VALUE;
		   deviceMappings[KeyEvent.KEYCODE_BUTTON_THUMBR] [numDevs]= START_VALUE;			
		}		
	}
	
	protected void mapSelectStart(){
		deviceMappings[KeyEvent.KEYCODE_BUTTON_SELECT][numDevs] = SELECT_VALUE;
		deviceMappings[KeyEvent.KEYCODE_BUTTON_START][numDevs] = START_VALUE;	
	}
	
	
	protected int detectDevice(InputDevice device){
	
		boolean  detected = false;
						 
		if(numDevs==MAX_DEVICES )
			return -1;
		
		if(device==null || banDev == null)
			return -1;
		
		if(banDev.get(device.getId())==1)
		   return -1;
			        
		String name = device.getName();
		
		CharSequence desc = "";
				
		if(name.indexOf("PLAYSTATION(R)3")!=-1 || name.indexOf("Dualshock3")!=-1 
		   || name.indexOf("Sixaxis")!=-1 || name.indexOf("Gasia,Co")!=-1
			){
									
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = Y_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = B_VALUE;
			
			mapDPAD();mapL1R1();mapTHUMBS();mapSelectStart();
			
			desc = "Sixaxis";
			
			detected = true;
		}
		else if(name.indexOf("Gamepad 0")!=-1 || name.indexOf("Gamepad 1")!=-1 //Sixaxis Controller
				|| name.indexOf("Gamepad 1")!=-1 || name.indexOf("Gamepad 2")!=-1){
								
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = Y_VALUE;
						
			mapDPAD();mapL1R1();mapTHUMBS();mapSelectStart();
			
			detected = true;
		}
		else if(name.indexOf("nvidia_joypad")!=-1 ) {
								
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = Y_VALUE;
			
			mapL1R1();mapTHUMBS();
			
			deviceMappings[KeyEvent.KEYCODE_BACK][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_START] [numDevs]= START_VALUE;
			isShield = true;			
			detected = true;
			
			desc = "NVIDIA Shield";
		}
		else if (name.indexOf("X-Box 360")!=-1 || name.indexOf("X-Box")!=-1 
				   || name.indexOf("Xbox 360 Wireless Receiver")!=-1 ){
			

			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = Y_VALUE;

			mapDPAD();mapL1R1();mapTHUMBS();mapSelectStart();
			
			desc = "XBox";
			
			detected = true;			
		}
		else if (name.indexOf("Logitech")!=-1 && name.indexOf("Dual Action")!=-1){
		
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = Y_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = B_VALUE;
			
			mapL1R1();mapTHUMBS();mapSelectStart();
	        
			desc = "Dual Action";
			
			detected = true;
		}
		else if (name.indexOf("Logitech")!=-1 && name.indexOf("RumblePad 2")!=-1){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_2][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_1][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_3][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_4][numDevs] = Y_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_9][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_10][numDevs] = START_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_5][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_6][numDevs] = R1_VALUE;   
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_11][numDevs] = R2_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_12][numDevs] = L2_VALUE; 
			
			desc = "Rumblepad 2";
	            
			detected = true;	
			
		}		
		else if (name.indexOf("Logitech")!=-1 && name.indexOf("Precision")!=-1){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_2][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_1][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_3][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_4][numDevs] = Y_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_5][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_6][numDevs] = R1_VALUE;   
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_7][numDevs] = R2_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_8][numDevs] = L2_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_9][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_10][numDevs] = START_VALUE;
			
			desc = "Logitech Precision";
		    
			detected = true;
		}
		else if (name.indexOf("TTT THT Arcade console 2P USB Play")!=-1){
		
			deviceMappings[KeyEvent.KEYCODE_BUTTON_1][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_2][numDevs] = Y_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_5][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_6][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_3][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_7][numDevs] = R1_VALUE;  			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_4][numDevs] = R2_VALUE;		
			deviceMappings[KeyEvent.KEYCODE_BUTTON_8][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_9][numDevs] = START_VALUE;
			
			desc = "TTT THT Arcade";
			
			detected = true;
		}
		else if (name.indexOf("TOMMO NEOGEOX Arcade Stick")!=-1){
			
			mapDPAD();
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_C][numDevs] = Y_VALUE;
					
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R2][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L2][numDevs] = START_VALUE;
			
			desc = "TOMMO Neogeo X Arcade";
			
			detected = true;
		}
		else if (name.indexOf("Onlive Wireless Controller")!=-1){
			
			mapDPAD();
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = Y_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = B_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = R1_VALUE;  			
	
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BACK][numDevs] = START_VALUE;
			
			desc = "Onlive Wireless";
			
			detected = true;
		}
		else if (name.indexOf("MadCatz")!=-1 && name.indexOf("PC USB Wired Stick")!=-1){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_C][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = Y_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Z][numDevs] = L1_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = R1_VALUE;   
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L2][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R2][numDevs] = START_VALUE;
			
			desc = "Madcatz PC USB Stick";
			
			detected = true;
		}
		else if (name.indexOf("Logicool")!=-1 && name.indexOf("RumblePad 2")!=-1){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_C][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = Y_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = A_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Z][numDevs] = R1_VALUE;   
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = R2_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = L2_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L2][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R2][numDevs] = START_VALUE;
			
			desc = "Logicool Rumblepad 2";
					    
			detected = true;
		}	
		else if (name.indexOf("Zeemote")!=-1 && name.indexOf("Steelseries free")!=-1){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = Y_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = A_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_MODE][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_START][numDevs] = START_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = R1_VALUE;   
	        
			desc = "Zeemote Steelseries";
			
			detected = true;				
		}			
		else if (name.indexOf("HuiJia  USB GamePad")!=-1){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_3][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_4][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_2][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_1][numDevs] = Y_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_7][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_8][numDevs] = R1_VALUE;   
		
			deviceMappings[KeyEvent.KEYCODE_BUTTON_9][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_10][numDevs] = START_VALUE;
			
			desc = "Huijia USB SNES";
				    
			detected = true;
		}	
		else if (name.indexOf("Smartjoy Family Super Smartjoy 2")!=-1){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_3][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_4][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_2][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_1][numDevs] = Y_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_7][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_8][numDevs] = R1_VALUE;   
		
			deviceMappings[KeyEvent.KEYCODE_BUTTON_5][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_6][numDevs] = START_VALUE;
			
			desc = "Super Smartjoy";
			
			detected = true;
		}	
		else if (name.indexOf("Jess Tech Dual Analog Rumble Pad")!=-1){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_3][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_1][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_4][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_2][numDevs] = Y_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_5][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_7][numDevs] = R1_VALUE;   
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_6][numDevs] = R2_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_8][numDevs] = L2_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_11][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_12][numDevs] = START_VALUE;
			
			//desc = "Super Smartjoy";
					    
			detected = true;
		}	
		else if (name.indexOf("Microsoft")!=-1 && name.indexOf("Dual Strike")!=-1){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_4][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_2][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_3][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_1][numDevs] = Y_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_7][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_8][numDevs] = R1_VALUE;   
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_9][numDevs] = R2_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_6][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_5][numDevs] = START_VALUE;
		    	
			desc = "MS Dual Strike";
			
			detected = true;
		}
		else if (name.indexOf("Microsoft")!=-1 && name.indexOf("SideWinder")!=-1){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = Y_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = R1_VALUE;   
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Z][numDevs] = R2_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_C][numDevs] = L2_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_11][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_12][numDevs] = START_VALUE;

			desc = "MS Sidewinder";
			
			detected = true;
		}	
		else if (name.indexOf("WiseGroup")!=-1 && 
				(name.indexOf("JC-PS102U")!=-1 || name.indexOf("TigerGame")!=-1) || 
				 name.indexOf("Game Controller Adapter")!=-1 || name.indexOf("Dual USB Joypad")!=-1 ||
				 name.indexOf("Twin USB Joystick")!=-1 
				){
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_13][numDevs] = UP_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_15][numDevs] = DOWN_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_16][numDevs] = LEFT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_14][numDevs] = RIGHT_VALUE;		
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_4][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_1][numDevs] = Y_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_3][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_2][numDevs] = B_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_7][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_8][numDevs] = R1_VALUE;   
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_5][numDevs] = R2_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_6][numDevs] = L2_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_10][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_9][numDevs] = START_VALUE;
			
			desc = "PlayStation2";
             		
			detected = true;
		}
		else if (name.indexOf("MOGA")!=-1){
			
			mapDPAD();
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = Y_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = R1_VALUE;   
						
			deviceMappings[KeyEvent.KEYCODE_BUTTON_SELECT][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_START][numDevs] = START_VALUE;
			
			desc = "MOGA";
			
			detected = true;
		}
		else if (name.indexOf("OUYA Game Controller")!=-1){
			
			mapDPAD();
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = Y_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = B_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L1][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = R1_VALUE;   
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_THUMBL][numDevs] = R2_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_THUMBR][numDevs] = L2_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L2][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R2][numDevs] = START_VALUE;
			
			desc = "OUYA";
			
			detected = true;
		}	
		else if (name.indexOf("DragonRise")!=-1){
			
			mapDPAD();
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_2][numDevs] = B_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_3][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_4][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_1][numDevs] = Y_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_5][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_6][numDevs] = R1_VALUE;   
						
			deviceMappings[KeyEvent.KEYCODE_BUTTON_7][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_8][numDevs] = START_VALUE;
				
			desc = "DragonRise";
			
			detected = true;
		}
		else if (name.indexOf("Thrustmaster T Mini")!=-1){
			
			mapDPAD();
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_A][numDevs] = A_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_X][numDevs] = Y_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_B][numDevs] = X_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_C][numDevs] = B_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Y][numDevs] = L1_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_Z][numDevs] = R1_VALUE;   
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L2][numDevs] = R2_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R1][numDevs] = L2_VALUE;
			
			deviceMappings[KeyEvent.KEYCODE_BUTTON_R2][numDevs] = SELECT_VALUE;
			deviceMappings[KeyEvent.KEYCODE_BUTTON_L2][numDevs] = START_VALUE;
			
			desc = "Thrustmaster T Mini";
			
			detected = true;
		}			
		
		//JOYPAD_B = X_VALUE
		//JOYPAD_Y = A_VALUE
		//JOYPAD_A = B_VALUE
		//JOYPAD_X = Y_VALUE

		if(detected)
		{
			System.out.println("Controller detected: "+device.getName());
			deviceIDs[numDevs] = device.getId();
			numDevs++;
			if(numDevs == 1)
			   mm.getMainHelper().updateMAME4droid();	
			
		    CharSequence text = "Detected "+desc +  " GamePad as P"+numDevs;
		    int duration = Toast.LENGTH_SHORT;

		    Toast toast = Toast.makeText(mm, text, duration);
		    toast.show();
			
			return numDevs-1;
		}
		else
		{
			banDev.append(device.getId(), 1);
		}
		
		return -1;
	}

	public boolean isControllerDevice(){
		   return numDevs!=0 || iCade;
	}
}
