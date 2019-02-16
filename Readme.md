# MULTITOUCH FOR PUREDATA

Enabling multi-touch mode with pd-native guis, inside any patch.

This is experimental, and not guaranteed to work on any  touchscreen setup.
Any feedback welcome jyg@gumo.fr

 Demo here : https://vimeo.com/292789121

## Configuration

- Required configuration : linux pc with multitouch screen.
- Multitouch gestures (scrolling, zooming, pinch, etc...) shoud be desactivated on the O.S.. Only monotouch events have to be forwarded as mouse events by the O.S..
- Puredata 0.49
- iemguts lib externals
- hcs/screensize external (optional)
- and a special version of hidio (included). see here https://github.com/jyg/PdMultitouch/blob/master/hidio/Readme.md

## Installation
1) check you have installed iemguts externals library.

2) put the *hidio.pd_linux* file (from hidio folder) into your externals folder. Check if it works by opening hidio-help.pd. (If not, you may have to recompile it. In a terminal inside hidio folder, type  **./configure** then **make**).

3) Open the patch *multitouch.enable-help.pd*.

4) follow the 4-stages configuration in the *multitouch.settings2.pd* window.

That's all...

## Changes Log
17/12/2018	
	added custom gui modules : vfader, jogzone (pd 0.49)
