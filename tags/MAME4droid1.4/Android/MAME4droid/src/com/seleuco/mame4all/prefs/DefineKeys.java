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

import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import com.seleuco.mame4all.R;

public class DefineKeys extends ListActivity {
		
	protected int playerIndex = 0;
	
	public static final String[] playerLabels = {
        "Player 1",
        "Player 2",
        "Player 3",
        "Player 4",
	};

	@Override
	public void onCreate(Bundle icicle) {
		super.onCreate(icicle);
				
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_BLUR_BEHIND,
				WindowManager.LayoutParams.FLAG_BLUR_BEHIND);
		
		drawListAdapter();
	}

	private void drawListAdapter() {
		final Context context = this;

		ArrayAdapter<String> keyLabelsAdapter = new ArrayAdapter<String>(this,
				android.R.layout.simple_list_item_1, DefineKeys.playerLabels) {
			@Override
			public View getView(final int position, final View convertView,
					final ViewGroup parent) {
				final TextView textView = new TextView(context);
				textView.setTextAppearance(context, R.style.ListText);
				textView.setText(getItem(position));				
				return textView;
			}
		};

		setListAdapter(keyLabelsAdapter);
	}

	@Override
	public void onListItemClick(ListView parent, View v, int position, long id) {
		playerIndex = position;
		startActivityForResult(new Intent(this, ListKeys.class).putExtra(
				"playerIndex", playerIndex), 0);
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);

		drawListAdapter();
	}
}

