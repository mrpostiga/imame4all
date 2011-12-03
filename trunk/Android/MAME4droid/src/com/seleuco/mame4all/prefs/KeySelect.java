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

package com.seleuco.mame4all.prefs;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;


public class KeySelect extends Activity {

	protected int emulatorInputIndex;

	@Override
	public void onCreate(Bundle icicle) {
		super.onCreate(icicle);

		emulatorInputIndex = getIntent().getIntExtra("emulatorInputIndex", 0);
		setTitle("Press button for \""+ListKeys.emulatorInputLabels[emulatorInputIndex]+"\"");


		final Button chancelButton = new Button(this) {
			{
				setText("Cancel");
				setOnClickListener(new View.OnClickListener() {
					public void onClick(View v) {
						setResult(RESULT_CANCELED, new Intent());
						finish();
					}
				});
			}
		};

		final Button clearButton = new Button(this) {
			{
				setText("Clear");
				setOnClickListener(new View.OnClickListener() {
					public void onClick(View v) {
						setResult(RESULT_OK, new Intent().putExtra("androidKeyCode",  -1));
						finish();
					}
				});
			}
		};

		final View primaryView = new View(this) {
			{
				setLayoutParams(new LayoutParams(LayoutParams.FILL_PARENT, 1));
				setFocusable(true);
				setFocusableInTouchMode(true);
				requestFocus();
			}
            /*
			@Override
			public boolean onKeyPreIme (int keyCode, KeyEvent event) {

				setResult(RESULT_OK, new Intent().putExtra("androidKeyCode", keyCode));
				finish();
				return true;
			}
			*/
			@Override
			public boolean onKeyDown (int keyCode, KeyEvent event) {

				setResult(RESULT_OK, new Intent().putExtra("androidKeyCode", keyCode));
				finish();
				return true;
			}
		};

		final LinearLayout parentContainer = new LinearLayout(this) {
			{
				setOrientation(LinearLayout.VERTICAL);
				addView(chancelButton);
				addView(clearButton);
				addView(primaryView);
			}
		};

		setContentView(parentContainer, new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.WRAP_CONTENT));

	}

}