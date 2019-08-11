#!/bin/bash

# small power menu using rofi, i3, systemd and pm-utils
# (last 3 dependencies are adjustable below)
# tostiheld, 2016
# Updated : viyoriya 2019

Lock_command="i3exit lock"
Exit_command="i3exit exit"
suspend_command="systemctl suspend"
hibernate_command="systemctl hibernate"
Reboot_command="systemctl reboot"
Shutdown_command="systemctl poweroff"


# you can customise the rofi command all you want ...
rofi_command="rofi -width 11 -height 15 -lines 6 -hide-scrollbar -bg #586e75 -opacity 60 -padding 2 -yoffset -300 -xoffset 567"
#-show-icons yes -yoffset 300 -xoffset 300
options=$' Lock\n Exit\n Suspend\n Hibernate\n Reboot\n Shutdown' 

# ... because the essential options (-dmenu and -p) are added here
#eval \$"$(echo "$options" | $rofi_command -dmenu -p " ")_command"

eval \$"$(echo "$options" | $rofi_command -dmenu -p '' | awk '{print $2}')_command"
