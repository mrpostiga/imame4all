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

import android.content.Context;
import android.content.res.TypedArray;
import android.preference.DialogPreference;
import android.util.AttributeSet;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;

import com.seleuco.mame4all.R;

public class SensitivityPrefScreen extends DialogPreference implements
		SeekBar.OnSeekBarChangeListener {
	private SeekBar seekBar;
	private TextView valueView;
	private int minValue = 1, maxValue = 10;
	private int oldValue, newValue;

	
	public SensitivityPrefScreen(Context context, AttributeSet attrs) {
		super(context, attrs);
		
		//minValue = attrs.getAttributeIntValue("", "minValue", 1);
		//maxValue = attrs.getAttributeIntValue("", "maxValue", 10);
		
		setDialogLayoutResource(R.layout.bar);
		setPositiveButtonText("Save");
		setNegativeButtonText("Cancel");
	}

	@Override
	protected void onBindDialogView(View view) {
		super.onBindDialogView(view);
		if (newValue < minValue)
			newValue = minValue;
		if (newValue > maxValue)
			newValue = maxValue;
		seekBar = (SeekBar) view.findViewById(R.id.seekbar);
		seekBar.setMax(maxValue - minValue);
		seekBar.setProgress(newValue - minValue);
		seekBar.setSecondaryProgress(newValue - minValue);
		seekBar.setOnSeekBarChangeListener(this);
		valueView = (TextView) view.findViewById(R.id.value);
		valueView.setText(Integer.toString(newValue));
	}

	public void onProgressChanged(SeekBar seekBar, int progress,
			boolean fromUser) {
		newValue = progress + minValue;
		valueView.setText(Integer.toString(newValue));
	}

	public void onStartTrackingTouch(SeekBar seekBar) {
	}

	public void onStopTrackingTouch(SeekBar seekBar) {
	}

	@Override
	protected void onDialogClosed(boolean positiveResult) {
		super.onDialogClosed(positiveResult);
		if (!positiveResult)
			newValue = oldValue;
		else {
			
			//InputHandler.trackballSensitivity = newValue;
			
			oldValue = newValue;
			persistInt(newValue);
		}
	}

	@Override
	protected Object onGetDefaultValue(TypedArray a, int index) {
		return a.getInteger(index, 0);
	}

	@Override
	protected void onSetInitialValue(boolean restoreValue, Object defaultValue) {
		oldValue = (restoreValue ? getPersistedInt(0)
				: ((Integer) defaultValue).intValue());
		newValue = oldValue;
	}
}