#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

STEEPCOIND=${STEEPCOIND:-$SRCDIR/steepcoind}
STEEPCOINCLI=${STEEPCOINCLI:-$SRCDIR/steepcoin-cli}
STEEPCOINTX=${STEEPCOINTX:-$SRCDIR/steepcoin-tx}
STEEPCOINQT=${STEEPCOINQT:-$SRCDIR/qt/steepcoin-qt}

[ ! -x $STEEPCOIND ] && echo "$STEEPCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
STEEPVER=($($STEEPCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for steepcoind if --version-string is not set,
# but has different outcomes for steepcoin-qt and steepcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$STEEPCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $STEEPCOIND $STEEPCOINCLI $STEEPCOINTX $STEEPCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${STEEPVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${STEEPVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
