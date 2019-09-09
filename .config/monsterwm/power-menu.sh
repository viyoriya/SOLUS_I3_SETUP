#!/bin/bash

# small power menu using rofi, dwm, systemd a
# tostiheld, 2016
# Updated : viyoriya 2019

SESSON_ID=$(loginctl session-status | awk 'NR==1{print $1}')
Lock_command="slock"
Exit_command="loginctl terminate-session $SESSON_ID"
Reboot_command="systemctl reboot"
Shutdown_command="systemctl poweroff"

rofi_command="rofi -width 11 -height 15 -lines 4"
options=$' Lock\n Exit\n Reboot\n Shutdown' 
eval \$"$(echo "$options" | $rofi_command -dmenu -p '' | awk '{print $2}')_command"
exit 0