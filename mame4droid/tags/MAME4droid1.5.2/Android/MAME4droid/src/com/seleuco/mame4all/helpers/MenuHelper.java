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

import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

import com.seleuco.mame4all.Emulator;
import com.seleuco.mame4all.MAME4all;
import com.seleuco.mame4all.R;
import com.seleuco.mame4all.input.InputHandler;

public class MenuHelper {
	
	protected MAME4all mm = null;
	
	public MenuHelper(MAME4all value){
		mm = value;
	}
	
	public boolean createOptionsMenu(Menu menu) {
		
		MenuInflater inflater = mm.getMenuInflater();		
		inflater.inflate(R.menu.menu, menu);        
		
		return true;		
	}
	
	public boolean prepareOptionsMenu(Menu menu) {
		
		return true;
	}

	public boolean optionsItemSelected(MenuItem item) {
	
		switch (item.getItemId()) {

		case (R.id.menu_quit_option):
			 mm.showDialog(DialogHelper.DIALOG_EXIT);
			return true;
		case (R.id.menu_quit_game_option):
			if(Emulator.isInMAME())
		       mm.showDialog(DialogHelper.DIALOG_EXIT_GAME);
			return true;			
		case R.id.menu_options_option:
			 mm.showDialog(DialogHelper.DIALOG_OPTIONS);
			return true;		
		case R.id.vkey_A:
			mm.getInputHandler().handleVirtualKey(InputHandler.A_VALUE);
			return true;
		case R.id.vkey_B:
			mm.getInputHandler().handleVirtualKey(InputHandler.B_VALUE);
			return true;
		case R.id.vkey_X:
			mm.getInputHandler().handleVirtualKey(InputHandler.X_VALUE);
			return true;
		case R.id.vkey_Y:
			mm.getInputHandler().handleVirtualKey(InputHandler.Y_VALUE);
			return true;
		case R.id.vkey_MENU:
			mm.getInputHandler().handleVirtualKey(InputHandler.START_VALUE);
			return true;
		case R.id.vkey_SELECT:
			mm.getInputHandler().handleVirtualKey(InputHandler.SELECT_VALUE);
			return true;
		}

		return false;

	}

}
