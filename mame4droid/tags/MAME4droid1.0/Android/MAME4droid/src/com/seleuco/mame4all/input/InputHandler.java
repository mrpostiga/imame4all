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

package com.seleuco.mame4all.input;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

import android.content.res.Configuration;
import android.graphics.Rect;
import android.os.Handler;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnKeyListener;
import android.view.View.OnTouchListener;

import com.seleuco.mame4all.Emulator;
import com.seleuco.mame4all.MAME4all;
import com.seleuco.mame4all.helpers.DialogHelper;

public class InputHandler implements OnTouchListener, OnKeyListener, IController{
	
	protected static final int[] emulatorInputValues = {
		UP_VALUE,DOWN_VALUE,LEFT_VALUE,RIGHT_VALUE, B_VALUE, X_VALUE, A_VALUE, Y_VALUE, L1_VALUE, R1_VALUE, SELECT_VALUE, START_VALUE
	};
		
	public static int[] defaultKeyMapping = {
		KeyEvent.KEYCODE_DPAD_UP,KeyEvent.KEYCODE_DPAD_DOWN,KeyEvent.KEYCODE_DPAD_LEFT,KeyEvent.KEYCODE_DPAD_RIGHT,
		KeyEvent.KEYCODE_DPAD_CENTER,KeyEvent.KEYCODE_SEARCH,-1,-1,-1,-1,-1,KeyEvent.KEYCODE_BACK
	};
			
	public static int[] keyMapping = new int[emulatorInputValues.length];
	
	protected float dx;
	protected float dy;
				
	protected ArrayList<InputValue> values = new ArrayList<InputValue>();
	
	protected long pad_data = 0;
	
	protected int newtouch;
	protected int oldtouch;
	protected boolean touchstate;

	
	protected  int trackballSensitivity = 30;
	protected  boolean trackballEnabled = true;
		
	/////////////////
	
	final public static int STATE_SHOWING_CONTROLLER = 1;
	final public static int STATE_SHOWING_NONE = 3;
	
	protected int state = STATE_SHOWING_CONTROLLER;
	
	final public static int TYPE_MAIN_RECT = 1;
	final public static int TYPE_STICK_RECT = 2;
	final public static int TYPE_BUTTON_RECT = 3;
	final public static int TYPE_STICK_IMG = 4;
	final public static int TYPE_BUTTON_IMG = 5;
	final public static int TYPE_SWITCH  = 6;
	final public static int TYPE_OPACITY = 7;
	
	
	protected int stick_state;
	public int getStick_state() {
		return stick_state;
	}

	protected int old_stick_state;

	protected int btnStates[] = new int[NUM_BUTTONS];
	public int[] getBtnStates() {
		return btnStates;
	}

	protected int old_btnStates[] = new int[NUM_BUTTONS];
	
	protected MAME4all mm = null;
	
	//protected Timer timer = new Timer();
	
	protected Handler handler = new Handler();
		
	protected Object lock = new Object();
	
	protected Runnable finishTrackBallMove = new Runnable(){
			//@Override
		    public void run() {
		    	//synchronized(lock){
		    	  //System.out.println("---> INIT C");	
		    	  //System.out.println("+CLEAR Set Pad "+pad_data+ " new:"+newtrack+" old:"+oldtrack);
		    	  //pad_data &= ~oldtrack;	
		    	  pad_data &= ~UP_VALUE;
		    	  pad_data &= ~DOWN_VALUE;
		    	  pad_data &= ~LEFT_VALUE;
		    	  pad_data &= ~RIGHT_VALUE;
				  Emulator.setPadData(pad_data);

				  //System.out.println("++CLEAR Set Pad "+pad_data+ " new:"+newtrack+" old:"+oldtrack);
				  //System.out.println("---> CLEAR");
		    	//}
		}};	
		
	public InputHandler(MAME4all value){
		
		mm = value;
				
		if(mm.getMainHelper().getscrOrientation() == Configuration.ORIENTATION_LANDSCAPE)
		{
			state = mm.getPrefsHelper().isLandscapeTouchController() ? STATE_SHOWING_CONTROLLER : STATE_SHOWING_NONE;
		}
		else
		{
			state = mm.getPrefsHelper().isPortraitTouchController() ? STATE_SHOWING_CONTROLLER : STATE_SHOWING_NONE;
		}
		
		stick_state = old_stick_state = STICK_NONE;
		for(int i=0; i<NUM_BUTTONS; i++)
			btnStates[i] = old_btnStates[i] = BTN_NO_PRESS_STATE;
	}
	
