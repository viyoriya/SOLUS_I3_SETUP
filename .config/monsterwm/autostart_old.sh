#! /bin/bash

xset +fp ~/.fonts &
xset fp rehash &
wmname LG3D &
xsetroot -cursor_name left_ptr &
compton -e 0.92 -o 0.92 -b &
feh --bg-scale ~/Pictures/wallpapers/r_Dark0de_1.png &
dunst -conf ~/.config/dunst/dunstrc &
notify-send -u low "Solus monsterwm" "All right" -i ~/.config/monsterwm/Solus.png &

ff="/tmp/$RANDOM.monsterwm.fifo"
[[ -p $ff ]] || mkfifo -m 600 "$ff"

test(){
	echo -e " \uf0ac Monsterwm"
}
cpu(){
  read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
  sleep 0.5
  read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
  cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
  echo -e "$cpu%"
}
function statusbar {
    ACTIVE_DISPLAY_VJ=$(xdotool getwindowfocus getwindowname)
    VOLUME="$(amixer get Master | tail -1 | sed 's/.*\[\([0-9]*%\)\].*/\1/')"
    MEMORY=$(free -m | awk '/Mem/ {printf "%d/%d MB\n", $3, $2 }')
    UPTIME="$(uptime | sed 's/.*up \([^,]*\),.*/\1/')"
    DATE_TIME=$(date +" %d/%m  %H:%M")
    echo -e "%{l}$(test)" "%{c}$ACTIVE_DISPLAY_VJ" "%{r}  $VOLUME |  $MEMORY |  $(cpu) |  $UPTIME | $DATE_TIME"
}

while true; do
    echo -e "$(statusbar)"
    sleep 30s
done < "$ff" | lemonbar -p -u 3 -F '#4666FF' -B '#1F222D' -f "monospace:size=10" -f "Font Awesome 5 Brands-Regular:size=10" -f "Font Awesome 5 Free-Solid:size=10" -f "Font Awesome 5 Free-Regular:size=10" &

monsterwm > "$ff"

rm $ff