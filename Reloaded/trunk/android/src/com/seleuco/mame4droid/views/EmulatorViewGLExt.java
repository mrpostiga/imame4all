package com.seleuco.mame4droid.views;

import android.content.Context;
import android.os.Build;
import android.os.Handler;
import android.util.AttributeSet;

import com.seleuco.mame4droid.MAME4droid;
import com.seleuco.mame4droid.helpers.DialogHelper;
import com.seleuco.mame4droid.input.InputHandler;
import com.seleuco.mame4droid.views.EmulatorViewGL;

public class EmulatorViewGLExt extends EmulatorViewGL implements  android.view.View.OnSystemUiVisibilityChangeListener  {
	
	protected int mLastSystemUiVis;
	
	public void setMAME4droid(MAME4droid mm) {
		
		super.setMAME4droid(mm);
		
		if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1)
		{
          setNavVisibility(true);
          setOnSystemUiVisibilityChangeListener(this);
		}
	}

	public EmulatorViewGLExt(Context context, AttributeSet attrs) {
		super(context, attrs);
	}
	
    Runnable mNavHider = new Runnable() {
        @Override public void run() {
            setNavVisibility(false);
        }
    };
    
    @Override protected void onWindowVisibilityChanged(int visibility) {
        super.onWindowVisibilityChanged(visibility);

        // When we become visible, we show our navigation elements briefly
        // before hiding them.
        /**/
        setNavVisibility(true);
        getHandler().postDelayed(mNavHider, 2000);        
    }
    
	@Override
	public void onSystemUiVisibilityChange(int visibility) {
		// Detect when we go out of low-profile mode, to also go out
        // of full screen.  We only do this when the low profile mode
        // is changing from its last state, and turning off.

        int diff = mLastSystemUiVis ^ visibility;
        mLastSystemUiVis = visibility;
                       
        if ((diff&SYSTEM_UI_FLAG_HIDE_NAVIGATION) != 0
                && (visibility&SYSTEM_UI_FLAG_HIDE_NAVIGATION) == 0) {
            setNavVisibility(true);
            mm.showDialog(DialogHelper.DIALOG_FULLSCREEN);
        }
        else  if ((diff&SYSTEM_UI_FLAG_LOW_PROFILE) != 0
                && (visibility&SYSTEM_UI_FLAG_LOW_PROFILE) == 0) {
            setNavVisibility(true);
        }
	}
	
    void setNavVisibility(boolean visible) {
        int newVis = 0;
        boolean full = mm.getInputHandler().getInputHandlerState() == InputHandler.STATE_SHOWING_NONE;
        
        if(full)
        {
        	newVis = SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | SYSTEM_UI_FLAG_LAYOUT_STABLE;
        }
        else
        {
        	newVis = SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | SYSTEM_UI_FLAG_LAYOUT_STABLE;
        }
        
        if (!visible) 
        {
        	if(full)
        	{
                newVis |= SYSTEM_UI_FLAG_LOW_PROFILE | SYSTEM_UI_FLAG_FULLSCREEN
                    | SYSTEM_UI_FLAG_HIDE_NAVIGATION;
        	}
        	else
        	{
        		newVis |= SYSTEM_UI_FLAG_LOW_PROFILE | SYSTEM_UI_FLAG_FULLSCREEN;
        	}        	
        }

        // If we are now visible, schedule a timer for us to go invisible.
        if (visible) {
            Handler h = getHandler();
            if (h != null) {
                h.removeCallbacks(mNavHider);
                h.postDelayed(mNavHider, 3000);               
            }
        }

        // Set the new desired visibility.
        setSystemUiVisibility(newVis);
    }		

}
