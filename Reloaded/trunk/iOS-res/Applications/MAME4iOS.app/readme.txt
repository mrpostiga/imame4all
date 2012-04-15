=================================================================
MAME4iOS Reloaded (0.139u1 ) 1.0 WIP (April 08, 2012) 
by David Valdeita (Seleuco)
=================================================================


INTRODUCTION
---------------

MAME4iOS Reloaded is developed by David Valdeita (Seleuco), port of MAME 0.139u1 emulator by Nicola Salmoria and TEAM. 

MAME4iOS Reloaded emulates arcade games supported by original MAME 0.139u1.

This MAME4iOS version is targeted to A5 devices (1GHz and 512MB RAM minimum), because it is based on a high specs 2010 PC MAME build.
Anyway don't expect arcade games of the 90 to work at full speed. With some games that are really bad optimized (like outrun or mk series) you will 
need at least a future A6 device (ARM cortex a15). This is related to MAME build used, since it is  targeted to high specs PC's as i said before. 
This version doesn't have an UML backend ARM dynamic recompiler, which means drivers based on high specs arcade CPUs won't be playable 
(it has not sense since this games will be slow in any case).

Said that, with a low end device, use at your own risk. I suggest you use iMAME4all (0.37b5) instead.
Remember that games that can be emulated on both versions will run much faster on iMAME4all (0.37b5) than on MAME4iOS Reloaded (0.139u1),
and will drain less battery.

This version emulates over 8000 different romsets. 

Please, try to understand that that with that amount of games, some will run better than others and some might not even run with MAME4iOS Reloaded. 
Please, don't email me asking for a specific game to run.

Tips to help performance: use lower quality sound or switch it off. Disable stick and buttons animations and disable smooth scaling also.

After installing, place your MAME-titled zipped roms in /var/mobile/Media/ROMs/MAME4iOS/ folder.

MAME4iOS Reloaded uses only '0.139u1' romset.

Official web page for news, source code & additional information:

http://code.google.com/p/imame4all/

To see MAME license, go to the end of this document.

Features
------------

Autorotate.
Smoothed image.
Scanline & TV Filter.
Full screen, windowed.
Animated touch DPad.
1/4 buttons selectable.
Video Aspect Normal, Rotate, Rotate controls.
Adjustable CPU, Audio clock.
WiiMote\WiiClassic control thanks to BTstack.
Support for up to 4 WiiMotes/Classic (multiplayer).
iCade & iControlPad support.

... and more. 

CONTROLS
-----------

The emulator controls are the following ones:
- Virtual pad: Movement in pad, mouse and analog control of the four players. 
- Buttons B,X,A,Y,L,R: Buttons A,B,C,D,E,F.
- Button SELECT (Coin): Insert credits (UP+SELECT = 2P credits, RIGHT+SELECT = 3P credits, DOWN+SELECT = 4P credits).
- Button START: start (UP+START = 2P start, RIGHT+START = 3P start, DOWN+START = 4P start).
- Buttons L2: Exit to selection menu to select another game.
- Buttons START+SELECT (start+coin) simultaneously: Access to the MAME menu.
- Button R2: Open help, global settings.

NOTE: To type OK when MAME requires it, press LEFT and then RIGHT.

GLOBAL OPTIONS
----------------
-Smoothed image. Enable to apply a smoothing image filter over the emulator screen.

-CRT Filter. Enable to apply a CRT like filter over the image.

-Sacanline Filter. Enable to apply a scanline filter over the image.

-Keep Aspect. 'Enabled' keeps the aspect ratio; 'Disabled' will use all available screen.

-Safe Render Path (iPhone only). Enable at the expenses of performance for maximun compability. Slow in 3G (not recomended unless you find any problem).

-Full Screen (Landscape); Uses all available screen or shows the emulator windowed.

-Animated. Animates ON/OFF DPad/Stick. Disable to gain performance.

-Touch Type: Set the touch stick to works as analog stick or as digital stick.

-Stick Type: limits the joystick's range of motion: 8-way,4-way,2-way The most common reason to use a gate in an actual arcade setting is the retrofitting of an older machine that is not compatible with  a new 8-way stick. A classic example of this is Pac-Man. The game was originally designed for a 4-way stick, and is programmed  to respond only when a new input occurs. If the user is holding the stick in the down position, then suddenly makes a motion  to move to the right, what often happens is that the stick first moves into the down-right diagonal, which the game  does not recognize as new input since down is still being held. However, right is also now considered held, and when the user  completes the motion to move right, it is also not a new input, and Pac-Man will still be moving down.

