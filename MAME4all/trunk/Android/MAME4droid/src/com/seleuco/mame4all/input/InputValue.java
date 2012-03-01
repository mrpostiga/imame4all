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
	
	private int type;
	private int value;
	
	private int o_x1;
	private int o_y1;
	private int o_x2;
	private int o_y2;
	
	private float dx = 1;
	private float dy = 1;
	private int ax = 0;
	private int ay = 0;
	
	private int xoff_tmp = 0;
	private int yoff_tmp = 0;

	private int xoff = 0;
	private int yoff = 0;
	
	private Rect rect = null;
	
	private Rect origRect = null;    
	
	private MAME4all mm = null;
	    
    public InputValue(int d[], MAME4all mm){
       this.mm = mm;
       //data = d;
       type = d[0];
       value = d[1];
       
       if(type == InputHandler.TYPE_STICK_RECT && mm.getPrefsHelper().isTouchDZ())
       {
    	   if(value == InputHandler.STICK_LEFT)
    	   {
    		   d[4] -= d[4] * 0.18f;
    	   }
    	   if(value == InputHandler.STICK_RIGHT)
    	   {		    	    		   
    		   d[2] += d[4] * 0.18f;
    		   d[4] -= (d[4] * 0.18f);
    	   }		    	    	   		    	    		  
       }
       
       o_x1 = d[2];
       o_y1 = d[3];
       o_x2 = o_x1 + d[4];
       o_y2 = o_y1 + d[5];       
    }
  
    public void setFixData(float dx, float dy, int ax, int ay)
    {
    	this.dx = dx;
    	this.dy = dy;
    	this.ax = ax;
    	this.ay = ay;
    	rect = null;
    }
    
    public void setOffset(int xoff,int yoff)
    {
    	this.xoff = xoff;
    	this.yoff = yoff;
    	xoff_tmp = 0;
    	yoff_tmp = 0;
    	rect = null;
    }
    
    public void setOffsetTMP(int xoff_tmp,int yoff_tmp)
    {
    	this.xoff_tmp = xoff_tmp;
    	this.yoff_tmp = yoff_tmp;
    	rect = null;
    }
    
    public void commitChanges()
    {
    	xoff += xoff_tmp;
    	yoff += yoff_tmp;
    	xoff_tmp=0;
    	yoff_tmp=0;
    }
    
    public Rect getRect()
    {	
    	if(rect==null)
    	{
    		 rect = 
    			 new Rect( (int)(o_x1 * dx) + ax + xoff + xoff_tmp, 
    					   (int)(o_y1 * dy) + ay + yoff + yoff_tmp, 
    					   (int)(o_x2 * dx) + ax + xoff + xoff_tmp,
    					   (int)(o_y2 * dy) + ay + yoff + yoff_tmp); 
    	}
    	return rect;
    }
       
    protected Rect getOrigRect()
    {
    	if(origRect==null)
    	{
    		 origRect =  new Rect( o_x1, o_y1, o_x2, o_y2); 
    	}
    	return origRect;
    }
    
    
    public int getType(){
    	return type;
    }
    
    public int  getValue(){
    	return value;
    }
    
	public int getXoff_tmp() {
		return xoff_tmp;
	}

	public int getYoff_tmp() {
		return yoff_tmp;
	}
	
	public int getXoff() {
		return xoff;
	}

	public int getYoff() {
		return yoff;
	}
}