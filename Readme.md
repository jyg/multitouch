# MULTITOUCH FOR PUREDATA

 Enabling pseudo-multi-touch mode with pd-native guis, inside any patch.
 This is higly experimental, and not guaranteed to work on any other touchscreen setup than mine.
 Demo here : https://vimeo.com/292789121

To achieve this, we use 2 components :
* a custom executable, TouchscreenSend, derivated from evtest, that catches screentouch events and sends them by osc to the port 7000 on local host.
* a set of pd-abstactions receiving those osc data and converting them into simulated mouse events sent to the gui-patch.

## FIRST INSTALL GUIDELINES

- Required configuration : linux pc with multitouch screen.
- Multitouch gestures (scrolling, zooming, pinch, etc...) shoud be desactivated on the O.S.
- Puredata 0.49, with ggee/shell and iemguts lib externals

1) Install  / launch evtest program in a console ;

2) In the displayed list, locate the address of your touchscreen input device on your system
	 (example : "/dev/input/event17:	ELAN Touchscreen" ) ;

3) Open the patch multitouch.settings.pd ;

4) Edit the messagebox connected to the 3rd outlet, fill it with the path to the TouchscreenSend program followed by the address of the touchscreen device on your system ;
	(example [/home/jyg/TouchscreenSend /dev/input/event17(

5) According to your system, you shoud also change the screen and touch device resolution values ;
	You can get the touchscreen resolution by launching again evtest and specifying the device number, and then searching for the lines "Event code 60 (ABS_MT_TOOL_X)" and  "Event code 61 (ABS_MT_TOOL_Y)" and getting the Max values
   
6) Save and close the patch.

7) You should now use the native pd-gui objects in pseudo-multitouch mode. Test with multitouch.enable-help.pd

8) To add the multitouch features to your pd-project, you'll have to add the path to the multitouch abstractions
## BUGS

-Allways close the patch before leaving puredata. If no, the process TouchscreenSend launched by ggee/shell will freeze pd.
-Don't edit multitouch.enable, because it does dynamic patching on loadbang and won't work properly if modified.
