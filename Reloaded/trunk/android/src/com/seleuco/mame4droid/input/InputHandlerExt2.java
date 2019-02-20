/*
 * This file is part of MAME4droid.
 *
 *
 *   InputHandlerExt2.java is heavily based on InputHandlerExt.java.
 *
 *     * I took out most of the device brand specific handling special
 *   cases, as Android gamepad/joysticks can be handled in a fairly
 *   generic fashion.  As an example, take a look at ControllerSample.zip
 *   (https://developer.android.com/training/game-controllers/controller-input.html).
 *   It handles left and right joysticks, dpad, and gamepad button
 *   inputs, all in a robust, non-device specific manner. These changes
 *   make it easy to support any Android gamepad/joystick going
 *   forwards. It should just work, without any fuss.
 *
 *     * I took out the code that reconfigured the key mappings based on
 *  various specific devices. The MAME engine already supports
 *  reconfiguration of device input mappings, so as long as we pass it
 *  reasonable, distinct values, for a given device, the user should be
 *  able to customize it fairly easily, for their given device, using the
 *  MAME UI.
 *
 *     * I took out the stick deadzone handling. As far as I can tell,
 *  removing this stick deadzone handling actually made the controls more
 *  consistently responsive, and I couldn't see any downside, in terms of
 *  playability.
 *
 *     * If you have a gamepad with two joysticks, the two joysticks will
 *  now be mapped to joystick 1 and joystick 3, respectively. This makes
 *  it possible to play Robotron type games (games requiring two
 *  simultaneous joysticks) easily. If you add a second gamepad,
 *  it will add joysticks 2 and 4.
 *
 *     * I've added a new class to handle dpad direction button presses.
 *  Dpad.java is largely taken from a code sample provided by the Android
 *  developers
 * (https://developer.android.com/training/game-controllers/controller-input.html#dpad
 *  ). This seems to work really well and reliably, and should be able to
 *  handle dpads from any Android compatible gamepad/joystick out on the
 *  market.
 *
 *  - UChin Kim, 28 February 2018.
 *
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *
  ****************************************************************
 *
 * Copyright (C) 2015 David Valdeita (Seleuco)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses>.
 *
 * Linking MAME4droid statically or dynamically with other modules is
 * making a combined work based on MAME4droid. Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * In addition, as a special exception, the copyright holders of MAME4droid
 * give you permission to combine MAME4droid with free software programs
 * or libraries that are released under the GNU LGPL and with code included
 * in the standard release of MAME under the MAME License (or modified
 * versions of such code, with unchanged license). You may copy and
 * distribute such a system following the terms of the GNU GPL for MAME4droid
 * and the licenses of the other code concerned, provided that you include
 * the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of MAME4idroid are not
 * obligated to grant this special exception for their modified versions; it
 * is their choice whether to do so. The GNU General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 *
 * MAME4droid is dual-licensed: Alternatively, you can license MAME4droid
 * under a MAME license, as set out in http://mamedev.org/


 */

package com.seleuco.mame4droid.input;

import android.annotation.TargetApi;
import android.content.Context;
import android.hardware.input.InputManager;
import android.os.Build;
import android.util.SparseIntArray;
import android.util.Log;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.InputEvent;
import android.view.View;
import android.view.View.OnGenericMotionListener;
import android.widget.Toast;

import java.util.Arrays;

import com.seleuco.mame4droid.Emulator;
import com.seleuco.mame4droid.MAME4droid;
import com.seleuco.mame4droid.helpers.DialogHelper;
import com.seleuco.mame4droid.helpers.MainHelper;
import com.seleuco.mame4droid.helpers.PrefsHelper;


@TargetApi(Build.VERSION_CODES.HONEYCOMB_MR1)
public class InputHandlerExt2 extends InputHandler implements OnGenericMotionListener  {

    private static String LOG_TAG = "InputHandlerExt2";

    static protected int MAX_DEVICES	= 4;
    static protected int MAX_KEYS	= 250;

