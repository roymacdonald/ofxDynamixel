# ofxDynamixel
### openFrameworks addon for controlling Robotis Dynamixel servos using their DynamixelSDK.

This was initially made as a modified version of 
[https://github.com/ghiouar/ofxDynamixel](https://github.com/ghiouar/ofxDynamixel) although right now it is a completely diffent thing, just different, dont know if better. I just modified it to better suit my needs.

### Features
* Full control of each servo with access to all the available parameters. 
* Gui (based on ofxGui, but extendable to any other via ofParameter)
* Easy to implement for other Dynamixel servos.
* Makes extensive use of smart pointers (shared_ptr, weak_ptr) so it hopefully is memory leak free.


Mostly tested with the Dynamixel XL320, XL430 and sparsely with the AX-12+.

### Install
Just copy to the addons folder and use Project Generator to add to your project.

Currently the DynamixelSDK is compiled for macos, but it should be quite straight forwards compilling it for other platforms. If you do so, just put the compiled library (dll or whatever) into the libs folder and copy the includes, in case that you use a different version than the one I've added.

### IMPORTANT
Needs to use openFrameworks from [this commit](https://github.com/openframeworks/openFrameworks/commit/8ad1fbb26bc88df40f0769830a92baaa0d2b30dd) or newer. Or use the newest nightly build.
