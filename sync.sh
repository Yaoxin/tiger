#!/usr/bin/env bash

CUR_DIR=$(pwd)
BASENAME=${CUR_DIR##*/}
REMOTE_DIR="/home/cloudy"

echo ${CUR_DIR}
rsync -av -e ssh --exclude-from='.gitignore' ${CUR_DIR} root@192.168.120.30:${REMOTE_DIR}/

if [ $? != 0 ]; then
    echo "sync ${CUR_DIR} failed."
else
    echo "sync ${CUR_DIR} successful."
fi

