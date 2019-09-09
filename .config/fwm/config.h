/* see LICENSE for copyright and license */

#ifndef CONFIG_H
#define CONFIG_H

/* Button definitions, nothing to edit for you */
#define MOD1            Mod1Mask    /* ALT key */
#define MOD4            Mod4Mask    /* Super/Windows key */
#define CONTROL         ControlMask /* Control key */
#define SHIFT           ShiftMask   /* Shift key */

/* EDIT THIS: general settings */
#define MASTER_SIZE     0.6       /* master-stack ratio */
#define SHOW_PANEL      True      /* show panel by default on exec */
#define TOP_PANEL       True      /* False means panel is on bottom */
#define PANEL_HEIGHT    18        /* 0 for no space for panel, thus no panel */
#define DEFAULT_MODE    TILE      /* TILE MONOCLE BSTACK GRID FIBONACCI EQUAL */
#define ATTACH_ASIDE    False     /* False means new window is master */
#define FOLLOW_MOUSE    True      /* Focus the window the mouse just entered */
#define FOLLOW_WINDOW   True      /* Follow the window when moved to a different desktop */
#define CLICK_TO_FOCUS  True      /* Focus an unfocused window when clicked */
#define BORDER_WIDTH    3         /* window border width */
#define SCRATCH_WIDTH   1         /* scratch window border width, 0 to disable */
#define FOCUS           "#956671" /* focused window border color   */
#define UNFOCUS         "#5e81ac" /* unfocused window border color */
#define SCRATCH         "#cc0000" /* scratchpad border color */
#define DESKTOPS        9        /* number of desktops - edit DESKTOPCHANGE keys to suit */
#define DEFAULT_DESKTOP 0         /* the desktop to focus on exec */
#define MINWSZ          50        /* minimum window size in pixels */
#define USELESSGAP      1         /* the size of the useless gap in pixels */
#define GLOBALGAPS      True      /* use the same gap size on all desktops */
#define MONOCLE_BORDERS True      /* display borders in monocle mode */
#define INVERT          False     /* use alternative modes by default */
#define AUTOCENTER      True      /* automatically center windows floating by default */
#define OUTPUT_TITLE    False     /* output the title of the currently active window */
#define USE_SCRATCHPAD  True      /* enable the scratchpad functionality */
#define CLOSE_SCRATCHPAD True     /* close scratchpad on quit */
#define SCRPDNAME       "scratchpad" /* the name of the scratchpad window */
#define EWMH_TASKBAR    False      /* False if text (or no) panel/taskbar */

/*
 * EDIT THIS: applicaton specific rules
 * Open applications to specified desktop with specified mode.
 * If desktop is negative, then current is assumed. Desktops are 0-indexed.
 * The matching is done via POSIX-regexes on the window title, see
 * https://en.wikipedia.org/wiki/Regular_expression#POSIX_extended for syntax
 * Sadly, this can not be empty (for now), so enter something non-existent if
 * you do not wish to use this functionality.
 */
static const AppRule rules[] = { \
    /* title regex   desktop follow   float  border_with */
    { "st",             0,    True,   False,    3 },
    { "google-chrome",  1,    True,   False,    3 },
    { "Google Chrome",  1,    True,   False,    3 },    
    { "Google-chrome",  1,    True,   False,    3 },    
    { "subl",           2,    True,   False,    3 },
    { "Subl",           2,    True,   False,    3 },    
    { "Sublime Text",   2,    True,   False,    3 },
    { "Firefox",        3,    True,   False,    3 },

};

/* helper for spawning shell commands, usually you don't edit this */
#define SHCMD(cmd) {.com = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/*
 * EDIT THIS: commands
 * Adjust and add these to the shortcuts below to launch anything you want by
 * pressing a key (combination). The last argument should ALWAYS be a null
 * pointer. scrpcmd needs to be defined and different from all other commands
 * (like the example) so FrankenWM can tell when you want to open a scratchpad
 * window. The title of the scratchpad window should also match SCRPDNAME from
 * above
 */
static const char *scrpcmd[]        = { "st", "-e", "scratchpad", NULL };

