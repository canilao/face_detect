#! /bin/bash

astyle --style=allman --unpad-paren --indent=spaces=4 --align-pointer=middle Includes/*.h Includes/*.cpp main.cpp
