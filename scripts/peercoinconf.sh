#!/bin/bash -ev

mkdir -p ~/.steepcoin
echo "rpcuser=username" >>~/.steepcoin/steepcoin.conf
echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >>~/.steepcoin/steepcoin.conf

