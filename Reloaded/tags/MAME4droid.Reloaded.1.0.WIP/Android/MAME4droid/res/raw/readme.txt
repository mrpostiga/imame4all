=================================================================
MAME4droid Reloaded (0.134u4 ) 1.0 WIP (February 27, 2012) 
by David Valdeita (Seleuco)
=================================================================


INTRODUCTION
---------------

MAME4droid Reloaded is developed by David Valdeita (Seleuco), port of MAME 0.134u4 emulator by Nicola Salmoria and TEAM. 

MAME4droid Reloaded emulates arcade games supported by original MAME 0.134u4.

This MAME4droid version is targeted to Dual-Core devices (1GHz and 512MB RAM minimum), because it is based on a high specs 2009 PC MAME build.
Anyway don't expect arcade games of the 90 to work at full speed. With some games that are really bad optimized (like outrun or mk series) you will 
need at least a 1.5 ghz dual-core device. This is related to MAME build used, since it is  targeted to high specs PC's as i said before. 
This version doesn't have an uml back end ARM dynamic recompiler, which means drivers based on high specs arcade CPUs won't be playable 
(it has not sense since this games will be slow in any case).

Said that, with a low end device, use at your own risk. I suggest you use MAME4droid (0.37b5) instead.
Remember that games that can be emulated on both MAME4droid versions will run much faster on MAME4droid (0.37b5) than on MAME4droid Reloaded (0.134),
and will drain less battery.

This version emulates over 8000 different romsets. 

Please, try to understand that that with that amount of games, some will run better than others and some might not even run with MAME4droid Reloaded. 
Please, don't email me asking for a specific game to run.

Tips to help performance: use lower quality sound or switch it off. Disable stick and buttons animations and disable smooth scaling also.

After installing, place your MAME-titled zipped roms in /sdcard/ROMs/MAME4droid/roms folder.

MAME4droid Reloaded uses only '0.134u4' romset.

Official web page for news, source code & additional information:

http://code.google.com/p/imame4all/

To see MAME license, go to the end of this document.

Features
------------

Support for 2.1 and upper Android devices. 
Native support for Android Honeycomb tablets.
Autorotate.
HW Keys remapping.
Touch Controller can be shown/hidden.
Smooth image.
Overlay Filters, scalines, CRT..
Digital or Analog touch selectable.
Animated touch stick or DPAD.
Button Layout customizable control. 
iON's iCade and iCP (as iCade mode) external controllers supported. 
Wiimote support using WiiCrotroller Market app.
Tilt Sensor as left/right.
1 to 6 buttons optionally shown.
Options for video aspect ratio, scaling, rotate.

... and more. 

CONTROLS
-----------

The emulator controls are the following ones:
- Virtual pad: Movement in pad, mouse and analog control of the four players. 
- Buttons B,X,A,Y,L,R: Buttons A,B,C,D,E,F.
- Button SELECT (Coin): Insert credits (UP+SELECT = 2P credits, RIGHT+SELECT = 3P credits, DOWN+SELECT = 4P credits).
- Button START: start (UP+START = 2P start, RIGHT+START = 3P start, DOWN+START = 4P start).
- Buttons L2: Exit to selection menu to select another game.
- Buttons START+SELECT simultaneously: Access to the MAME menu.
- Button R2: Open help, global settings.

NOTE: To type OK when MAME requires it, press LEFT and then RIGHT.

GLOBAL OPTIONS
----------------

-Video render Mode: 

    * SW: SW render, more accurate. Higher device compatibility.
    * GL. Open GL ES 1.0 or upper. This should be your choice if it works fine for you. Faster rendering even with image filtering.

-Threaded sound. Worse sound quality but smoother gameplay when frame drops.

-Frame Skip: Specifies the frameskip value. This is the number of frames out of every 12 to drop when running. For example, if you say -frameskip 2,then MAME will display 10 out of every 12 frames. By skipping those frames, you may be able to get full speed in a game that requires more horsepower than your computer has. The default value is autoframekip that Automatically determines the frameskip level while you're playing the game, adjusting it constantly in a frantic attempt to keep the game running at full speed.
	 
-Throttle: Configures the default thottling setting. When throttling is on, MAME attempts to keep the game running at the game's intended speed. When throttling is off, MAME runs the game as fast as it can. Note that the fastest speed is more often than not limited by your graphics card, especially for older games.	 
	
-Sound: Enable or disable sound altogether. Also Sets the audio sample rate. Smaller values (e.g. 11025) cause lower audio quality but faster emulation speed. Higher values (e.g. 48000) cause higher audio quality but slower emulation speed.
		 
-Show FPS: Shows ON/OFF fps.

-Show Info/Warnings: Shows Game Info and any warnings when a game is selected.

-Cheats: Enables the reading of the cheat database, if present, and the Cheat menu in the user interface.

-Debug Mode. Enable debug mode. Only for developers.

-Change ROMs path: Change current ROMs path. You need to restart app. You must move roms from older folder to the new one also.

-Save battery: Allows MAME to give time back to the system (sleep) when running with -throttle. This allows other programs to have some CPU time, assuming that the game isn't taxing 100% of your CPU resources. This option can potentially cause hiccups in performance if other demanding programs are running.

