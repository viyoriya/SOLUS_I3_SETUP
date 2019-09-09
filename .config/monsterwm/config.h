/* see LICENSE for copyright and license */

#ifndef CONFIG_H
#define CONFIG_H

/** modifiers **/
#define MOD1            Mod1Mask    /* ALT key */
#define MOD4            Mod4Mask    /* Super/Windows key */
#define CONTROL         ControlMask /* Control key */
#define SHIFT           ShiftMask   /* Shift key */

/** generic settings **/
#define MASTER_SIZE     0.52
#define SHOW_PANEL      True      /* show panel by default on exec */
#define TOP_PANEL       True      /* False means panel is on bottom */
#define PANEL_HEIGHT    18        /* 0 for no space for panel, thus no panel */
#define DEFAULT_MODE    TILE      /* initial layout/mode: TILE MONOCLE BSTACK GRID FLOAT */
#define ATTACH_ASIDE    False      /* False means new window is master */
#define FOLLOW_WINDOW   True      /* follow the window when moved to a different desktop */
#define FOLLOW_MOUSE    True      /* focus the window the mouse just entered */
#define CLICK_TO_FOCUS  True      /* focus an unfocused window when clicked  */
#define FOCUS_BUTTON    Button3   /* mouse button to be used along with CLICK_TO_FOCUS */
#define BORDER_WIDTH    3         /* window border width */
#define FOCUS           "#956671" /* focused window border color    */
#define UNFOCUS         "#5e81ac" /* unfocused window border color  */
#define MINWSZ          50        /* minimum window size in pixels  */
#define DEFAULT_DESKTOP 0         /* the desktop to focus initially */
#define DESKTOPS        9         /* number of desktops - edit DESKTOPCHANGE keys to suit */

/**
 * open applications to specified desktop with specified mode.
 * if desktop is negative, then current is assumed
 */
static const AppRule rules[] = { \
    /*  class     desktop  follow  float */
    { "St",             0,    True,   False  },
    { "Google-chrome",  1,    True,   False  },
    { "Subl",           2,    True,   False  },
    { "Firefox",        3,    True,   False  },
};

/* helper for spawning shell commands */
#define SHCMD(cmd) {.com = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/**
 * custom commands
 * must always end with ', NULL };'
 */
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

/**
 * keyboard shortcuts
 */
static Key keys[] = {
    /* modifier          key            function           argument */
    {  MOD4,             XK_Return,     spawn,             {.com = termcmd}},
    {  MOD4,             XK_r,          spawn,             {.com = rofiruncmd}},    
    {  MOD4,             XK_w,          spawn,             {.com = rofiwindowcmd}},    
    {  MOD4,             XK_F2,         spawn,             {.com = chromecmd}},
    {  MOD4,             XK_F3,         spawn,             {.com = rangercmd}},    
    {  MOD4,             XK_F4,         spawn,             {.com = sublcmd}},  
    {  MOD4,             XK_F5,         spawn,             {.com = firefoxcmd}}, 
    {  MOD4,             XK_b,          togglepanel,       {NULL}},
    {  MOD4,             XK_BackSpace,  focusurgent,       {NULL}},
    {  MOD4,             XK_q,          killclient,        {NULL}},
    {  MOD4,             XK_j,          next_win,          {NULL}},
    {  MOD4,             XK_k,          prev_win,          {NULL}},
    {  MOD4,             XK_h,          resize_master,     {.i = -10}}, /* decrease size in px */
    {  MOD4,             XK_l,          resize_master,     {.i = +10}}, /* increase size in px */
    {  MOD4,             XK_d,          resize_stack,      {.i = -10}}, /* shrink   size in px */
    {  MOD4,             XK_i,          resize_stack,      {.i = +10}}, /* grow     size in px */
    {  MOD4|CONTROL,     XK_h,          rotate,            {.i = -1}},
    {  MOD4|CONTROL,     XK_l,          rotate,            {.i = +1}},
    {  MOD4|SHIFT,       XK_h,          rotate_filled,     {.i = -1}},
    {  MOD4|SHIFT,       XK_l,          rotate_filled,     {.i = +1}},
    {  MOD4,             XK_Tab,        last_desktop,      {NULL}},
    {  MOD4,             XK_t,          switch_mode,       {.i = TILE}},
    {  MOD4,             XK_m,          switch_mode,       {.i = MONOCLE}},
    {  MOD4,             XK_b,          switch_mode,       {.i = BSTACK}},
    {  MOD4,             XK_g,          switch_mode,       {.i = GRID}},
    {  MOD4,             XK_f,          switch_mode,       {.i = FLOAT}},
    {  MOD4|SHIFT,       XK_q,          quit,              {.i = 0}}, /* quit with exit value 0 */
    {  MOD4|SHIFT,       XK_r,          quit,              {.i = 1}}, /* quit with exit value 1 */
    {  MOD4,             XK_0,          spawn,             SHCMD("~/.config/monsterwm/power-menu.sh") },
    {  MOD4,             XK_Print,      spawn,             SHCMD("~/.config/monsterwm/screenshot.sh") },
    {  MOD4|SHIFT,       XK_Print,      spawn,             SHCMD("~/.config/monsterwm/screenshot-w.sh") },
    {  MOD4,             XK_F1,         spawn,             {.com = volumeUp } },
    {  MOD4|SHIFT,       XK_F1,         spawn,             {.com = volumeDown } },        
    {  MOD1,             XK_Return,     swap_master,       {NULL}},
    {  MOD1|SHIFT,       XK_j,          move_down,         {NULL}},
    {  MOD1|SHIFT,       XK_k,          move_up,           {NULL}},
    {  MOD1,             XK_j,          moveresize,        {.v = (int []){   0,  25,   0,   0 }}}, /* move down  */
    {  MOD1,             XK_k,          moveresize,        {.v = (int []){   0, -25,   0,   0 }}}, /* move up    */
    {  MOD1,             XK_l,          moveresize,        {.v = (int []){  25,   0,   0,   0 }}}, /* move right */
    {  MOD1,             XK_h,          moveresize,        {.v = (int []){ -25,   0,   0,   0 }}}, /* move left  */
    {  MOD1|SHIFT,       XK_j,          moveresize,        {.v = (int []){   0,   0,   0,  25 }}}, /* height grow   */
    {  MOD1|SHIFT,       XK_k,          moveresize,        {.v = (int []){   0,   0,   0, -25 }}}, /* height shrink */
    {  MOD1|SHIFT,       XK_l,          moveresize,        {.v = (int []){   0,   0,  25,   0 }}}, /* width grow    */
    {  MOD1|SHIFT,       XK_h,          moveresize,        {.v = (int []){   0,   0, -25,   0 }}}, /* width shrink  */
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

/**
 * mouse shortcuts
 */
static Button buttons[] = {
    {  MOD4,    Button1,     mousemotion,   {.i = MOVE}},
    {  MOD4,    Button3,     mousemotion,   {.i = RESIZE}},
    {  MOD1,    Button3,     spawn,         {.com = rofiruncmd}},
};
#endif

/* vim: set expandtab ts=4 sts=4 sw=4 : */
