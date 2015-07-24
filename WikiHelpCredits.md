**INTRODUCTION**

iMAME4all is a iOS universal app, port of MAME 0.37b5 emulator by Nicola Salmoria for all iOS devices
(iPad HD, iPhone 4G , iPod touch and older) based on GP2X, WIZ MAME4ALL 2.5 by Franxis.

It emulates arcade games supported by original MAME 0.37b5 plus some additional games from newer MAME versions.

This version emulates over 2000 different romsets. (see at the end of document for a list of games that could work).

Please, try to understand that that with that amount of games, some will run better than others and some might not even run with iMAME4all.
Please, don´t email me asking for a specific game to run.

Although the performance is very good with modern devices (all games I tested on iPad run practically perfect), owners of older devices should
not expect a good performance; please turn off sound because that's very helpful.

After installing, place your MAME-titled zipped roms in /var/mobile/Media/ROMs/iMAME4all/roms folder.

Please use "clrmame.dat" file included in /var/mobile/Media/ROMs/iMAME4all to convert romsets from other MAME versions to the ones used by
this version, using ClrMAME Pro utility, available in next webpage:

http://mamedev.emulab.it/clrmamepro/

To see MAME license see the end of this document

**CONTROLS**

The emulator controls are the next ones:

- Virtual pad: Movement in pad, mouse and analog control of the four players.

- Buttons B,X,A,Y,L,R: Buttons A,B,C,D,E,F.

- Button SELECT (1): Insert credits (UP+SELECT = 2P credits, RIGHT+SELECT = 3P credits, DOWN+SELECT = 4P credits).

- Button START (2): start (UP+START = 2P start, RIGHT+START = 3P start, DOWN+START = 4P start).

