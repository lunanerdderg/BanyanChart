#!/bin/bash

cd $HOME/Documents/Programming/Apps/BanyanChart
echo
echo "-= Git fetch =-"
git fetch --all
echo
echo "-= Git status =-"
git status
echo
echo "-= Pulling from Github branch '${1:-"main"}' =-"
git reset --hard origin/"${1:-"main"}"
echo
echo "-= Git status =-"
git status
echo
echo "-= Success! =-"
cd ~