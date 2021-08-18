
Debian
====================
This directory contains files used to package steepcoind/steepcoin-qt
for Debian-based Linux systems. If you compile steepcoind/steepcoin-qt yourself, there are some useful files here.

## steepcoin: URI support ##


steepcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install steepcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your steepcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/steepcoin128.png` to `/usr/share/pixmaps`

steepcoin-qt.protocol (KDE)

