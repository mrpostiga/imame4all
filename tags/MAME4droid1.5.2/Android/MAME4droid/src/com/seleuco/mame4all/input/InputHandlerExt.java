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

import android.view.MotionEvent;

import com.seleuco.mame4all.Emulator;
import com.seleuco.mame4all.MAME4all;
import com.seleuco.mame4all.helpers.DialogHelper;
import com.seleuco.mame4all.helpers.PrefsHelper;

public class InputHandlerExt extends InputHandler {
	

	protected int [] touchContrData = new int[20];
	protected InputValue [] touchKeyData = new InputValue[20];
	
	protected static int [] newtouches = new int[20];
	protected static int [] oldtouches = new int[20];
	protected static boolean [] touchstates = new boolean[20];
	
	public InputHandlerExt(MAME4all value) {
		super(value);
	}
	
	
	@Override
	protected boolean handleTouchController(MotionEvent event) {

		int action = event.getAction();
		int actionEvent = action & MotionEvent.ACTION_MASK;
		
		int pid = 0;
				
        try
        {
		   int pointerIndex = (event.getAction() & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
           pid = event.getPointerId(pointerIndex);
        }
        catch(Error e)
        {
            pid = (action & MotionEvent.ACTION_POINTER_ID_SHIFT) >> MotionEvent.ACTION_POINTER_ID_SHIFT;
        }    
		
		//dumpEvent(event);
		
		for (int i = 0; i < 10; i++) 
		{
		    touchstates[i] = false;
		    oldtouches[i] = newtouches[i];
		}
		
		for (int i = 0; i < event.getPointerCount(); i++) {

			int actionPointerId = event.getPointerId(i);
						
			int x = (int) event.getX(i);
			int y = (int) event.getY(i);
			
			if(actionEvent == MotionEvent.ACTION_UP 
			   || (actionEvent == MotionEvent.ACTION_POINTER_UP && actionPointerId==pid) 
			   || actionEvent == MotionEvent.ACTION_CANCEL)
			{
                //nada
			}	
			else
			{		
				//int id = i;
				int id = actionPointerId;
				if(id>touchstates.length)continue;//strange but i have this error on my development console
				touchstates[id] = true;
				//newtouches[id] = 0;
				
				for (int j = 0; j < values.size(); j++) {
					InputValue iv = values.get(j);
										
					if (iv.getRect().contains(x, y)) {
						
						//Log.d("touch","HIT "+iv.getType()+" "+iv.getRect()+ " "+iv.getOrigRect());
						
						if (iv.getType() == TYPE_BUTTON_RECT || iv.getType() == TYPE_STICK_RECT) {
						
							switch (actionEvent) {
							
							case MotionEvent.ACTION_DOWN:
							case MotionEvent.ACTION_POINTER_DOWN:
							case MotionEvent.ACTION_MOVE:
															
								if(iv.getType() == TYPE_BUTTON_RECT)
								{	
								     newtouches[id] |= getButtonValue(iv.getValue(),true);
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
								else if(mm.getPrefsHelper().getControllerType() == PrefsHelper.PREF_DIGITAL
										&& !(TiltSensor.isEnabled() && Emulator.isInMAME()))
								{
									 newtouches[id] = getStickValue(iv.getValue());
								}
					            
								if(oldtouches[id] != newtouches[id])	            
					            	pad_data[0] &= ~(oldtouches[id]);
					            
								pad_data[0] |= newtouches[id];
							}
							if(Emulator.getValue(Emulator.BPLUSX_KEY)==1 && (iv.getValue()==BTN_B || iv.getValue()==BTN_X))
							   break;
						}/* else if (iv.getType() == TYPE_SWITCH) {
							if (event.getAction() == MotionEvent.ACTION_DOWN) {
																
								for (int ii = 0; ii < 10; ii++) 
								{
								    touchstates[ii] = false;
								    oldtouches[ii] = 0;
								}
								changeState();
								mm.getMainHelper().updateMAME4all();
								return true;
							}
						}*/
					}
				}	                	            
			} 
		}

		for (int i = 0; i < touchstates.length; i++) {
			if (!touchstates[i] && newtouches[i]!=0) {
				boolean really = true;

				for (int j = 0; j < 10 && really; j++) {
					if (j == i)
						continue;
					really = (newtouches[j] & newtouches[i]) == 0;//try to fix something buggy touch screens
				}

				if (really)
				{
					pad_data[0] &= ~(newtouches[i]);
				}
				
				newtouches[i] = 0;
				oldtouches[i] = 0;
			}
		}
		
		handleImageStates();
		
		Emulator.setPadData(0,pad_data[0]);
		return true;
	}
}
