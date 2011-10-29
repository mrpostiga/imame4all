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

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;

import com.seleuco.mame4all.Emulator;
import com.seleuco.mame4all.MAME4all;

public class DialogHelper {
	
	public final static int DIALOG_EXIT = 1;
	public final static int DIALOG_ERROR = 2;
	public final static int DIALOG_INFO = 3;
	public final static int DIALOG_EXIT_GAME = 4;
	public final static int DIALOG_OPTIONS = 5;
	public final static int DIALOG_THANKS = 6;
	public final static int DIALOG_FULLSCREEN = 7;
	
	protected MAME4all mm = null;
	
	protected String errorMsg;
	protected String infoMsg;
	
	public void setErrorMsg(String errorMsg) {
		this.errorMsg = errorMsg;
	}

	public void setInfoMsg(String infoMsg) {
		this.infoMsg = infoMsg;
	}
		
	public DialogHelper(MAME4all value){
		mm = value;
	}
	
	public Dialog createDialog(int id) {
	    Dialog dialog;
	    AlertDialog.Builder builder = new AlertDialog.Builder(mm);
	    switch(id) {
	    case DIALOG_EXIT:
	    	
	    	builder.setMessage("Are you sure you want to exit?")
	    	       .setCancelable(false)
	    	       .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
	    	           public void onClick(DialogInterface dialog, int id) {
	    	                //System.exit(0);
	    	                android.os.Process.killProcess(android.os.Process.myPid());   
	    	           }
	    	       })
	    	       .setNegativeButton("No", new DialogInterface.OnClickListener() {
	    	           public void onClick(DialogInterface dialog, int id) {
	    	                dialog.cancel();
	    	           }
	    	       });
	    	dialog = builder.create();
	        break;
	    case DIALOG_ERROR:
	    	builder.setMessage("Error")
	    	       .setCancelable(false)
	    	       .setPositiveButton("OK", new DialogInterface.OnClickListener() {
	    	           public void onClick(DialogInterface dialog, int id) {
	    	                System.exit(0);
	    	           }
	    	       });

	    	 dialog = builder.create();
	         break;
	    case DIALOG_INFO:
	    	builder.setMessage("Info")
	    	       .setCancelable(false)
	    	       .setPositiveButton("OK", new DialogInterface.OnClickListener() {
	    	           public void onClick(DialogInterface dialog, int id) {
	    	           }
	    	       });

	    	 dialog = builder.create();
	         break;
	    case DIALOG_EXIT_GAME:	    	
	    	builder.setMessage("Are you sure you want to exit game?")
	    	       .setCancelable(false)
	    	       .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
	    	           public void onClick(DialogInterface dialog, int id) {
	    	                Emulator.resume();
	    		        	Emulator.setValue(Emulator.EXIT_GAME_KEY, 1);		    	
	    			    	try {
	    						Thread.sleep(100);
	    					} catch (InterruptedException e) {
	    						e.printStackTrace();
	    					}
	    					Emulator.setValue(Emulator.EXIT_GAME_KEY, 0);	    	                
	    	                //dialog.dismiss();
	    	           }
	    	       })
	    	       .setNegativeButton("No", new DialogInterface.OnClickListener() {
	    	           public void onClick(DialogInterface dialog, int id) {
	    	        	   Emulator.resume(); 
	    	        	   dialog.cancel();
	    	           }
	    	       });
	    	dialog = builder.create();
	        break;
	    case DIALOG_OPTIONS:	    	
	    	final CharSequence[] items = {"Help","Settings", "Support", "Cancel"};
	    	builder.setTitle("Choose an option from the menu. Press cancel to go back");
	    	builder.setItems(items, new DialogInterface.OnClickListener() {
	    	    public void onClick(DialogInterface dialog, int item) {
	    	        switch (item){
	    	          case 0: mm.getMainHelper().showHelp();break;
	    	          case 1: mm.getMainHelper().showSettings();break;
	    	          case 2: mm.showDialog(DialogHelper.DIALOG_THANKS);;break;
	    	          case  3: Emulator.resume();break;
	    	        }
	    	    }
	    	});
	    	dialog = builder.create();
	        break;
	    case DIALOG_THANKS:
	    	builder.setMessage("I am releasing everything for free, in keeping with the licensing MAME terms, which is free for non-commercial use only. This is strictly something I made because I wanted to play with it and have the skills to make it so. That said, if you are thinking on ways to support my development I suggest you to check my support page of other free works for the community.")
	    	       .setCancelable(false)
	    	       .setPositiveButton("OK", new DialogInterface.OnClickListener() {
	    	           public void onClick(DialogInterface dialog, int id) {
	    	        	   mm.getMainHelper().showWeb();
	    	           }
	    	       });

	    	 dialog = builder.create();
	         break;
	    case DIALOG_FULLSCREEN:	    	
	    	final CharSequence[] items2 = {"Options","Exit","Cancel"};
	    	builder.setTitle("Choose an option from the menu. Press cancel to go back");
	    	builder.setItems(items2, new DialogInterface.OnClickListener() {
	    	    public void onClick(DialogInterface dialog, int item) {
	    	        switch (item){
	    	          case 0: mm.showDialog(DialogHelper.DIALOG_OPTIONS);break;
	    	          case 1:	    	        	
	    	        	if(!Emulator.isInMAME())
						    mm.showDialog(DialogHelper.DIALOG_EXIT);
					    else
					        mm.showDialog(DialogHelper.DIALOG_EXIT_GAME);
                        break;
	    	          case 2: Emulator.resume();break;
	    	        }
	    	    }
	    	});
	    	dialog = builder.create();
	        break;	         
	    default:
	        dialog = null;
	    }
	    return dialog;

	}

	public void prepareDialog(int id, Dialog dialog) {
		
		if(id==DIALOG_ERROR)
		{
			((AlertDialog)dialog).setMessage(errorMsg);
		}
		else if(id==DIALOG_INFO)
		{
			((AlertDialog)dialog).setMessage(infoMsg);
		}	
	    else if(id==DIALOG_EXIT_GAME)
		{
	    	Emulator.pause();
		}
	    else if(id==DIALOG_OPTIONS)
		{
	    	 Emulator.pause();
		}
	    else if(id==DIALOG_FULLSCREEN)
		{
	    	 Emulator.pause();
		}
	}
        
}