    protected float MY_PI	= 3.14159265f;

    public static  int deviceSlot [] = new int[MAX_DEVICES];

    // this variable is only used in one function, but here as a
    // static variable to minimize potential garbage collection delay issues.
    private static int matchedDeviceSlot [] = new int[MAX_DEVICES];

    protected int []deviceMappings = new int[MAX_KEYS];

    protected boolean gf_NVMouseExtensions;

    private Dpad dpadHandler = new Dpad();

    public InputHandlerExt2(MAME4droid value) {
        super(value);

        Arrays.fill(deviceMappings, -1);

        // I believe the only permissible values for rhs of deviceMappings
        // are:  (see IController.java, first 14 entries are the only
        // values that will be understood by the MAME emulator).
        // UP_VALUE, LEFT_VALUE, DOWN_VALUE, RIGHT_VALUE,
        // START_VALUE, COIN_VALUE,
        // A_VALUE, B_VALUE, C_VALUE, D_VALUE, E_VALUE, F_VALUE,
        // EXIT_VALUE, OPTION_VALUE

        // L1, R1
        deviceMappings[KeyEvent.KEYCODE_BUTTON_L1] = E_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_R1] = F_VALUE;

        // L2, R2
        deviceMappings[KeyEvent.KEYCODE_BUTTON_L2] = EXIT_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_R2] = OPTION_VALUE;


        // left thumb, right thumb
        deviceMappings[KeyEvent.KEYCODE_BUTTON_THUMBL] = COIN_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_THUMBR] = START_VALUE;


        deviceMappings[KeyEvent.KEYCODE_BUTTON_A] = A_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_B] = B_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_X] = C_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_Y] = D_VALUE;

        deviceMappings[KeyEvent.KEYCODE_BUTTON_Z] = E_VALUE;


        deviceMappings[KeyEvent.KEYCODE_BACK] = EXIT_VALUE;

        deviceMappings[KeyEvent.KEYCODE_BUTTON_1] = A_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_2] = B_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_3] = C_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_4] = D_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_5] = E_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_6] = F_VALUE;

        deviceMappings[KeyEvent.KEYCODE_BUTTON_7] = UP_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_8] = DOWN_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_9] = LEFT_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_10] = RIGHT_VALUE;

        deviceMappings[KeyEvent.KEYCODE_BUTTON_11] = EXIT_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_12] = OPTION_VALUE;

        deviceMappings[KeyEvent.KEYCODE_BUTTON_13] = UP_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_14] = DOWN_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_15] = LEFT_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_16] = RIGHT_VALUE;

        deviceMappings[KeyEvent.KEYCODE_BUTTON_SELECT] = COIN_VALUE;
        deviceMappings[KeyEvent.KEYCODE_BUTTON_START] = START_VALUE;

        // dpad.
        deviceMappings[KeyEvent.KEYCODE_DPAD_UP] = UP_VALUE;
        deviceMappings[KeyEvent.KEYCODE_DPAD_DOWN] = DOWN_VALUE;
        deviceMappings[KeyEvent.KEYCODE_DPAD_LEFT] = LEFT_VALUE;
        deviceMappings[KeyEvent.KEYCODE_DPAD_RIGHT] = RIGHT_VALUE;


        int ids[] = InputDevice.getDeviceIds();
        for(int i=0; i< ids.length; i++)
        {
            InputDevice inputDevice = InputDevice.getDevice(ids[i]);
            if (inputDevice == null)
                continue;

            Log.i(LOG_TAG, "detected input device: " + inputDevice.getName());
        }

        Arrays.fill(deviceSlot, -1);

        gf_NVMouseExtensions = false;
        if(mm.getPrefsHelper().isMouseEnabled())
        {
            try
            {
                Wrap_NVMouseExtensions.checkAvailable();
                gf_NVMouseExtensions = true;
            }
            catch (Throwable t) {}
        }

    }

    final public float rad2degree(float r){
        return ((r * 180.0f) / MY_PI);
    }

    protected float processAxis(InputDevice.MotionRange range, float axisvalue){
        float absaxisvalue = Math.abs(axisvalue);
        float deadzone = range.getFlat();
        //System.out.println("deadzone: "+deadzone);
        //deadzone = Math.max(deadzone, 0.2f);
        if(absaxisvalue <= deadzone ){
            return 0.0f;
        }
        float nomralizedvalue;
        if(axisvalue < 0.0f){
            nomralizedvalue = absaxisvalue / range.getMin();
        }else{
            nomralizedvalue = absaxisvalue / range.getMax();
        }

        return nomralizedvalue;
    }

    @Override
    public boolean onTouch(View view, MotionEvent event) {
        //System.out.println("touch: "+event.getRawX()+" "+event.getX()+" "+event.getRawY()+" "+event.getY());
        if(mm==null)return false;

        if(gf_NVMouseExtensions)
        {
            boolean isMouse= event.getToolType(0) == MotionEvent.TOOL_TYPE_MOUSE;
            if(isMouse)
            {
                if(isMouseEnabled)
                {
                    if (event.getActionMasked() == MotionEvent.ACTION_MOVE)
                    {
                        float flRelativeX = event.getAxisValue(Wrap_NVMouseExtensions.getAxisRelativeX(), 0);
                        float flRelativeY = event.getAxisValue(Wrap_NVMouseExtensions.getAxisRelativeY(), 0);

                        Emulator.setAnalogData(8, flRelativeX , flRelativeY);
                    }

                    int pressedButtons = event.getButtonState();
                    int beforePad = pad_data[0];

                    if ((pressedButtons & MotionEvent.BUTTON_PRIMARY) != 0) {
                        pad_data[0] |= A_VALUE;
                    }
                    else
                    {
                        pad_data[0] &= ~A_VALUE;
                    }
                    if ((pressedButtons & MotionEvent.BUTTON_SECONDARY) != 0) {
                        pad_data[0] |= B_VALUE;
                    }
                    else
                    {
                        pad_data[0] &= ~B_VALUE;
                    }
                    if ((pressedButtons & MotionEvent.BUTTON_TERTIARY) != 0) {
                        pad_data[0] |= C_VALUE;
                    }
                    else
                    {
                        pad_data[0] &= ~C_VALUE;
                    }

                    if (beforePad != pad_data[0])
                        Emulator.setPadData(0,pad_data[0]);

                }
                return true;
            }
        }
        return super.onTouch(view,event);
    }


    public boolean genericMotion(MotionEvent event){

        if (handleDPAD(event)) {
            return true;
        }

        if(gf_NVMouseExtensions)
        {
            if(Emulator.isInMAME())
            {
                if((event.getSource() & InputDevice.SOURCE_MOUSE) != 0)
                {
                    if(!isMouseEnabled)
                    {
                        isMouseEnabled = true;
                        CharSequence text = "Mouse is enabled!";
                        int duration = Toast.LENGTH_SHORT;
                        Toast toast = Toast.makeText(mm, text, duration);
                        toast.show();

                        mm.getMainHelper().updateMAME4droid();
                        resetInput();
                    }

                    //String strOutput = "";
                    if (event.getActionMasked() == MotionEvent.ACTION_HOVER_MOVE)
                    {
                        //strOutput += "Mouse Move: (" + event.getRawX() + ", " + event.getRawY() + ")\n";
                        float flRelativeX = event.getAxisValue(Wrap_NVMouseExtensions.getAxisRelativeX(), 0);
                        float flRelativeY = event.getAxisValue(Wrap_NVMouseExtensions.getAxisRelativeY(), 0);

                        //strOutput += "Relative: (" + flRelativeX + ",  " + flRelativeY + ")\n";
                        //System.out.println(strOutput);
                        Emulator.setAnalogData(8, flRelativeX , flRelativeY);
                    }

                    return true;
                }
            }
        }

        if (mm.getPrefsHelper().getInputExternal() != PrefsHelper.PREF_INPUT_USB_AUTO) {
            return false;
        }

        if (((event.getSource() & (InputDevice.SOURCE_CLASS_JOYSTICK | InputDevice.SOURCE_GAMEPAD)) == 0)
            || (event.getAction() != MotionEvent.ACTION_MOVE)) {
            return false;
        }
        int historySize = event.getHistorySize();
        for (int i = 0; i < historySize; i++) {
            processJoystickInput(event, i);
        }

        return processJoystickInput(event, -1);
    }

    @Override
    public boolean onGenericMotion(View view, MotionEvent event) {
        return false;
    }

    final public float getAxisValue(int axis, MotionEvent event, int historyPos ){
        float value = 0.0f;
        InputDevice device = event.getDevice();
        if(device!=null)
        {
            InputDevice.MotionRange range = device.getMotionRange(axis, event.getSource());
            if (range != null) {
                float axisValue;
                if (historyPos >= 0) {
                    axisValue = event.getHistoricalAxisValue(axis, historyPos);
                } else {
                    axisValue = event.getAxisValue(axis);
                }
                value = this.processAxis(range, axisValue);
                //System.out.print("x: "+x);
            }
        }
        return value;
    }

    final public float  getAngle(float x, float y){
        float ang = rad2degree((float)Math.atan(y / x));
        ang -= 90.0f;
        if (x < 0.0f)
            ang -= 180.0f;
        ang = Math.abs(ang);
        return ang;
    }

    final public float  getMagnitude(float x, float y){
        return (float) Math.sqrt((x * x) + (y * y));
    }


    protected boolean handleDPAD(InputEvent event) {

        int dev = lookupDeviceSlot(event.getDevice());
        if (dev == -1) {
            dev = assignNewDeviceSlot(event.getDevice());

            // this means the device is null
            // gobble up the bad event, as we can't do anything with it.
            if (dev == -1)
                return true;
        }

        int joy = dev != -1 ? dev : 0;

        int beforePad = pad_data[joy];

        int dpadDirections = InputHandler.LEFT_VALUE | InputHandler.RIGHT_VALUE | InputHandler.UP_VALUE | InputHandler.DOWN_VALUE;

        pad_data[joy] &= ~ (dpadDirections);

        int directionPressed = dpadHandler.getDirectionPressed(event);
        switch (directionPressed) {

        case Dpad.UP:
            pad_data[joy] |= UP_VALUE;
            break;

        case Dpad.DOWN:
            pad_data[joy] |= DOWN_VALUE;
            break;


        case Dpad.LEFT:
            pad_data[joy] |= LEFT_VALUE;
            break;

        case Dpad.RIGHT:
            pad_data[joy] |= RIGHT_VALUE;
            break;

        default:
            break;

        } // end switch.

        if (beforePad != pad_data[joy]) {
            Emulator.setPadData(joy, pad_data[joy]);
            return true;
        }

        return false;
    }



    protected boolean processJoystickInput(MotionEvent event, int historyPos){

        int dev = lookupDeviceSlot(event.getDevice());
        if (dev == -1) {
            dev = assignNewDeviceSlot(event.getDevice());
            // this means the device is null
            // gobble up the bad event, as we can't do anything with it.
            if (dev == -1)
                return true;
        }

        int joy = dev != -1 ? dev : 0;
        int alternate_joy = joy;

        // the weird numbering here is so that we can use a second
        // gamepad, which would map to joy == 1, thereby giving
        // us up to four distinct joysticks:
        //  gamepad 0: joysticks 0 and 2.
        // gamepad 1: joysticks 1 and 3.
        //
        if (joy == 0)
            alternate_joy = 2;
        else if (joy == 1)
            alternate_joy = 3;

        handleDPAD(event);

        float x = getAxisValue(MotionEvent.AXIS_X, event, historyPos);
        float y = getAxisValue(MotionEvent.AXIS_Y, event, historyPos);

        Emulator.setAnalogData(joy, x, -y);

        x = getAxisValue(MotionEvent.AXIS_Z, event, historyPos);
        y = getAxisValue(MotionEvent.AXIS_RZ, event, historyPos);

        Emulator.setAnalogData(alternate_joy, x, -y);

        return true;
    }

    public boolean onKey(View vw, int keyCode, KeyEvent event) {

        if(ControlCustomizer.isEnabled())
        {
            if(keyCode == KeyEvent.KEYCODE_BACK)
            {
                mm.showDialog(DialogHelper.DIALOG_FINISH_CUSTOM_LAYOUT);
            }
            return true;
        }

        int dev = assignNewDeviceSlot(event.getDevice());

        // dev == -1 means that event.getDevice() == null
        if(dev==-1)
        {
            if(mm.getMainHelper().getDeviceDetected() == MainHelper.DEVICE_SHIELD && event.getKeyCode()==KeyEvent.KEYCODE_BACK)
            {
                handlePADKey(/*10*/12, event);
                return true;
            }

            return super.onKey(vw, keyCode, event);
        }

        int v = deviceMappings[event.getKeyCode()];

        if(v != -1)
        {
            if(v==EXIT_VALUE)
            {
                if(event.getAction()==KeyEvent.ACTION_UP)
                {
                    if(Emulator.isInMenu())
                    {
                        Emulator.setValue(Emulator.EXIT_GAME_KEY, 1);
                        try {Thread.sleep(100);} catch (InterruptedException e) {}
                        Emulator.setValue(Emulator.EXIT_GAME_KEY, 0);
                    }
                    else if(!Emulator.isInMAME())
                    {
                        mm.showDialog(DialogHelper.DIALOG_EXIT);
                    }
                    else
                    {
                        if(mm.getPrefsHelper().isWarnOnExit())
                            mm.showDialog(DialogHelper.DIALOG_EXIT_GAME);
                        else
                        {
                            Emulator.setValue(Emulator.EXIT_GAME_KEY, 1);
                            try {Thread.sleep(100);} catch (InterruptedException e) {}
                            Emulator.setValue(Emulator.EXIT_GAME_KEY, 0);
                        }
                    }
                }
            } // end if (v == EXIT_VALUE)

            else if(v==OPTION_VALUE)
            {
                if( event.getAction()==KeyEvent.ACTION_UP)
                {
                    if(event.getDevice().getName().indexOf("OUYA")!=-1)
                        mm.showDialog(DialogHelper.DIALOG_FULLSCREEN);
                    else
                        mm.showDialog(DialogHelper.DIALOG_OPTIONS);
                }
            }
            else
            {
                int action = event.getAction();

                int beforePad = pad_data[dev];

                if(action == KeyEvent.ACTION_DOWN)
                {
                    pad_data[dev] |= v;
                }
                else if(action == KeyEvent.ACTION_UP)
                {
                    pad_data[dev] &= ~ v;
                }

                if (beforePad != pad_data[dev])
                    Emulator.setPadData(dev,pad_data[dev]);
            }

            return true;
        }

        return false;
    }

    public void setInputListeners(){

        super.setInputListeners();

        //mm.getEmuView().setOnGenericMotionListener(this);
        //mm.getInputView().setOnGenericMotionListener(this);
    }

    public void unsetInputListeners(){

        super.unsetInputListeners();

        if(mm==null)
            return;
        if(mm.getInputView()==null)
            return;
        if(mm.getEmuView()==null)
            return;

        //mm.getEmuView().setOnGenericMotionListener(null);
        //mm.getInputView().setOnGenericMotionListener(null);
    }



    protected boolean deviceIsGamepadOrJoystick(InputDevice device) {
        int sources = device.getSources();
        if (((sources & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD) ||
            ((sources & InputDevice.SOURCE_CLASS_JOYSTICK) == InputDevice.SOURCE_CLASS_JOYSTICK)) {
            return true;
        }

        return false;
    }




    protected int lookupDeviceSlot(InputDevice device) {

        if (device == null)
            return -1;

        for(int i=0; i<MAX_DEVICES; i++)
        {
            if(deviceSlot[i]==device.getId())
                return i;
        }

        return -1;
    }


    protected int assignNewDeviceSlot(InputDevice device) {

        if (device == null)
            return -1;

        int slotNumber = lookupDeviceSlot(device);
        if (slotNumber > -1)
            return slotNumber;

        Log.i(LOG_TAG, "assigning new slot for device " + device.getId());

        // clear disconnected devices
        // iterate through the current input devices list.
        // when we find a gamepad/joystick, we look up it's slot number.
        // if it has a valid slot number, we mark it in matchedDeviceSlot[].
        // If a device has been disconnected, it will never be marked,
        // so matchedDeviceSlot for that slot will remain at -1.
        // At which point, we know we can safely clear out that device's slot,
        // as it has been disconnected.
        Arrays.fill(matchedDeviceSlot, -1);

        for (int deviceId : InputDevice.getDeviceIds()) {
            InputDevice dev = InputDevice.getDevice(deviceId);
            if (dev == null)
                continue;

            if (! deviceIsGamepadOrJoystick(dev))
                continue;

            slotNumber = lookupDeviceSlot(dev);
            if (slotNumber > -1)
                matchedDeviceSlot[slotNumber] = 1;
        }

        for (int slot = 0; slot < MAX_DEVICES; slot++) {
            if ((deviceSlot[slot] > -1) && (matchedDeviceSlot[slot] < 0)) {
                Log.i(LOG_TAG, "gamepad/joystick deviceId = " + deviceSlot[slot] + " has been disconnected..");
                deviceSlot[slot] = -1;
            }
        }


        // set a default value, in case the current device does not turn
        // out to be a gamepad or joystick.
        slotNumber = -1;

        for(int i=0; i<MAX_DEVICES; i++)
        {
            if (deviceSlot[i] == -1) {
                slotNumber = i;
                break;
            }
        }

        // Tell the Emulator to handle the max possible joystick index, which
        // is 3 (range: 0 - 3, inclusive).
        //
        // There's no downside to setting the max possible joystick index to 3.
        // The upside is that we can easily configure one gamepad to send
        // joystick events for two separate joysticks. And a second gamepad
        // can similarly be configured to send joystick events for two separate
        // joysticks as well. And due to our telling the Emulator that the
        // max possible joystick index is 3 (0 based indexing), the Emulator
        // will automatically pick up any and all joystick events from joysticks
        // 1 through 4 (1 based indexing).
        //
        // 1 << 9 == MYOSD_SELECT
        Emulator.setPadData(3, 1<<9);

        if (deviceIsGamepadOrJoystick(device)) {
            Log.i(LOG_TAG, "detected gamepad/joystick deviceId = " + device.getId());
            deviceSlot[slotNumber] = device.getId();

            // fall through
        }

        return slotNumber;
    }


    public boolean isControllerDevice(){
        if(isMouseEnabled && !Emulator.isInMAME())
            isMouseEnabled = false;
        int numDevs = 0;
        for(int i=0; i<MAX_DEVICES; i++)
        {
            if(deviceSlot[i]!=-1)
                numDevs++;
        }
        return numDevs!=0 || iCade || (isMouseEnabled && !Emulator.isInMenu());
    }

    protected void setMouseVisibility(boolean fVisibility) {
        if (! gf_NVMouseExtensions) return;
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.JELLY_BEAN) return;

        InputManager inputManager = (InputManager) mm.getSystemService(Context.INPUT_SERVICE);

        Wrap_NVMouseExtensions.setCursorVisibility(inputManager, fVisibility);
    }

    public void resume(){
        super.resume();
        setMouseVisibility(false);
    }
}
