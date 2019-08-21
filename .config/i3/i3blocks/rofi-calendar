#! /bin/sh

DATEFTM="${DATEFTM:-+<span color='#9fb4cd'> %d/%m </span><span color='#0073ff' weight='bold'>%H:%M</span>}"
SHORTFMT="${SHORTFMT:-+%d.%m.%Y}"
LABEL="${LABEL:-}"
blockdate=$(date "$DATEFTM")
shortblockdate=$(date "$SHORTFMT")

year=$(date '+%Y')
month=$(date '+%m')
case "$BLOCK_BUTTON" in
    1|2)
        date=$(date '+%A, %d. %B');;
    3)
        (( month == 12 )) && month=1 && year=$((year + 1)) || month=$((month + 1))
        date=$(cal $month $year | sed -n '1s/^  *//;1s/  *$//p')
esac
case "$BLOCK_BUTTON" in
    1|2|3)
export TERM=xterm
cal --color=always $month $year \
    | sed 's/\x1b\[[7;]*m/\<b\>\<u\>/g' \
    | sed 's/\x1b\[[27;]*m/\<\/u\>\<\/b\>/g' \
    | tail -n +2 \
    | rofi \
        -dmenu \
        -markup-rows \
        -no-fullscreen \
        -font 'Monospace Regular 9' \
        -hide-scrollbar \
        -lines 7 \
        -yoffset -285 -xoffset 540 \
        -theme '~/.config/rofi/themes/viyoriya.rasi' \
        -eh 1 \
        -width -25 \
        -no-custom \
        -p "" > /dev/null 
    esac
echo "$LABEL$blockdate"
echo "$LABEL$shortblockdate"
