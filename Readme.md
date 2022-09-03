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
- and a special version of hidio . see here https://github.com/jyg/hidio

## Installation
1) check you have installed iemguts externals library.

2) put the *hidio.pd_linux* file (from hidio folder) into your externals folder. Check if it works by opening hidio-help.pd. (If not, you may have to recompile it. In a terminal inside hidio folder, type  **./configure** then **make**).

3) Open the patch *multitouch-help.pd*.

4) follow the 4 steps configuration procedure in the *multitouch.settings2.pd* window.
![image](https://user-images.githubusercontent.com/1431894/188274136-1ec0e88b-06b5-4a78-a4fd-26cdd6728e2d.png)

That's all...

## Ubuntu 20.04 and input device access permission
see this issue https://github.com/jyg/multitouch/issues/2

## Changes Log
17/12/2018	
	added custom gui modules : vfader, jogzone (pd 0.49)
