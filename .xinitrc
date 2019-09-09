#!/bin/sh
#
# ~/.xinitrc

# $ xrdb ~/.Xresources
# Xcursor.theme:Adwaita
# Xcursor.size: 16
# test


if [ -d /etc/X11/xinit/xinitrc.d ]; then
  for f in /etc/X11/xinit/xinitrc.d/*; do
    [ -x "$f" ] && . "$f"
  done
  unset f
fi

session=${1:-dwm}

#if [[ $session == catwm ]]; then
#	. ~/.config/catwm/autostart.sh
#fi

case $session in
        i3            ) exec i3;;
        dwm           ) exec dwm;;
        mwm           ) exec ~/.config/monsterwm/autostart.sh ;;
	    catwm         ) exec ~/.config/catwm/autostart.sh ;;
		fwm           ) exec ~/.config/fwm/autostart.sh ;;
        *             ) exec $1;;
esac
