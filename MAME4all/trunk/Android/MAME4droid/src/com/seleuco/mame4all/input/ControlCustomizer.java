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

import java.util.ArrayList;
import java.util.StringTokenizer;

import android.content.res.Configuration;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.Paint.Style;
import android.view.MotionEvent;

import com.seleuco.mame4all.MAME4all;
import com.seleuco.mame4all.helpers.PrefsHelper;

public class ControlCustomizer {
	
	private static boolean enabled = false;

	public static void setEnabled(boolean enabled) {
		ControlCustomizer.enabled = enabled;
	}
	
	public static boolean isEnabled() {
		return enabled;
	}
	
	private InputValue valueMoved = null;
	private int ax = 0;
	private int ay = 0;
	private int old_ax=0;
	private int old_ay=0;
	private int prev_ax=0;
	private int prev_ay=0;

	protected MAME4all mm = null;
	
	public void setMAME4all(MAME4all value) {
	    mm = value;	
	}
	
	public void discardDefinedControlLayout(){
							
		ArrayList<InputValue> values = mm.getInputHandler().getAllInputData();
		for (int j = 0; j < values.size(); j++) 
		{
			InputValue iv = values.get(j);
			iv.setOffsetTMP(0, 0);
			if(iv.getType() == InputHandler.TYPE_ANALOG_RECT)
				mm.getInputHandler().getAnalogStick().setStickArea(iv.getRect());
		}
		mm.getInputView().updateImages();	
	}
	
	public void saveDefinedControlLayout(){
		
		StringBuffer definedStr = new StringBuffer(); 
					
		ArrayList<InputValue> values = mm.getInputHandler().getAllInputData();
		boolean first = true;
		for (int j = 0; j < values.size(); j++) 
		{
			InputValue iv = values.get(j);
			iv.commitChanges();
			if(iv.getXoff()==0 && iv.getYoff()==0)
				continue;
			if(!first)
				definedStr.append(",");
			definedStr.append(iv.getType()+","+iv.getValue()+","+iv.getXoff()+","+iv.getYoff());
			first = false;
		}
		mm.getPrefsHelper().setDefinedControlLayout(definedStr.toString());		
	}
	
	public void readDefinedControlLayout(){
		if(mm.getMainHelper().getscrOrientation() != Configuration.ORIENTATION_LANDSCAPE)
			return;
		
		String definedStr = mm.getPrefsHelper().getDefinedControlLayout();
		
		if(definedStr!=null)
		{	
		
		ArrayList<InputValue> values = mm.getInputHandler().getAllInputData();
		
		StringTokenizer tok = new StringTokenizer(definedStr,",",false);
		
			while(tok.hasMoreTokens())
			{
			    int type  = Integer.parseInt(tok.nextToken());
			    int value = Integer.parseInt(tok.nextToken());
			    int xoff = Integer.parseInt(tok.nextToken());
			    int yoff = Integer.parseInt(tok.nextToken());
			    for (int j = 0; j < values.size(); j++) 
			    {
					InputValue iv = values.get(j);
					if(iv.getType() == type && iv.getValue()==value)
					{	
						iv.setOffset(xoff, yoff);
						if(type == InputHandler.TYPE_ANALOG_RECT)
						   mm.getInputHandler().getAnalogStick().setStickArea(iv.getRect());
					}	
			    }		
			 }
		}
		
		mm.getInputView().updateImages();				
		
	}
	