	public int setInputHandlerState(int value){
		return state = value;
	}
	
	public int getInputHandlerState(){
		return state;
	}
	
	public void changeState(){
		
						                  
		boolean isTouchController = mm.getMainHelper().getscrOrientation() == Configuration.ORIENTATION_PORTRAIT ?
				                    mm.getPrefsHelper().isPortraitTouchController():
				                    mm.getPrefsHelper().isLandscapeTouchController();
		
	    if(state == STATE_SHOWING_CONTROLLER)
	    {				    	
	    	pad_data = 0;
	    	Emulator.setPadData(pad_data);
	    	
	    	state = STATE_SHOWING_NONE;		    				    	
	    }
	    else
	    {
	    	if(isTouchController)
	    	    state = STATE_SHOWING_CONTROLLER;
	    }	    	    	
	}
	
	public void setTrackballSensitivity(int trackballSensitivity) {
		this.trackballSensitivity = trackballSensitivity;
	}
	
	public void setTrackballEnabled(boolean trackballEnabled) {
		this.trackballEnabled = trackballEnabled;
	}
	
	public void setFixFactor(float dx, float dy){
		this.dx = dx;
		this.dy = dy;
		fixControllerCoords(values);
	}
	
	protected boolean setPadData(KeyEvent event, int data){
		int action = event.getAction();
		if(action == KeyEvent.ACTION_DOWN)
			pad_data |= data;
		else if(action == KeyEvent.ACTION_UP)
			pad_data &= ~ data;
		return true;
	}
	
	protected boolean handlePADKey(int value, KeyEvent event){
				
		setPadData(event,emulatorInputValues[value]);
		
		Emulator.setPadData(pad_data);
   		
		return true;		
	}
			
	public boolean onKey(View v, int keyCode, KeyEvent event) {
		//Log.d("JAVA", "onKeyDown=" + keyCode + " " + keyCode + " " + event.getDisplayLabel() + " " + event.getUnicodeChar() + " " + event.getNumber());
          
		 int value = -1;
		 for(int i=0; i<keyMapping.length; i++)
			 if(keyMapping[i]==keyCode)
				 value = i;
		  
         if(value >=0 && value <=11)
		     if(handlePADKey(value, event))return true;
            
         return false;
	}
	