static const char *termcmd[]        = { "st", NULL };
static const char *chromecmd[]      = { "google-chrome-stable", NULL };
static const char *rangercmd[]      = { "st","-e","ranger", NULL };
static const char *sublcmd[]        = { "subl", NULL };
static const char *firefoxcmd[]     = { "firefox",NULL};
static const char *rofiruncmd[]     = { "rofi","-show","drun", NULL };
static const char *rofiwindowcmd[]  = { "rofi","-show","window", NULL };
static const char *volumeUp[]       = { "amixer","sset","Master","5%+",NULL};
static const char *volumeDown[]     = { "amixer","sset","Master","5%-",NULL};

#define DESKTOPCHANGE(K,N) \
    {  MOD4,             K,              change_desktop, {.i = N}}, \
    {  MOD4|ShiftMask,   K,              client_to_desktop, {.i = N}},

/*
 * EDIT THIS: shortcuts
 * By default, all shortcuts use only Mod4 (+ Shift/Control), but you can use
 * Mod1 as well if you like to, I just prefer not to. (Update: handling
 * floating windows makes more sense when using Mod1 as well, so there's that)
 */
static key keys[] = {
    /* modifier          key            function           argument */

    {  MOD4,             XK_Return,     spawn,             {.com = termcmd}},
    {  MOD4,             XK_r,          spawn,             {.com = rofiruncmd}},    
    {  MOD4,             XK_w,          spawn,             {.com = rofiwindowcmd}},    
    {  MOD4,             XK_F2,         spawn,             {.com = chromecmd}},
    {  MOD4,             XK_F3,         spawn,             {.com = rangercmd}},    
    {  MOD4,             XK_F4,         spawn,             {.com = sublcmd}},  
    {  MOD4,             XK_F5,         spawn,             {.com = firefoxcmd}}, 
    {  MOD4,             XK_BackSpace,  focusurgent,       {NULL}},
    {  MOD4,             XK_q,          killclient,        {NULL}},
    /* move the current window to the center of the screen, floating */
    {  MOD4,             XK_c,          centerwindow,      {NULL}},    
    /* toggle the scratchpad terminal, if enabled */
    {  MOD4,             XK_s,          togglescratchpad,  {NULL}},    
    /* select windows */
    {  MOD4,             XK_j,          next_win,          {NULL}},
    {  MOD4,             XK_k,          prev_win,          {NULL}},
    /* resize master/first stack window */
    {  MOD4,             XK_h,          resize_master,     {.i = -10}}, /* decrease size in px */
    {  MOD4,             XK_l,          resize_master,     {.i = +10}}, /* increase size in px */
    {  MOD4,             XK_d,          resize_stack,      {.i = -10}}, /* shrink   size in px */
    {  MOD4,             XK_i,          resize_stack,      {.i = +10}}, /* grow     size in px */
    /* toggle to last desktop */
    {  MOD4,             XK_Tab,        last_desktop,      {NULL}},
    /* mode selection */
    {  MOD4,             XK_t,          switch_mode,       {.i = TILE}},
    {  MOD4,             XK_m,          switch_mode,       {.i = MONOCLE}},
    {  MOD4,             XK_b,          switch_mode,       {.i = BSTACK}},
    {  MOD4,             XK_g,          switch_mode,       {.i = GRID}},
    {  MOD4,             XK_f,          switch_mode,       {.i = FIBONACCI}},
    {  MOD4,             XK_d,          switch_mode,       {.i = DUALSTACK}},
    {  MOD4,             XK_e,          switch_mode,       {.i = EQUAL}},
    {  MOD4,             XK_z,          rotate_mode,       {.i = -1}},
    {  MOD4,             XK_x,          rotate_mode,       {.i = +1}},
    {  MOD4|SHIFT,       XK_q,          quit,              {.i = 0}}, /* quit with exit value 0 */
    {  MOD4|SHIFT,       XK_r,          quit,              {.i = 1}}, /* quit with exit value 1 */
    {  MOD4,             XK_0,          spawn,             SHCMD("~/.config/fwm/power-menu.sh") },
    {  MOD4,             XK_Print,      spawn,             SHCMD("~/.config/fwm/screenshot.sh") },
    {  MOD4|SHIFT,       XK_Print,      spawn,             SHCMD("~/.config/fwm/screenshot-w.sh") },
    {  MOD4,             XK_F1,         spawn,             {.com = volumeUp } },
    {  MOD4|SHIFT,       XK_F1,         spawn,             {.com = volumeDown } },   
    {  MOD4|SHIFT,       XK_b,          togglepanel,       {NULL}},
    /* jump to the next/previous desktop */
    {  MOD4|CONTROL,     XK_h,          rotate,            {.i = -1}},
    {  MOD4|CONTROL,     XK_l,          rotate,            {.i = +1}},
   /* jump to the next/previous desktop with just the current window */
    {  MOD4|SHIFT,       XK_h,          rotate_filled,     {.i = -1}},
    {  MOD4|SHIFT,       XK_l,          rotate_filled,     {.i = +1}},
    /* jump to the next/previous desktop with just the current window */
    {  MOD4|CONTROL|SHIFT, XK_h,        rotate_client,     {.i = -1}},
    {  MOD4|CONTROL|SHIFT, XK_l,        rotate_client,     {.i = +1}},
    /* select the master window, or the previously focussed slave */
    {  MOD4|SHIFT,       XK_w,          focusmaster,       {NULL}},
    /* move windows */
    {  MOD4|SHIFT,       XK_j,          move_down,         {NULL}},
    {  MOD4|SHIFT,       XK_k,          move_up,           {NULL}},
    /* reset the selected floating window to tiling */
    {  MOD4|SHIFT,       XK_t,          tilemize,          {NULL}},
    /* swap the current window to master */
    {  MOD1,             XK_Return,     swap_master,       {NULL}},
    /* maximize the current window */
    {  MOD1,             XK_f,          maximize,          {NULL}},
    /* minimize window to queue/pull window from queue */
    {  MOD1,             XK_m,          minimize,          {NULL}},
    {  MOD1,             XK_n,          restore,           {NULL}},
    /* toggles inverted stacking modes (left/top stack) */
    {  MOD1|SHIFT,       XK_i,          invertstack,       {NULL}},
    /* show/hide all windows on all desktops */
    {  MOD1|CONTROL,     XK_s,          showhide,          {NULL}},
    /* move floating windows */
    {  MOD4|MOD1,        XK_j,          float_y,           {.i = +10}},
    {  MOD4|MOD1,        XK_k,          float_y,           {.i = -10}},
    {  MOD4|MOD1,        XK_h,          float_x,           {.i = -10}},
    {  MOD4|MOD1,        XK_l,          float_x,           {.i = +10}},
    /* resize floating windows */
    {  MOD4|MOD1|CONTROL,XK_j,          resize_y,          {.i = +10}},
    {  MOD4|MOD1|CONTROL,XK_k,          resize_y,          {.i = -10}},
    {  MOD4|MOD1|CONTROL,XK_h,          resize_x,          {.i = -10}},
    {  MOD4|MOD1|CONTROL,XK_l,          resize_x,          {.i = +10}},
    /* resize the borders */
    {  MOD4|CONTROL,     XK_u,          adjust_borders,    {.i = -1}},
    {  MOD4|CONTROL,     XK_i,          adjust_borders,    {.i = +1}},
    /* resize the useless gaps between the windows */
    {  MOD4|CONTROL,     XK_o,          adjust_gaps,       {.i = -1}},
    {  MOD4|CONTROL,     XK_p,          adjust_gaps,       {.i = +1}},
    /* desktop selection */
       DESKTOPCHANGE(    XK_1,                             0)
       DESKTOPCHANGE(    XK_2,                             1)
       DESKTOPCHANGE(    XK_3,                             2)
       DESKTOPCHANGE(    XK_4,                             3)
       DESKTOPCHANGE(    XK_5,                             4)
       DESKTOPCHANGE(    XK_6,                             5)
       DESKTOPCHANGE(    XK_7,                             6)
       DESKTOPCHANGE(    XK_8,                             7)
       DESKTOPCHANGE(    XK_9,                             8)
};

/* EDIT THIS: mouse-based shortcuts */
static Button buttons[] = {
    /* move/resize using the mouse */
    {  MOD4,    Button1,     mousemotion,   {.i = MOVE}},
    {  MOD4,    Button3,     mousemotion,   {.i = RESIZE}},
    {  MOD1,    Button3,     spawn,         {.com = rofiruncmd}},
};
#endif

