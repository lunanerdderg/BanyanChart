#!/bin/bash

cd $HOME/Documents/Programming/Apps/BanyanChart
echo
echo "===================================================="
echo "-= Git fetch =-"
echo
git fetch --all
echo
echo "===================================================="
echo "-= Git status =-"
echo
git status
echo
echo "===================================================="
echo "-= Pulling from Github branch '${1:-"main"}' =-"
echo
git reset --hard origin/"${1:-"main"}"
echo
echo "===================================================="
echo "-= Git status =-"
echo
git status
echo
echo "===================================================="
echo "-= Success! =-"
echo
cd ~