-Define Keys. Let you define or map the HW keys to emulator controls. (Xperia Play and any other devices with physical keyboards users should configure their buttons or keys here)

-Restore Keys. Restore key mappings to defaults.

-Customize touch layout: Select to customize landscape touch control layout. You should press 'back' when you finish.

-Default touch layout. Restore landscape control layout to default values.

-Animated. Animates ON/OFF DPad/Stick. Disable to for better performance.

-Vibrate on keypress. Enable/Disable to let device vibrate when buttons or dpad/stick is touched.

-Touch Type:

     * Digital (DPAD). The controller is a digital DPAD. Some games need it or are better suited for this kind of controller.
     * Analog (Performance). The controller is a full analog stick, but drawed for performance.
     * Analog (Pretty). The controller is a full analog stick. 

-Stick Type: limits the joystick's range of motion: 8-way,4-way,2-way The most common reason to use a gate in an actual arcade setting is the retrofitting of an older machine that is not compatible with  a new 8-way stick. A classic example of this is Pac-Man. The game was originally designed for a 4-way stick, and is programmed  to respond only when a new input occurs. If the user is holding the stick in the down position, then suddenly makes a motion  to move to the right, what often happens is that the stick first moves into the down-right diagonal, which the game  does not recognize as new input since down is still being held. However, right is also now considered held, and when the user  completes the motion to move right, it is also not a new input, and Pac-Man will still be moving down.

-Full screen buttons (landscape) 1-4). Show 1-4 Buttons: Hide/show Y/A/X buttons if needed. Select A=B+X to use A button as B and X simultaneous press.

-Digital Touch Dead Zone: Enable/Disable a deadzone on DPAD touch center. It could be better for some games. Disable if you don't like it.

-Analog Touch Dead Zone: Select the deadzone amount on stick touch center.

-External Controller

   * Default. Select this value to use an external keyboard or devices based on keyboard IMES like WiiController.
   * iCade. Select this value to use iON's iCade controller. You should be bluetooth paired before.
   * iCP. Select this value to use ICP layout. iCP should be configured on iCade mode.
   
-Tilt sensor. Enable to use tilt sensor as left/right.

-Tilt sensor dead zone.  Select the deadzone amount on tilt sensor.

-Tilt sensor sensitivity: Set tilt sensor sensitivity.  

-Trackball sensitivity: Set trackball persistance.

-Trackball fire only: Disable trackball movement.

-Scaling Mode:  
     
     * Original.
     * 1.5X: 1.5 original size. 
     * 2X: Double original size.
     * 2.5X: 2.5 original size. 
     * Keep Aspect: keeps the aspect ratio
     * Stretch to fit screen, will use all available screen.
     
-Filter overlay. Applies an image filter (scanlines or CRT) at the expense of performance.      

-Touch controller visible: Hide/Show the touch controller. Disable if you want to use an external controller like a keyboard or Wiimote.

-Smooth scaling: Turn on bitmap filtering at the expense of performance.


INSTALLATION
---------------

After installing, place your MAME-titled zipped roms in /sdcard/ROMs/MAME4droid/roms  folder.

artwork/    -> Artwork directory
cfg/        -> MAME configuration files directory
nvram/      -> NVRAM files directory
roms/       -> ROMs directory
samples/    -> Samples directory
snap/       -> Screen snapshots directory
sta/        -> Save states directory


SUPPORTED GAMES
------------------

MAME4droid Reloaded uses only '0.134u4' romset.

Games have to be copied into the roms/ folder.

ROM NAMES
------------

Romsets have to be MAME 0.134u4 ones (September 2009).

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

- MAME 0.134u4 original version by Nicola Salmoria and the MAME Team (http://www.mame.net).

PORT CREDITS
----------------
- Port to Android by David Valdeita (Seleuco)

DEVELOPMENT

- 2012-02-27 Version 1.0 WIP. First version.

KNOWN PROBLEMS
------------------

-  A lot... this is a work in progress version. :)

Don't work true analog control, standard or pixel aspect video options, input options...
Don't work local multiplayer.
Don't work 4 player selector.


INTERESTING WEBPAGES ABOUT MAME
-----------------------------------

- http://www.mame.net/
- http://www.mameworld.net/

ART
---------

Retina skin and touch control layout thanks to Bryn Thompson. 

Thanks to: 

Todd Laney for sending me iCade patches, and Martijn Bosschaart for support me with an iCade.


MAME4droid LICENSE
------------------

The MAME4droid project is released under the GPL license. In addition you have some extra rights granted by a special license exception which allow you to link the MAME4droid GPL source with the not GPL MAME source.

The exception also gives you the rights to eliminate it if you don't like it or if you want to include the MAME4droid source in another GPL program. So, MAME4droid is 100% GPL.

You can more easily think at it as a sort of double license. A GPL or a GPL + exception. You have all the rights of the GPL, and, if you want, some others.

The only limitation is for MAME4droid. MAME4droid cannot include external GPL source without the explicit permission of the source copyright holder. 

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

