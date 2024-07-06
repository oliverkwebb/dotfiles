#!/bin/sh
userresources="$HOME/.Xresources"
usermodmap="$HOME/.config/Xmodmap"
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

[ -f $sysresources ] && xrdb -merge $sysresources &
[ -f "$userresources" ] && xrdb -merge "$userresources" &
[ -f $sysmodmap ] && xmodmap $sysmodmap &
[ -f "$usermodmap" ] && xmodmap "$usermodmap" &
dex --autostart --environment i3 &
xss-lock --transfer-sleep-lock -- lock --nofork &
nm-applet &
xwallpaper --stretch /home/oliver/Pictures/Wallpapers/wallpaper.png &
picom &
exec i3
