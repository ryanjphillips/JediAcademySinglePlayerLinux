Speed Academy
=============

Source port of the singleplayer of Star Wars Jedi Knight: Jedi Academy. Focuses on staying true to the original game, possibly for speedrun purposes. Based on the original source code released by Raven, see README.txt

New console variables:
```
// cg_
cg_drawMovementRestriction  (0-1) default:"0" Draw the current movement restriction. -- represents no restrictions.
cg_drawOverbounceInfo       (0-1) default:"0" Draw overbounce probabilities, G is for Go, J is for Jump
cg_drawSpeedrunTotalTimer   (0-3) default:"0" Draw the total run timer.
cg_drawSpeedrunLevelTimer   (0-3) default:"0" Draw the current level timer.
cg_drawStrafeHelper         (0-1) default:"0" Draw the strafe helper.
cg_strafeHelperCenter       (0-1) default:"1" Modify the strafe helper.
cg_strafeHelperCenterMarker (0-1) default:"1" Modify the strafe helper.
cg_strafeHelperHeight       (#) default:"20"  Modify the strafe helper.
cg_strafeHelperScale        (#) default:"4"   Modify the strafe helper.
cg_strafeHelperY            (#) default:"50"  Modify the strafe helper.

// g_
g_stickLandings             (0-1) default:"1" Disable the slowdown applied when landing.
g_disableCrouchBoosts       (0-1) default:"0" Disable "crouch boosting".
g_fixSpinGlitch             (0-1) default:"0" Disable "spin glitch".
g_disableRandomBoosts       (0-1) default:"0" Disable "random" boosts. Cheat protected.
g_selfKnockback             (0-1) default:"0" Disable the self knockback restriction. Cheat protected.

// sv_ 
sv_speedrunModeIL           (0-1) default:"0" Individual-level run mode. When set to 1, timer will reset every time an autosave is loaded. When set to 0, timer will reset only when yavin1b is loaded.
```