	public void handleVirtualKey(int action){
		
		pad_data |= action;
		Emulator.setPadData(pad_data);
		
		try {
			Thread.sleep(150);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		pad_data &= ~ action;
		Emulator.setPadData(pad_data);
		
	}
	
	//debug method
	public ArrayList<InputValue> getAllInputData(){
		if(state == STATE_SHOWING_CONTROLLER)
			return values;
		else
			return null;			    
	}
	
	public Rect getMainRect(){
		if(values==null)
		   return null;
		for(int i = 0; i <values.size();i++)
		{	
			if(values.get(i).getType()==TYPE_MAIN_RECT)
				return values.get(i).getOrigRect();
		}		
		return null;	
	}
	
	/*
	protected boolean handleTouchController(MotionEvent event){
		boolean b = false;
		
		if(event.getAction() == MotionEvent.ACTION_DOWN || event.getAction() == MotionEvent.ACTION_MOVE)
		{
		   //int x = (int)event.getRawX();
		   //int y = (int)event.getRawY();
		   
		   int x = (int)event.getX();
		   int y = (int)event.getY();
		   
		   for(int i =0; i< values.size();i++)
		   {
			   InputValue iv = values.get(i);
			   
			   if(iv.getRect().contains(x, y))
			   {	
				   if(iv.getType()==TYPE_ACTION)
				   {	 
				       pad_data |= getButtonValue(iv.getValue());				  
				       b =  true;//NO MULTITOUCH (SIC)
				  }
				  else if(iv.getType()==TYPE_SWITCH)
				  {					  
					  changeState();
					  mm.getMainHelper().updateViews();
					  return true;
				  }		
			   }				   
		   }	   		   
		}   
		else
		{
			pad_data = 0; b = true;
		}
		
		if(b)
	       Emulator.setPadData(pad_data);
		
        return b;
		
	}
	*/
	
	protected void handleImageStates(){
		
		if(!mm.getPrefsHelper().isAnimatedInput())
		   return;
		
	    switch ((int)pad_data & (UP_VALUE|DOWN_VALUE|LEFT_VALUE|RIGHT_VALUE))
	    {
	        case    UP_VALUE:    stick_state = STICK_UP; break;
	        case    DOWN_VALUE:  stick_state = STICK_DOWN; break;
	        case    LEFT_VALUE:  stick_state = STICK_LEFT; break;
	        case    RIGHT_VALUE: stick_state = STICK_RIGHT; break;
	            
	        case    UP_VALUE | LEFT_VALUE:  stick_state = STICK_UP_LEFT; break;
	        case    UP_VALUE | RIGHT_VALUE: stick_state = STICK_UP_RIGHT; break;
	        case    DOWN_VALUE | LEFT_VALUE:  stick_state = STICK_DOWN_LEFT; break;
	        case    DOWN_VALUE | RIGHT_VALUE: stick_state = STICK_DOWN_RIGHT; break;
	            
	        default: stick_state = STICK_NONE;
	    }
			
		for (int j = 0; j < values.size(); j++) {
			InputValue iv = values.get(j);
			if(iv.getType()==TYPE_STICK_IMG)
			{
				if(stick_state != old_stick_state)
				{
					mm.getInputView().invalidate(iv.getRect());
					old_stick_state = stick_state;
				}
			}
			else if(iv.getType()==TYPE_BUTTON_IMG)
			{
				int i = iv.getValue();
				
				btnStates[i] = (pad_data & getButtonValue(i,false)) !=0 ? BTN_PRESS_STATE: BTN_NO_PRESS_STATE;
				
				if(btnStates[iv.getValue()]!=old_btnStates[iv.getValue()])
			    {
			    	mm.getInputView().invalidate(iv.getRect());
			    	old_btnStates[iv.getValue()] = btnStates[iv.getValue()]; 
			    }
			}							
		}
	}

	protected boolean handleTouchController(MotionEvent event) {

		int action = event.getAction();
		
		oldtouch = newtouch;
				
		int x = (int) event.getX();
		int y = (int) event.getY();

		if (action == MotionEvent.ACTION_UP || action == MotionEvent.ACTION_CANCEL) {
			touchstate = false;
			
		} else {

			touchstate = true;

			for (int j = 0; j < values.size(); j++) {
				InputValue iv = values.get(j);

				if (iv.getRect().contains(x, y)) {

					if (iv.getType() == TYPE_BUTTON_RECT || iv.getType() == TYPE_STICK_RECT) {

						switch (action) {

						case MotionEvent.ACTION_DOWN:
						case MotionEvent.ACTION_POINTER_DOWN://ESTO NO ESTA en 1.6
						case MotionEvent.ACTION_MOVE:
							
							if(iv.getType() == TYPE_BUTTON_RECT)
							{	
							   newtouch = getButtonValue(iv.getValue(),true);
								 
							   if(iv.getValue()==BTN_L2)
								{ 
								    if(!Emulator.isInMAME())
									    mm.showDialog(DialogHelper.DIALOG_EXIT);
								    else
								        mm.showDialog(DialogHelper.DIALOG_EXIT_GAME);
								}
								else if(iv.getValue()==BTN_R2)
								{
									 mm.showDialog(DialogHelper.DIALOG_OPTIONS);
								}
							}   
							else
							{	
							   newtouch = getStickValue(iv.getValue());

							}   
							
							if (oldtouch != newtouch) 
								pad_data &= ~oldtouch;							
							pad_data |= newtouch ;
						}
						break;
					} 
                   else if (iv.getType() == TYPE_SWITCH) {
						if (event.getAction() == MotionEvent.ACTION_DOWN) {
							touchstate = false;
							oldtouch = 0;
							changeState();
							mm.getMainHelper().updateMAME4all();
							return true;
						}
					}
				}
			}			
		}

		if (!touchstate) {

			pad_data &= ~oldtouch;
			newtouch = 0;
			oldtouch = 0;
		}

		handleImageStates();
		
		Emulator.setPadData(pad_data);
		
		return true;
	}
	
	public boolean onTouch(View v, MotionEvent event) {
		
		//System.out.println(event.getRawX()+" "+event.getX()+" "+event.getRawY()+" "+event.getY());
		
        if(v == mm.getInputView())
		{
		    if(state == STATE_SHOWING_CONTROLLER)
		    {	
		    	 return handleTouchController(event);
		    }
		    return false;
		}
        else
        {
			if(mm.getMainHelper().getscrOrientation() == Configuration.ORIENTATION_PORTRAIT && state != STATE_SHOWING_NONE)
				return false;
			if(mm.getMainHelper().getscrOrientation() == Configuration.ORIENTATION_LANDSCAPE && state != STATE_SHOWING_NONE)
				return false;
	    	mm.showDialog(DialogHelper.DIALOG_FULLSCREEN);
			return true;
        }
	}

	public boolean onTrackballEvent(MotionEvent event) {

		int gap = 0;

		if(!trackballEnabled)return false;
		
		int action = event.getAction();

		if (action == MotionEvent.ACTION_MOVE /*&& trackballEnabled*/) {

			int newtrack = 0;

			final float x = event.getX();
			final float y = event.getY();

			//float d = Math.max(Math.abs(x), Math.abs(y));

			// System.out.println("x: "+x+" y:"+y);

			if (y < -gap) {
				newtrack |= UP_VALUE;
				// System.out.println("Up");
			} else if (y > gap) {
				newtrack |= DOWN_VALUE;
				// System.out.println("Down");
			}

			if (x < -gap) {
				newtrack |= LEFT_VALUE;
				// System.out.println("left");
			} else if (x > gap) {
				newtrack |= RIGHT_VALUE;
				// System.out.println("right");
			}

			// System.out.println("Set Pad "+pad_data+
			// " new:"+newtrack+" old:"+oldtrack);

			handler.removeCallbacks(finishTrackBallMove);
			handler.postDelayed(finishTrackBallMove, (int) (/* 50 * d */150 * trackballSensitivity));// TODO
			
			if (newtrack != 0) {
				pad_data &= ~UP_VALUE;
				pad_data &= ~DOWN_VALUE;
				pad_data &= ~LEFT_VALUE;
				pad_data &= ~RIGHT_VALUE;
				pad_data |= newtrack;
			}

		} else if (action == MotionEvent.ACTION_DOWN) {
			pad_data |= B_VALUE;

		} else if (action == MotionEvent.ACTION_UP) {
			pad_data &= ~B_VALUE;
		}

		Emulator.setPadData(pad_data);

		return true;
	}
		
	protected void fixControllerCoords(ArrayList<InputValue> values) {

		if (values != null) {
			for (int i = 0; i < values.size(); i++) {

				Rect r = values.get(i).newFixedRect();
				if (r != null) {
					/*
					if(mm.getMainHelper().getscrOrientation() == Configuration.ORIENTATION_PORTRAIT)
					{
						r.top -= 240;
					    r.bottom -= 240;
					}
					*/
					r.right = (int) (r.right * dx);
					r.left = (int) (r.left * dx);
					r.top = (int) (r.top * dy);
					r.bottom = (int) (r.bottom * dy);
					//values.get(i).setRect(r);
				}
			}
		}
	}
	
	public int getOpacity(){
		
		ArrayList<InputValue> data = null;
		if(state==STATE_SHOWING_CONTROLLER)
			data = values;
		else
			return -1;
		
		for(InputValue v : data)
		{
		   if(v.getType() == TYPE_OPACITY)
			   return v.getValue();
		}
		return -1;
	}
	
	public void readControllerValues(int v){
		readInputValues(v,values);
		fixControllerCoords(values);
	}
	
	protected void readInputValues(int id, ArrayList<InputValue> values)
	{
	     InputStream is = mm.getResources().openRawResource(id);
	     
	     InputStreamReader isr = new InputStreamReader(is);
	     BufferedReader br = new BufferedReader(isr);
	     
	     InputValue iv = null;
	     values.clear();
	     
	     int i=0;
	     try{
		     String s = br.readLine();
		     while(s!=null)
		     {
		    	 int [] data = new int[10]; 
		    	 StringTokenizer st = new StringTokenizer(s,",");
		    	    int j = 0;
		    		while(st.hasMoreTokens()){
		                String token = st.nextToken();
		                int k = token.indexOf("/");
		                if(k!=-1)
		                {
		                   token = token.substring(0, k);	
		                }
		                token = token.trim();
		                data[j] = Integer.parseInt(token);
		                j++;
		            }    	 
		    	 		    
                    //values.
		    		
		    	    s = br.readLine();i++;		    	    
		    	    if(j!=0)
		    	    {			    	       				    	    	
		    	       iv = new InputValue(data,mm);				    	    
		    	       values.add(iv);
		    	    }     
		     }	 
	     }catch(IOException e)
	     {
	    	 e.printStackTrace();
	     }
	}
	
	int getStickValue(int i){
		int ways = Emulator.getValue(Emulator.WAYS_STICK_KEY);
		boolean b = Emulator.isInMAME();
		
		if(ways==2 && b)
		{
			switch(i){
			   case 1: return   LEFT_VALUE;		   
			   case 3: return   RIGHT_VALUE;
			   case 4: return   LEFT_VALUE;
			   case 5: return   RIGHT_VALUE;
			   case 6: return   LEFT_VALUE;		   
			   case 8: return   RIGHT_VALUE;
			}	
		}
		else if(ways==4 && b)
		{
			switch(i){
			   case 1: return   LEFT_VALUE;		   
			   case 2: return   UP_VALUE;
			   case 3: return   RIGHT_VALUE;
			   case 4: return   LEFT_VALUE;
			   case 5: return   RIGHT_VALUE;
			   case 6: return   LEFT_VALUE;		   
			   case 7: return   DOWN_VALUE;
			   case 8: return   RIGHT_VALUE;
			}			
		}
		else
		{
			switch(i){
			   case 1: return   UP_VALUE | LEFT_VALUE;		   
			   case 2: return   UP_VALUE;
			   case 3: return   UP_VALUE | RIGHT_VALUE;
			   case 4: return   LEFT_VALUE;
			   case 5: return   RIGHT_VALUE;
			   case 6: return   DOWN_VALUE | LEFT_VALUE;		   
			   case 7: return   DOWN_VALUE;
			   case 8: return   DOWN_VALUE | RIGHT_VALUE;
			}
		}
		return 0;
	}
	
	int getButtonValue(int i, boolean b){
		switch(i){
		   case 0: return  Y_VALUE;		   
		   case 1:
			    if(Emulator.getValue(Emulator.BPLUSX_KEY)==1  && b)
			    {			    	
	                return X_VALUE | B_VALUE | A_VALUE;
                }
                else
                {
                	return  A_VALUE;
				}
		   case 2: return  B_VALUE;
		   case 3: return  X_VALUE;
		   
		   case 4: return  L1_VALUE;
		   case 5: return  R1_VALUE;   
		   case 6: return  L2_VALUE;
		   case 7: return  R2_VALUE;
		   
		   case 8: return  SELECT_VALUE;		   
		   case 9: return  START_VALUE;
		   
		   case 10: return  X_VALUE | A_VALUE;
		   case 11:
			    if(Emulator.getValue(Emulator.BPLUSX_KEY)==0 && Emulator.getValue(Emulator.LAND_BUTTONS_KEY)>=3)
			    {
			    	return X_VALUE | B_VALUE;
                }	
			    else
			    	return 0;
			    			    
		   case 12: return Y_VALUE | A_VALUE;
		   case 13: return Y_VALUE | B_VALUE;		   
		}
		return 0;
	}
	
	protected  void dumpEvent(MotionEvent event) {
		   String names[] = { "DOWN" , "UP" , "MOVE" , "CANCEL" , "OUTSIDE" ,
		      "POINTER_DOWN" , "POINTER_UP" , "7?" , "8?" , "9?" };
		   StringBuilder sb = new StringBuilder();
		   int action = event.getAction();
		   int actionCode = action & MotionEvent.ACTION_MASK;
		   sb.append("event ACTION_" ).append(names[actionCode]);
		   if (actionCode == MotionEvent.ACTION_POINTER_DOWN
		         || actionCode == MotionEvent.ACTION_POINTER_UP) {
		      sb.append("(pid " ).append(
		      //action >> MotionEvent.ACTION_POINTER_ID_SHIFT);
		      (action & MotionEvent.ACTION_POINTER_ID_MASK)>> MotionEvent.ACTION_POINTER_ID_SHIFT);		  
		      sb.append(")" );
		   }
		   sb.append("[" );
		   for (int i = 0; i < event.getPointerCount(); i++) {
		      sb.append("#" ).append(i);
		      sb.append("(pid " ).append(event.getPointerId(i));
		      sb.append(")=" ).append((int) event.getX(i));
		      sb.append("," ).append((int) event.getY(i));
		      if (i + 1 < event.getPointerCount())
		         sb.append(";" );
		   }
		   sb.append("]" );
		   Log.d("touch", sb.toString());
		}
}