- Button L1+[R1](https://code.google.com/p/imame4all/source/detail?r=1): Pause.

- Buttons L2: Exit to selection menu to select another game.

- Buttons L1+START simultaneously: Show profiler.

- Buttons START+SELECT simultaneously: Access to the MAME menu.

- Button [R2](https://code.google.com/p/imame4all/source/detail?r=2): Open help & global options.

NOTE: To type OK when MAME requires it, press LEFT and then RIGHT.

**EMULATION OPTIONS**

After selecting a game on the list, the following configuration options are available:

- Video Aspect:
The video aspect can be configured with the following combination of options:

Original: Original game driver resolution scaled to window keeping aspect ratio.
Cropping 4/3 or 3/4: Original game driver resolution scaled to window with cropping.
Fixed 320x240,240x320,640x480,480x640: Nominal emulated video resolution scaled to fixed resolution.
NOTE:If "Not Safe Render Path" is active, only fixed 320x240 (4/3) or 240x320 (3/4) are available.


- Video Rotate:
The video Rotate is configured with the following combination of options:
Normal: Nominal emulated video resolution.
Rotate: The window is rotated.
TATE: The window and controls are rotated. (it may help to play some landscape games)

- Video Sync:
Normal: Single buffer and dirty buffer is used.
DblBuf: Double buffer without dirty buffer.
OFF: No video synchronization, use manual frameskip.

- Frame-Skip:
Auto: The frameskip is adjusted automatically in real time.
0 to 11: The frameskip is manually adjusted. The selected frames each 12 are skipped.

- Sound:
The sound options are the following ones:
ON: The sound is activated. 11, 22, 33 and 44 KHz sound mixing rates are available in both mono and stereo.
OFF: The sound is disabled.
Fast sound: Some tweaks are done to improve the performance (but with a bit worse sound quality).

- CPU Clock:
The clock of the CPUs can be adjusted from 50% to 200%. The nominal value is 100% and the CPU is emulated accurately.
The clock can be safely underclocked to about 80% to gain performance in almost all games (be careful because some
games could not run correctly). Use lower values to get more performance but probably several more games would not
run correctly. Also the clock can be overclocked up to 200% to avoid slowdowns in some Neo·Geo games.

- Audio Clock:
The clock of the audio CPUs can also be adjusted from 50% to 200%. The nominal value is 100%. It can be underclocked
and overclocked as well.

- Cheats:
ON: The cheats are enabled. To access in game press SELECT+START and enter the "Cheats" menu.
OFF: The cheats are disabled.
Note: The high scores are not saved if cheats are enabled!!!.

- Auto-Fire:
To access the auto-fire configuration, during game press SELECT+START and enter the "Auto-Fire" menu.

- Press B to play the selected game or X to go back to game selection menu.

**GLOBAL OPTIONS**

-Smoothed image. Enable to apply a smoothing image filter over the emulator screen.

-TV Filter. Enable to apply a TV like filter over the image.

-Sacanline Filter. Enable to apply a scanline filter over the image.

-Keeps Aspect. 'Enabled' keeps the aspect ratio; 'Disabled' will use all available screen.

-Safe Render Path (iPhone only). Enable at the expenses of performance for maximun compability. Slow in 3G (not recomended unless you find any problem).

-Full Screen (Landscape); Uses all avalible screen or shows the emulator windowed.

-Animated DPad. Animates ON/OFF DPad. Disable to gain performance.

-Low Latency Sound. More accurate sound. Expensive.(keep enabled on iPad)

-Show FPS: Shows ON/OFF fps.

-Touch DeadZone: Enable/Disable a deadzone on DPAD touch center. It could be better for some games. Disable if you don't like it.

-Wii Classic DZ: Wii classic stick deadzone selector. Upper if you have problems with stick (controller going crazy). Lower to gets more sensitivity.

-Skin: Let's you select skin (retina or not). Retina skin looks better but needs more resources.

-Native TV-OUT:  If you like iPad 2 TVOUT mirror or you use and external 3rd party TVOUT app, you can turn off iMame4All native TVOUT.

-Overscan TV-OUT: You can set the amount of TV overscan correction.

**WIIMOTE**

iMAME4all lets you use a WiiMote over bluetooth to play.

iMAME4all uses btstack project to support WiiMote:

http://code.google.com/p/btstack/

To use WiiMote you have to first launch iMAME4all menu pressing [R2](https://code.google.com/p/imame4all/source/detail?r=2) button, and select WiiMote option. Then, make your WiiMote discoverable by pressing the 1+2 buttons at the same time.

Lanscape touch DPad is hidden when you use WiiMote. You can play with aspect view (Rotation, TATE) and lock phisical rotation to play portrait-landscape games better.

Buttons mapping:

2 = B

1 = X

+ = START

- = SELECT

B = Y

A = A

home: exit game

In landscape mode touch on anywhere of the screen to show the emulator options.

**ICADE**

Best way to use iCade with iMAME4All is in fullscreen portrait mode, hit the option button and choose options. The onscreen controls will fade out when you start using the iCade buttons
to get on screen controls back, just touch the screen.

if the iCade is off (the fake coin slot light is off) just hit an iCade button or move the joystick.(you must have paired the iCade via bluetooth before)

when the iCade turns off, the SW keyboard may popup and then backdown, this is normal don't be alarmed

iCade KEY MAPPINGS

TOP:  [RED/COIN]	[BLACK/EXIT]	[BLACK/Y]	[WHITE/B]
BOT:  [RED/START]	[BLACK/OPTION]	[BLACK/A]	[WHITE/X]

Thanks to Todd Laney for sending me patches, and Martijn Bosschaart who has support me to get the iCade HW.

Due to the limitations of the HW not all games are suited, use WiiClassic instead if you get slowdowns or control lag.

**TV-OUT**

To connect an iPad ot iPhone to your TV or a projector, you can either use the Apple HDMI, Component AV Cable, Apple Composite AV Cable, Apple Dock Connector to VGA Adapter, or other compatible cable.

Use TV Out settings to set up how iPad or iPhone plays videos on your TV.

When the cable is connected to a TV or projector, iMAME4all will automatically use it when playing a game.

Set the TV signal to NTSC or PAL: Choose Video > TV Signal and select NTSC or PAL. NTSC and PAL are TV broadcast standards, used in different regions. If you are in the Americas, NTSC is probably the correct choice. Elsewhere, try PAL. If youâ€™re not sure, check the documentation that came with your TV or projector.

Note: TV-Out needs firmaware >= 3.2

You can set the amount of overscan corrections in options menu.

If you like iPad 2 TVOUT mirror or you use and external 3rd party TVOUT app, you can turn off iMame4All native TVOUT in options menu.


**INSTALLATION**

cheat.dat   -> Cheats definition file

hiscore.dat -> High Scores definition file

artwork/    -> Artwork directory

cfg/        -> MAME configuration files directory

frontend/   -> Frontend configuration files

hi/         -> High Scores directory

inp/        -> Game recordings directory

memcard/    -> Memory card files directory

nvram/      -> NVRAM files directory

roms/       -> ROMs directory

samples/    -> Samples directory

skins/      -> Frontend skins directory

snap/       -> Screen snapshots directory

sta/        -> Save states directory


**SUPPORTED GAMES**

There are 2270 different supported romsets.
Games have to be copied into the roms/ folder.


**ROM NAMES**

Folder names or ZIP file names are listed on "gamelist.txt" file.
Romsets have to be MAME 0.37b5 ones (July 2000).
Additionaly there are additional romsets from newer MAME versions.

Please use "clrmame.dat" file to convert romsets from other MAME versions to the ones used by
this version for GP2X, using ClrMAME Pro utility, available in next webpage:

http://mamedev.emulab.it/clrmamepro/

NOTE: File and directory names in Linux are case-sensitive. Put all file and directory names
using low case!.


**SOUND SAMPLES**

The sound samples are used to get complete sound in some of the oldest games.
They are placed into the 'samples' directory compressed into ZIP files.
The directory and the ZIP files are named using low case!.

The sound samples collection can be downloaded in the following link:
http://dl.openhandhelds.org/cgi-bin/gp2x.cgi?0,0,0,0,5,2511

You can also use "clrmame.dat" file with ClrMAME Pro utility to get the samples pack.


**ARTWORK**

Artwork is used to improve the visualization for some of the oldest games. Download it here:
http://dl.openhandhelds.org/cgi-bin/gp2x.cgi?0,0,0,0,5,2512


**ORIGINAL CREDITS**

- MAME 0.37b5 original version by Nicola Salmoria and the MAME Team (http://www.mame.net).

- Z80 emulator Copyright (c) 1998 Juergen Buchmueller, all rights reserved.

- M6502 emulator Copyright (c) 1998 Juergen Buchmueller, all rights reserved.

- Hu6280 Copyright (c) 1999 Bryan McPhail, mish@tendril.force9.net

- I86 emulator by David Hedley, modified by Fabrice Frances (frances@ensica.fr)

- M6809 emulator by John Butler, based on L.C. Benschop's 6809 Simulator V09.

- M6808 based on L.C. Benschop's 6809 Simulator V09.

- M68000 emulator Copyright 1999 Karl Stenerud.  All rights reserved.

- 80x86 M68000 emulator Copyright 1998, Mike Coates, Darren Olafson.

- 8039 emulator by Mirko Buffoni, based on 8048 emulator by Dan Boris.

- T-11 emulator Copyright (C) Aaron Giles 1998

- TMS34010 emulator by Alex Pasadyn and Zsolt Vasvari.

- TMS9900 emulator by Andy Jones, based on original code by Ton Brouwer.

- Cinematronics CPU emulator by Jeff Mitchell, Zonn Moore, Neil Bradley.

- Atari AVG/DVG emulation based on VECSIM by Hedley Rainnie, Eric Smith and Al Kossow.

- TMS5220 emulator by Frank Palazzolo.

- AY-3-8910 emulation based on various code snippets by Ville Hallik, Michael Cuddy, Tatsuyuki Satoh, Fabrice Frances, Nicola Salmoria.

- YM-2203, YM-2151, YM3812 emulation by Tatsuyuki Satoh.

- POKEY emulator by Ron Fries (rfries@aol.com). Many thanks to Eric Smith, Hedley Rainnie and Sean Trowbridge.

- NES sound hardware info by Jeremy Chadwick and Hedley Rainne.

- YM2610 emulation by Hiromitsu Shioya.


**PORT CREDITS**

- Port to iOS by David Valdeita (Seleuco)

- Port to GP2X and WIZ by Franxis (fjmar@hotmail.com) based on source code MAME 0.37b5 (dated on july 2000).

- TheGrimReaper (m\_acky@hotmail.com) has colaborated with a lot of things since GP32 MAME 1.3, i.e. Vector graphics support, high scores, general frontend, frontend improvements, bugfixes, etc. Thank you!!!

- Pepe\_Faruk (joserod@ya.com) has colaborated with new screen centering code. Also he has added some new supported games. Thank you!!!

- Reesy (drsms\_reesy@yahoo.co.uk) has developed DrZ80 (Z80 ASM ARM core) and has helped a lot with core integration into MAME. He has also done several fixes to the Cyclone core. You are the best!!!

- Flubba (flubba@i-solutions.se) has done some optimizations and improvements to the DrZ80 core. Thank you!!!

- Dave (dev@finalburn.com) has developed Cyclone (M68000 ASM ARM core). Big thanks to him.

- Notaz (notasas@gmail.com) have fixed some bugs in the Cyclone source code. He has also contributed with several useful code to the GP2X scene. Thanks!!!http://uosis.mif.vu.lt/~grig2790/Cyclone/ http://notaz.gp2x.de/

- Chui (sdl\_gp32@yahoo.es) has developed MAME4ALL, the MAME GP2X port for Dreamcast, Windows and Linux. Also he has done several optimizations aplicable to all targets. http://chui.dcemu.co.uk/mame4all.html

- Slaanesh (astaude@hotmail.com) has continued my work on MAME GP32 and he has done several improvements aplicable to all targets. http://users.bigpond.net.au/mame/gp32/

- GnoStiC (mustafa.tufan@gmail.com) has done the USB Joypad support using the library created by Puck2099.

- Sean Poyser (seanpoyser@gmail.com) has done interesting improvements in some drivers. For example the use of diagonals in Q\*Bert or the use of the shoulder buttons in Tron.

- TTYman (ttyman@free.fr) has done the MAME GP2X port for the PSP portable console. http://ttyman.free.fr/

- Headoverheels (davega@euskalnet.net) has added some new games to MAME4ALL, and he has also done some optimizations to existing games.


**KNOWN PROBLEMS**

- Preferences couldn't be saved. Check for write permissions. chmod 777 if needed: Just go to imame4all.app file in your iDevice directory and set the permissions to 777. also needs to be on the iMAME4ALL folder under /var/mobile/Media/ROMS. (recursive)

This is what you need to do. SSH into your iPad and then run this command on the two directories like this:

first command:
'chmod -R 777 /var/mobile/Media/ROMs/iMAME4a­ll' and
second command:
'chmod -R 777 /Applications/iMAME4all.app'

Make sure of the following:

1) You're logged in as root
2) You type in the commands case sensitive
3) iMAME4all is not running

> You can use other apps but this works for sure. You can try iFile from cydia, which is a UI file manager that let you change permissions.

- Not perfect sound or incomplete in some games.

- Memory leaks. In case of errors, reset iOS and try again please ;-).


