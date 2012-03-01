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

package com.seleuco.mame4all;

import android.media.AudioTrack;

public class SoundThread implements Runnable {

	protected Thread t = null;
	protected AudioTrack audioTrack;

	byte[] buff;
	int buff_size;

	public void setAudioTrack(AudioTrack audioTrack) {
		this.audioTrack = audioTrack;
	}

	public SoundThread() {
		// Size: (44100/30fps) * bytesize * stereo * (2 buffers)
		buff = new byte[1470 * 2 * 2 * 2];
		buff_size = 0;
		t = new Thread(this, "sound-Thread");
		t.start();
	}

	@Override
	public void run() {

		while (true) {
			synchronized (this) {
				try {
					wait();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}

			if (audioTrack != null) {
				audioTrack.write(buff, 0, buff_size);
			}
		}
	}

	synchronized public void writeSample(byte[] b, int size) {

		System.arraycopy(b, 0, buff, 0, size);
		buff_size = size;
		this.notify();
	}

}
