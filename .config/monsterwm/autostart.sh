#!/usr/bin/env sh

#xset +fp ~/.fonts/ &
#xset fp rehash &
#for dir in /font/dir1/ /font/dir2/; do xset +fp $dir; done && xset fp rehash
#set wmname LG3D &
xsetroot -cursor_name left_ptr &
compton -e 0.92 -o 0.92 -b &
feh --bg-scale ~/Pictures/wallpapers/r_Dark0de_1.png &
dunst -conf ~/.config/dunst/dunstrc &
notify-send -u low "Solus monsterwm" "All right" -i ~/.config/monsterwm/Solus.png &

NB=F#FF5e81ac
WH=F#FF929496
UWH=U#FFFFFFFF
NEON=F#FF4666FF

monsterFocus(){
    title=$(xdotool getwindowfocus getwindowname)
    [[ ! -z "$title" ]] && echo -e '\uf101' $title || echo "" 
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
function status {
    VOLUME="$(amixer get Master | tail -1 | sed 's/.*\[\([0-9]*%\)\].*/\1/')"
    MEMORY=$(free -m | awk '/Mem/ {printf "%d/%d MB\n", $3, $2 }')
    UPTIME="$(uptime | sed 's/.*up \([^,]*\),.*/\1/')"
    DATE_TIME=$(date +"%{$NB}%{F-}%{$WH} %d/%m %{F-}%{$NB}%{F-}%{$NEON} %H:%M%{F-}")
    echo -e  " %{$NB}\uf028%{F-} %{$WH}$VOLUME%{F-} | %{$NB}\uf538%{F-} %{$WH}$MEMORY%{F-} | %{$NB}\uf2db%{F-} %{$WH}$(cpu)%{F-} | %{$NB}\uf254%{F-} %{$WH}$UPTIME%{F-} | $DATE_TIME  "
}

ff="/tmp/$RANDOM.monsterwm.fifo"
[[ -p $ff ]] || mkfifo -m 600 "$ff"

ds=("1" "2" "3" "4" "5" "6" "7" "8" "9" "0")
ms=("[T]" "[M]" "[B]" "[G]" "[F]" "[D]" "[I]")

while read -t 30 -r wmout || true; do
    if [[ $wmout =~ ^(([[:digit:]]+:)+[[:digit:]]+ ?)+$ ]]; then
        read -ra desktops <<< "$wmout" && unset r
        for desktop in "${desktops[@]}"; do
            IFS=':' read -r d w m c u <<< "$desktop"
            ((c)) && fg="%{$NEON}%{$UWH}" i="${ms[$m]}" \
            || fg="%{$WH}%{U-}"
            ((u)) && w+='%{$WH}%{U-}'
            # r+=" $fg${ds[$d]} [${w/#0/-}] "
            r+=" $fg${ds[$d]} "
        done
        r="${r%::*}"
    fi
    printf "%s%s\n" "%{l} $r%{F#FF62FF00}$i %{F#FF929496}$(monsterFocus)" "%{r}$(status)"
done < "$ff" | lemonbar -p -d -g x18xx -u 3 -n "monsterwm" -B "#FF1F222D" -f "monospace:size=9" -f "Font Awesome 5 Brands Regular:style=Regular:size=9" -f "Font Awesome 5 Free Solid:style=Solid:size=9" &

monsterwm > "$ff"

rm $ff