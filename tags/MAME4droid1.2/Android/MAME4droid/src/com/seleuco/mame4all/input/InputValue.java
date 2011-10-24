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

import com.seleuco.mame4all.MAME4all;

import android.graphics.Rect;


public class InputValue {
	
	protected Rect origRect = null;    
	protected Rect fixedRect = null;
	protected MAME4all mm = null;
	
    int [] data;
    
    public InputValue(int d[], MAME4all mm){
       this.mm = mm;
       data = d;	
    }
  
    public Rect getRect(){
    	if(fixedRect!=null)
    		return fixedRect;    	
    	return getOrigRect();
    }
    
    public Rect newFixedRect(){
    	Rect r = getOrigRect();
    	if(r!=null)
    	{	
    	   fixedRect = new Rect();
    	   fixedRect.set(r);
    	}   
    	return fixedRect;
    }
    
    protected Rect getOrigRect(){
    	if(origRect==null)
    	{
 	        if(data[0] == InputHandler.TYPE_STICK_RECT && mm.getPrefsHelper().isTouchDZ())
	        {
	    	   if(data[1] == InputHandler.STICK_LEFT)
	    	   {
	    		   //data[4] -= 25;
	    		   data[4] -= data[4] * 0.18f;
	    	   }
	    	   if(data[1] == InputHandler.STICK_RIGHT)
	    	   {
	    		   //data[2] += 25;
	    		   //data[4] -= 50;		    	    		   
	    		   data[2] += data[4] * 0.18f;
	    		   data[4] -= (data[4] * 0.18f);
	    	   }		    	    	   		    	    		  
	        }
    		origRect = new Rect( data[2], data[3], data[2] + data[4] , data[3] + data[5]); 
    	}
    	return origRect;
    }
        
    public int getType(){
    	return data[0];
    }
    
    public int  getValue(){
    	return data[1];
    }
        
}