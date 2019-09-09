#! /bin/bash

wmname LG3D &
compton -e 0.92 -o 0.92 -b &
feh --bg-scale ~/Pictures/wallpapers/u_muhahah_the_sixer_3.jpg &
dunst -conf ~/.config/dunst/dunstrc &
#notify-send -u low "Scrot" "Screenshot done !!!" -i ~/.local/share/icons/Papirus-Dark/32x32/devices/camera.svg
notify-send -u low "Solus Dwm" "All right" -i ~/.dwm/dwm_logo.png

cpu(){
  read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
  sleep 0.5
  read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
  cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
  echo -e "$cpu%"
}
while true; do
	VOLUME="$(amixer get Master | tail -1 | sed 's/.*\[\([0-9]*%\)\].*/\1/')"
	MEMORY=$(free -m | awk '/Mem/ {printf "%d/%d MB\n", $3, $2 }')
	UPTIME="$(uptime | sed 's/.*up \([^,]*\),.*/\1/')"
	DATE_TIME=$(date +" %d/%m  %H:%M")
	xsetroot -name "  $VOLUME |  $MEMORY |  $(cpu) |  $UPTIME | $DATE_TIME "
	sleep 1m
done &

#xsetroot -xcf /usr/share/icons/Adwaita/cursors/left_ptr 32 
#Xcursor.theme:Adwaita
#feh --bg-scale ~/Pictures/wallpapers/wlp.png &
#nm-applet &
#--config ~/.dwm/compton.conf
#dwm_logo.png