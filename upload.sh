#!/bin/bash

cd $HOME/Documents/Programming/Apps/BanyanChart
echo
echo "-= Git status =-"
git status
echo
echo "-= Pushing to Github - '${1:-"Update"}' =-"
git add -A && git commit -a -m "${1:-"Update"}" && git push
git submodule update --remote
echo
echo "-= Git status =-"
git status
echo
echo "-= Success! =-"
cd ~
