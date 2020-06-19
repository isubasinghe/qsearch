#!/usr/bin/env bash

# clean up
rm *.txt
rm -rf repo

git clone git@github.com:Alir3z4/stop-words.git repo
cd repo || exit

cat *.txt >> words.txt
find . ! -name 'words.txt' -type f -exec rm -f {} +

mv words.txt ..
cd ..

rm -rf repo