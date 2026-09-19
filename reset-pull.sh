#!/bin/bash

cd $HOME/Documents/Programming/Apps/BanyanChart
echo
echo "-= Git status =-"
git fetch --all
git status
echo
echo "-= Pulling from Github =-"
git reset --hard origin/"${1:-"main"}"
echo
echo "-= Git status =-"
git status
echo
echo "-= Success! =-"
cd ~