The Powder Toy (Subframe Chipmaker Mod)
=======================================

This is a mod of The Powder Toy for subframe chipmakers. Subframe technology refers to a collection of tricks used to reduce computation cycles in electronic components to a single frame.

Features
========

These features are enabled when you enter the Lua command `tpt.setdebug(0x8)` into the console (or you can put it in autorun.lua):

- Particle order reloading: if you use the brush or do a copy-paste, then advance the simulation, the frame will be completed and the particle order will be reloaded automatically. You can reload the particle order manually with Shift-F5.
- Shift-Space runs the simulation particle-by-particle rather than frame-by-frame.
- Shift-R starts a recording of the particle-by-particle simulation and automatically stops recording at the end of the frame. Recording can still be stopped with R but particle-by-particle simulation will still continue.
- Alt-F continues updating particles until it encouters an "interesting" update (create_part, delete_part or part_change_type called), and does not display any log messages until the frame is completed.
- Overwriting a local save "<save>.cps" will create a backup of the file you're overwriting at "<save>.cps.backup". Subframe development is dangerous.

These features will be present without enabling:

- Stacked particles are shown in the debug HUD.
- P opens the property tool window rather than takes a screenshot (you can still take screenshots with F2).
- The property tool sets temp values in celsius rather than kelvin by default. Add "K" to the back to set in kelvin.
- The ctype of FILTs will be displayed in the debug HUD. In the original game, this was only shown for non-FILT coloured particles like BRAY.
- DRAY is coloured bright yellow to distinguish it from ARAY and DTEC.
- When pasting (or placing a stamp), the paste boundary can cross outside the window boundary. Particles can also be moved out of the initial paste boundary (with the arrow keys) without getting deleted (merged in vanilla snapshot). Additionally, the white dotted paste boundary will not be shown.
- If you attempt to open a save or close the window with the ESC button (the case for closing with the 'X' button has not been implemented) when there are unsaved changes, a confirmation warning will be displayed.
- The position in frame is saved into undo history during subframe debugging, so you can undo into the middle of a frame without destroying everything.
- (v1.1) Stack tool (Shortcut: Shift-S): Clicking on a stack of particles will unstack them; selecting multiple particles in different positions will stack them in order of their positions.
- (v1.1) Creating CRAY with the brush gives it a ctype of SPRK automatically. If you want to create a ctype-less CRAY, use the property tool.
- (v1.1) Shift-; (semicolon) toggles stack mode. It allows you to draw over existing particles, and makes right-click delete one stacked particle at a time. This helps to make transparent DTEC.
- (v1.2) DTEC is coloured a darker red to distinguish it from ARAY.
- (v1.3) "filt:v" in property tool translates into (v<<8) + 125, to aid the configuration of CRAY that creates FILT with a preset tmp.
- (v1.6) 30th-bit handling: Adding "c" before typing in a number into the property tool when setting ctype will set the 30th bit. For example, "c50" will set the ctype to (50 | 0x20000000). Works with hex too -- just add "0x", like in "c0xC0FFEE". Even without "c", setting the ctype of colored particles using the property tool will not set the 31st and 32nd bit.
- (v1.6) Ctrl-J toggles the colored particle ctype display mode. This changes how the ctype of a colored particle is displayed in the debug HUD. The ctype is displayed in hex by default, but you can switch it back to decimal. For decimal, you can choose to enable 30th-bit handling. This ignores the 30th bit and, if the 29th bit is set, displays the ctype as a negative number.

Note that the original game already supports the following subframe debugging features:

- Shift-F updates all particles up to the particle where your mouse is at.
- Alt-F updates a single particle. This behaviour has been modified in this mod to continue updating particles until an "interesting" update occurs.

Changelog
=========

v1.0:
- Original release.

v1.1:
- Merge changes in snapshot.
- Add stack tool.
- Add stack mode.
- Give drawn CRAY a ctype of SPRK.

v1.2:
- Merge changes in 92.0.
- Change DTEC colour.

v1.3:
- Merge changes in 92.5.
- Add "filt:v" property tool syntax.

v1.4:
- Fix crash when pasting walls outside window boundaries.
- Notify in HUD when more than 5 particles are below the cursor.
- Warn instead of block when stacking more than 5 particles with stack tool.
- Unstack as many particles as possible when unstacking with stack tool.
- Merge changes in snapshot, including fix for Mac.
- Extend 30th-bit handling to PHOT.

v1.5:
- Don't trigger particle order reloading when SPRKing with brush.

v1.6:
- Merge changes in 93.3.
- Allow property tool to set temperature in kelvin.
- Make property tool 30th-bit handling opt-in.
- Allow spectral data to be displayed in hex and unmodified decimal.