	protected void updateRelatedRects(){
		
		ArrayList<InputValue> values = mm.getInputHandler().getAllInputData();
		if(valueMoved.getType() == InputHandler.TYPE_BUTTON_RECT)
		{
			for (int j = 0; j < values.size(); j++) 
			{
				InputValue iv = values.get(j);
				if(iv.getType()==InputHandler.TYPE_BUTTON_IMG && iv.getValue() == valueMoved.getValue())
				{
					iv.setOffsetTMP(valueMoved.getXoff_tmp(), valueMoved.getYoff_tmp());
					break;
				}	
			}
		}
		else if(valueMoved.getType() == InputHandler.TYPE_STICK_IMG || valueMoved.getType() == InputHandler.TYPE_ANALOG_RECT)
		{
			for (int j = 0; j < values.size(); j++) 
			{
				InputValue iv = values.get(j);
				
				if(iv.getType()==InputHandler.TYPE_STICK_RECT || iv.getType() == InputHandler.TYPE_STICK_IMG ||  iv.getType() == InputHandler.TYPE_ANALOG_RECT)
					iv.setOffsetTMP(valueMoved.getXoff_tmp(), valueMoved.getYoff_tmp());
				
				if(iv.getType() == InputHandler.TYPE_ANALOG_RECT)
				{
					mm.getInputHandler().getAnalogStick().setStickArea(valueMoved.getRect());
				}								
			}
		}		
	}

	public void handleMotion(MotionEvent event){
		int action = event.getAction();
		
		int x = (int) event.getX();
		int y = (int) event.getY();

		if (action == MotionEvent.ACTION_UP || action == MotionEvent.ACTION_CANCEL) {
			valueMoved = null;
			mm.getInputView().invalidate();
			ax=0;
			ay=0;			
		} 
		else 
		{						
			if(valueMoved != null)
			{
				int new_ax = ((Math.abs((x-ax) - prev_ax) > 5 ? (x - ax) : 0)/5)*5;
				int new_ay = ((Math.abs((y-ay) - prev_ay) > 5 ? (y - ay) : 0)/5)*5;
				if(new_ax!=0 || new_ay != 0)
				{
					prev_ax = new_ax!=0 ? new_ax : prev_ax;
					prev_ay = new_ay!=0 ? new_ay : prev_ay;
					valueMoved.setOffsetTMP(prev_ax+old_ax,prev_ay+old_ay);
					this.updateRelatedRects();
					mm.getInputView().updateImages();				
					mm.getInputView().invalidate();
				}
				//mm.getInputView().invalidate(valueMoved.getRect());
			}
			else				
			{	
				ArrayList<InputValue> values = mm.getInputHandler().getAllInputData();
				
				for (int j = 0; j < values.size(); j++) 
				{
				    InputValue iv = values.get(j);

      				if (iv.getRect().contains(x, y)) {

				    	if (iv.getType() == InputHandler.TYPE_BUTTON_RECT || iv.getType() == InputHandler.TYPE_STICK_IMG
				    			|| iv.getType() == InputHandler.TYPE_ANALOG_RECT) {						
						//iv.setOffsetTMP(0,0);
						//ax = iv.getRect().centerX();
						//ay = iv.getRect().centerY();
						old_ax = iv.getXoff_tmp();
						old_ay = iv.getYoff_tmp();
						ax = x;
						ay = y;
						valueMoved = iv;
						break;
					   }
			   	   }
				}	
			}
		}
	}
	
	public void draw(Canvas canvas) {
		ArrayList<InputValue> ids = mm.getInputHandler().getAllInputData();
		Paint p2 = new Paint();
   	    p2.setARGB(30, 255, 255, 255);
		//p2.setColor(Color.CYAN);
		p2.setStyle(Style.FILL);
		for(int i=0; i<ids.size();i++)
		{
		   InputValue v = ids.get(i);
		   Rect r = v.getRect();
		   if(r!=null  )
		   {
		       if (v.getType()==InputHandler.TYPE_BUTTON_RECT)
		    	   canvas.drawRect(r, p2);
		       else if(mm.getPrefsHelper().getControllerType() == PrefsHelper.PREF_DIGITAL && v.getType()==InputHandler.TYPE_STICK_RECT)
		    	   canvas.drawRect(r, p2);
		       else if(mm.getPrefsHelper().getControllerType() != PrefsHelper.PREF_DIGITAL && v.getType()==InputHandler.TYPE_ANALOG_RECT)
		    	   canvas.drawRect(r, p2);
		   }  
		}	
	}
}
