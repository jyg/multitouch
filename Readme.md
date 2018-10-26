# MULTITOUCH FOR PUREDATA

Enabling pseudo-multi-touch mode with pd-native guis, inside any patch.

This is higly experimental, and not guaranteed to work on any  touchscreen setup.
Any feedback wellcome jyg@gumo.fr

 Demo here : https://vimeo.com/292789121

## FIRST INSTALL GUIDELINES

- Required configuration : linux pc with multitouch screen.
- Multitouch gestures (scrolling, zooming, pinch, etc...) shoud be desactivated on the O.S.. Only monotouch events have to be forwarded as mouse events by the O.S..
- Puredata 0.49, with hcs/screensize (optional), iemguts lib externals, and a special version of hidio (included)

1) check you have installed iemguts externals library.

2) put the hidio.pd_linux file i(from hidio folder) nto your externals folder. Check it works by opening hidio-help.pd. (If not, you may have to recompile it. In a terminal inside hidio folder, type  **./configure** then **make**).

3) Open the patch multitouch.enable-help.pd.

4) follow the 3-stages configuration in the multitouch.settings pd-window.

That's all...