-Buttons  / Button A = B + X. Show 1-4/6 Buttons: Hide/show B/Y/A/X/L/R buttons if needed. Select A=B+X to use A button as B and X simultaneous press.

-Control Layout: Configures bluetooth control layout for iCade or iControlPad.

-Sound Rate: Set the default rate for games.

-Sound Stereo: Set the default number of channels for sound, you can also select "Fast" for faster performance but lower quality and mono.

-Show FPS: Shows ON/OFF fps.

-Emu Res: Force MAME internal drawing resolution, use hires resolution to improve artwork rendering at the expense of performance. 

-Throttle: Configures the default thottling setting. When throttling is on, MAME attempts to keep the game running at the game's intended speed. When throttling is off, MAME runs the game as fast as it can.

-FS \ FS Value (Frame Skip): Specifies the frameskip value. This is the number of frames out of every 12 to drop when running. For example, if you say -frameskip 2,then MAME will display 10 out of every 12 frames. By skipping those frames, you may be able to get full speed in a game that requires more horsepower than your device has. The default value is autoframekip that Automatically determines the frameskip level while you're playing the game, adjusting it constantly in a frantic attempt to keep the game running at full speed.

-Force Pixel Aspect: Enable it to force pixel aspect ratio bypassing MAME video selection.

-Sleep on idle: Allows MAME to give time back to the system (sleep) when running with -throttle. This allows other programs to have some CPU time, assuming that the game isn't taxing 100% of your CPU resources. This option can potentially cause hiccups in performance if other demanding programs are running.

-Show Info/Warnings: Shows Game Info and any warnings when a game is selected.

-Digital Touch DZ: Enable/Disable a deadzone on DPAD touch center. It could be better for some games. Disable if you don't like it.

-Analog Touch DZ: Analog touch stick deadzone selector.  Lower to gets more sensitivity.

-Wii Classic DZ: Wii classic stick deadzone selector. Upper if you have problems with stick (controller going crazy). Lower to gets more sensitivity.

-Skin: Let's you select skin (retina or not). Retina skin looks better but needs more resources.

-Native TV-OUT:  If you like iPad 2 TVOUT mirror or you use and external 3rd party TVOUT app, you can turn off iMame4All native TVOUT.

-Overscan TV-OUT: You can set the amount of TV overscan correction.

WIIMOTE
---------

iMAME4all lets you use up to 4 WiiMotes or Wii Classic controllers over bluetooth to play (multiplayer). 

iMAME4all uses btstack project to support WiiMote:

http://code.google.com/p/btstack/

To use WiiMote you have to first launch iMAME4all menu pressing R2 button, and select WiiMote option. Then, press to find first WiiMote and make your WiiMote discoverable by pressing the 1+2 buttons at the same time. 

You can add new WiiMote anytime, selecting WiiMote option again. If a WiiMote is disconnected (battery drained) you can reconnect it or connect another WiiMote and continue playing.

Buttons mapping:

2 = B
1 = X
+ = START
- = SELECT
B = Y
A = A
home: exit game

In landscape mode touch anywhere on the screen to show the emulator options.

ICADE
-------

The best way to use iCade with iMAME4All is in fullscreen portrait mode, hit the option button and choose options. The onscreen controls will fade out when you start using the iCade buttons. To get on screen controls back, just touch the screen.

If the iCade is off (the fake coin slot light is off) just hit an iCade button or move the joystick.(you must have paired the iCade via bluetooth before) 

When the iCade turns off, the SW keyboard may popup and then backdown, this is normal don't be alarmed

iCade KEY MAPPINGS

TOP:  [RED/COIN]	[BLACK/EXIT]	[BLACK/Y]	[WHITE/B]
BOT:  [RED/START]	[BLACK/OPTION]	[BLACK/A]	[WHITE/X]

Thanks to Todd Laney for sending me patches, and Martijn Bosschaart who has supported me to get the iCade HW.

Due to the limitations of the HW not all games are suited, use WiiClassic instead if you get slowdowns or control lag.


TV-OUT
--------

To connect an iPad ot iPhone to your TV or a projector, you can either use the Apple HDMI, Component AV Cable, Apple Composite AV Cable, Apple Dock Connector to VGA Adapter, or other compatible cable.

Use TV Out settings to set up how iPad or iPhone plays videos on your TV.

When the cable is connected to a TV or projector, iMAME4all will automatically use it when playing a game.