**INTERESTING WEBPAGES ABOUT MAME**

- http://www.mame.net/

- http://www.mameworld.net/

- http://www.marcianitos.org/


**Thanks to:**

Todd Laney for sending me iCade patches, and Martijn Bosschaart for support me with an iCade.

**ART**

Retina skin and touch control layout thanks to Bryn Thompson.

also

Thanks to: Zenzuke, Chipan, Dokesman, Enkonsierto, Quest, Sttraping, Sike, Danibat, Pedator,
Antiriad and Slaanesh. Thanks to everybody !.

**iMAME4all license**

The iMAME4all project is released under the GPL license.
In addition you have some extra rights granted by a special license exception which allow you to link the iMAME4all GPL source with the not GPL MAME source.

The exception also gives you the rights to eliminate it if you don't like it or if you want to include the iMAME4all source in another GPL program. So, iMAME4all is 100% GPL.

You can more easily think at it as a sort of double license. A GPL or a GPL + exception. You have all the rights of the GPL, and, if you want, some others.

The only limitation is for iMAME4all. iMAME4all cannot include external GPL source without the explicit permission of the source copyright holder.


**MAME license**

http://www.mame.net
http://www.mamedev.com

Copyright © 1997-2009, Nicola Salmoria and the MAME team. All rights reserved.

Redistribution and use of this code or any derivative works are permitted provided
that the following conditions are met:

**Redistributions may not be sold, nor may they be used in a commercial product or activity.**

**Redistributions that are modified from the original source must include the complete source
code, including the source code for all components used by a binary built from the modified
sources. However, as a special exception, the source code distributed need not include
anything that is normally distributed (in either source or binary form) with the major
components (compiler, kernel, and so on) of the operating system on which the executable
runs, unless that component itself accompanies the executable.**

**Redistributions must reproduce the above copyright notice, this list of conditions and the
following disclaimer in the documentation and/or other materials provided with the distribution.**

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.