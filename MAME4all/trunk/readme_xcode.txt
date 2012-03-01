Some notes on compiling and debugging on XCode 4 using a Jailbroken device.

The initial setting up is a little tricky as XCode will not codesign the compiled code so it will not run on the iOS device. The trick is to setup XCode 4 as follows. Follow the steps mentioned on this website. For XCode 4 follow the steps exactly as mentioned in comments "Xcoder July 15th, 2011 - 04:00"
http://www.alexwhittemore.com/?p=398 

Those comments are:
=================================================================================
1. Create the self-signed cert.
2. Install AppSync on your device.
3. Edit /Developer/Platforms/iPhoneOS.platform/Info.plist
4. For each project, copy /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.3.sdk/Entitlements.plist to your project and add get-task-allow to the bottom of it. Edit Build Settings -> Code Signing -> Code Signing Entitlements and set it to Entitlements.plist
This removes some old steps:
1. There is no need to edit SDKSettings.plist because we.re letting Xcode do the signing/entitlements.
2. There is no need for the Xcode binary patch.
3. There is no need for custom build phases or the gen_entitlements.py script.
=================================================================================

It's actually easier to setup in XCode 4 than earlier versions. The Entitlements.plist file and configuration should already be included with this Project. 

NOTE: The default iMAME4all executable name is "mame", XCode won't accept the name being different than the application so it needs to be called "iMAME4all". 

You'll also need the private frameworks from an iphone O/S firmware. The following directories with files from the iPhone O/S should exist under the project's iphoneos/ directory:
System/Library/PrivateFrameworks
System/Library/Frameworks
usr/lib

To debug iMAME4all on a device you need make sure the resource files are accessible, as XCode will install the application somewhere in the /var/media/Applications/ directory and not in /Applications. Make sure /Applications/iMAME4all.app/ exists with all the files but delete "iMAME4all" exe and "Info.plist" from there. iMAME4all will then run from XCode and pickup the necessary resource files. You'll need to edit "src/iOS/shared.h" definition IMAMEBASEPATH in the MYDEBUG section to point to whatever path XCode allocated on your device.

When swapping between Debug and Release versions make sure the relevant iMAME4all and Info.plist is removed from the other application directory and respring. You can only have one of these on a device at a time and having two will confure the iOS device.

This is all setup only once per project.

NOTE: If you receive the error "User interaction is not allowed." it means the keychain needs unlocking: 
security unlock-keychain ~/Library/Keychains/login.keychain
