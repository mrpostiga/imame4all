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

//http://code.google.com/p/andengine/source/diff?spec=svn029966d918208057cef0cffcb84d0e32c3beb646&r=029966d918208057cef0cffcb84d0e32c3beb646&format=side&path=/src/org/anddev/andengine/sensor/orientation/OrientationData.java

//NOTAS: usar acelerometro es suficiente, 

package com.seleuco.mame4all.input;

import java.text.DecimalFormat;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.Surface;

import com.seleuco.mame4all.Emulator;
import com.seleuco.mame4all.MAME4all;

public class TiltSensor {
	
	
    DecimalFormat df = new DecimalFormat("000.00");
	
	protected MAME4all mm = null;
	
	public void setMAME4all(MAME4all value) {
		mm = value;
	}
	
	public static String str;
	
	public static float rx = 0;
	
    private float tilt;
    private float ang;
    
    static private boolean enabled = false;
            
	static public boolean isEnabled() {
		return enabled;
	}

	// Change this to make the sensors respond quicker, or slower:
    private static final int delay = SensorManager.SENSOR_DELAY_GAME;
    
    public TiltSensor() {
   
    }
    
    public void enable(){
    	
    	if(!enabled){
            if(mm==null)
            	return;
            if(!mm.getPrefsHelper().isTiltSensor())
            	return;
    	    SensorManager man = (SensorManager) mm.getApplicationContext().getSystemService(Context.SENSOR_SERVICE);             
            Sensor acc_sensor = man.getDefaultSensor(Sensor.TYPE_ACCELEROMETER); 
    	    enabled = man.registerListener(listen, acc_sensor, delay);  
    	}
    	
    }
    
    public void disable(){
    	if(enabled){
    		SensorManager man = (SensorManager) mm.getApplicationContext().getSystemService(Context.SENSOR_SERVICE);
    		man.unregisterListener(listen);
    		enabled = false;
    	}    	
    }
    
    int old = 0;
    
    // Special class used to handle sensor events:
    private final SensorEventListener listen = new SensorEventListener() {
        public void onSensorChanged(SensorEvent e) {
        	
        	final float alpha = 0.1f;
        	//final float alpha = 0.3f;       	
        	float value = - e.values[0]; 
        		
        	try{
               int r = mm.getWindowManager().getDefaultDisplay().getRotation();
               
           	   if(r == Surface.ROTATION_0)
        		  value = - e.values[0];
        	   else if(r == Surface.ROTATION_90)
        		  value =   e.values[1];
        	   else if (r == Surface.ROTATION_180)
        		  value =   e.values[0];
        	   else
        		  value = - e.values[1];        
        	}catch(Error ee){};
        	
        	tilt = alpha * tilt + (1 - alpha) * value;

        	float deadZone = getDZ();
        	             
        	if(Emulator.isInMAME()  )
        	{        		
        		if(Math.abs(tilt) < deadZone)
        		{
        			mm.getInputHandler().pad_data[0] &= ~InputHandler.LEFT_VALUE;
        			mm.getInputHandler().pad_data[0] &= ~InputHandler.RIGHT_VALUE;
        			old=0;
        		}
        		else if (tilt < 0)
        		{
        			mm.getInputHandler().pad_data[0] |= InputHandler.LEFT_VALUE;
        			mm.getInputHandler().pad_data[0] &= ~InputHandler.RIGHT_VALUE;
        			old=1;
        		}
        		else
        		{
        			mm.getInputHandler().pad_data[0] &= ~InputHandler.LEFT_VALUE;
        			mm.getInputHandler().pad_data[0] |= InputHandler.RIGHT_VALUE;
        			old=2;
        		}
        		
        		Emulator.setPadData(0, mm.getInputHandler().pad_data[0]);
        		mm.getInputHandler().handleImageStates();
        	}
        	else if(old!=0)
        	{
    			mm.getInputHandler().pad_data[0] &= ~InputHandler.LEFT_VALUE;
    			mm.getInputHandler().pad_data[0] &= ~InputHandler.RIGHT_VALUE;
        		old=0;
        		Emulator.setPadData(0, mm.getInputHandler().pad_data[0]);
        		mm.getInputHandler().handleImageStates();
        	}
        	        	
        	if(Math.abs(tilt) >=deadZone)
        	{
        		rx = ((float)(tilt - 0) / (float)(getSensitivity() - 0)); 
        		if(rx>1.0f)rx=1.0f;
        		if(rx<-1.0f)rx=-1.0f;
        	}
        	else
        	{
        		rx = 0;
        	}
        	Emulator.setAnalogData(0,rx,0);

        	if(Emulator.isDebug())
        	{	
            	ang = (float) Math.toDegrees(Math.atan( 9.81f / tilt) * 2);
            	ang = ang < 0 ? -(ang + 180) : 180 - ang;
                str = df.format(rx) + " "+ df.format(tilt)+" " +df.format(ang)+ " "+ getDZ()+ " "+ getSensitivity()+ " "+mm.getInputHandler().pad_data[0];
        		mm.getInputView().invalidate();
        	}    
        }
        
        public void onAccuracyChanged(Sensor event, int res) {}
    };

    protected float getDZ(){
    	float v = 0;
		switch(mm.getPrefsHelper().getTiltDZ())
        {
          case 1: v = 0.0f;break;
          case 2: v = 0.1f;break;
          case 3: v = 0.25f;break;
          case 4: v = 0.5f;break;
          case 5: v = 1.5f;break;
        }
		return v;
    }
    
    protected float getSensitivity(){
    	float v = 0;
		switch(mm.getPrefsHelper().getTiltSensitivity())
        {
          case 10: v = 1.0f;break;
          case 9: v = 1.5f;break;
          case 8: v = 2.0f;break;
          case 7: v = 2.5f;break;
          case 6: v = 3.0f;break;
          case 5: v = 3.5f;break;
          case 4: v = 4.0f;break;
          case 3: v = 4.5f;break;
          case 2: v = 5.0f;break;
          case 1: v = 5.5f;break;          
        }
		return v;
    }            
}