Set the TV signal to NTSC or PAL: Choose Video > TV Signal and select NTSC or PAL. NTSC and PAL are TV broadcast standards, used in different regions. If you are in the Americas, NTSC is probably the correct choice. Elsewhere, try PAL. If you're not sure, check the documentation that came with your TV or projector.


You can set the amount of overscan corrections in options menu.

If you like iPad 2 TVOUT mirror or you use and external 3rd party TVOUT app, you can turn off iMame4All native TVOUT in options menu.


INSTALLATION
---------------

After installing, place your MAME-titled zipped roms in /sdcard/ROMs/MAME4iOS/roms  folder.

artwork/    -> Artwork directory
cfg/        -> MAME configuration files directory
nvram/      -> NVRAM files directory
roms/       -> ROMs directory
samples/    -> Samples directory
snap/       -> Screen snapshots directory
sta/        -> Save states directory


SUPPORTED GAMES
------------------

MAME4iOS Reloaded uses only '0.139u1' romset.

Games have to be copied into the roms/ folder.

ROM NAMES
------------

Romsets have to be MAME 0.139u1 ones (September 2010).

NOTE: File and directory names in Linux are case-sensitive. Put all file and directory names using low case!.


SOUND SAMPLES
----------------

The sound samples are used to get complete sound in some of the oldest games.
They are placed into the 'samples' directory compressed into ZIP files.
The directory and the ZIP files are named using low case!.


ARTWORK
----------

http://mameworld.info/mrdo/mame_artwork.html

ORIGINAL CREDITS
-------------------

- MAME 0.139u1 original version by Nicola Salmoria and the MAME Team (http://www.mame.net).

PORT CREDITS
----------------
- Port to Android by David Valdeita (Seleuco)

DEVELOPMENT

- 2012-04-08 Version 1.1. Upgraded to MAME 0.139u1. Added 4/3, pixel aspect video aspects (now works MAME menu aspect ratio selector),
improved iPad touch control layout, improved ROM manager, Added emulated resolution selector to improve artwork rendering, added configuration input menus, 
added missing options like frameskip.
- 2012-03-09 Version 1.0 WIP. First version.

KNOWN PROBLEMS
------------------

stuff pending: Don't work true analog control, Don't work local multiplayer.

- Preferences couldn't be saved. Check for write permissions. chmod 777 if needed:
  Just go to MAME4iOS.app file in your iDevice directory and set the permissions to 777.
  also needs to be on the MAME4iOS folder under /var/mobile/Media/ROMS. (recursive)

  This is what you need to do. SSH into your iPad and then run this command on the two directories like this:

  chmod -R 777 /var/mobile/Media/ROMs/MAME4IOS
  chmod -R 777 /Applications/MAME4iOS.app

  Make sure of the following:

  1) You're logged in as root
  2) You type in the commands case sensitive
  3) MAME4iOS is not running

  You can use other apps but this works for sure.


INTERESTING WEBPAGES ABOUT MAME
-----------------------------------

- http://www.mame.net/
- http://www.mameworld.net/

ART
---------

Retina skin and touch control layout thanks to Bryn Thompson. 

Thanks to: 

Todd Laney for sending me iCade patches, and Martijn Bosschaart for support me with an iCade.


MAME4iOS LICENSE
------------------

The MAME4iOS project is released under the GPL license. In addition you have some extra rights granted by a special license exception which allow you to link the MAME4iOS GPL source with the not GPL MAME source.

The exception also gives you the rights to eliminate it if you don't like it or if you want to include the MAME4iOS source in another GPL program. So, MAME4iOS is 100% GPL.

You can more easily think at it as a sort of double license. A GPL or a GPL + exception. You have all the rights of the GPL, and, if you want, some others.

The only limitation is for MAME4iOS. MAME4iOS cannot include external GPL source without the explicit permission of the source copyright holder. 

MAME LICENSE
----------------

http://www.mame.net
http://www.mamedev.com

Copyright © 1997-2012, Nicola Salmoria and the MAME team. All rights reserved. 

Redistribution and use of this code or any derivative works are permitted provided
that the following conditions are met: 

* Redistributions may not be sold, nor may they be used in a commercial product or activity. 

* Redistributions that are modified from the original source must include the complete source
code, including the source code for all components used by a binary built from the modified
sources. However, as a special exception, the source code distributed need not include 
anything that is normally distributed (in either source or binary form) with the major 
components (compiler, kernel, and so on) of the operating system on which the executable
runs, unless that component itself accompanies the executable. 

* Redistributions must reproduce the above copyright notice, this list of conditions and the
following disclaimer in the documentation and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 

