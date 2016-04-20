#!/bin/bash

# Create diretories structure for binaries
mkdir -p core/hal/obj/debug
mkdir -p core/kernel/bin
mkdir -p core/kernel/obj
mkdir -p core/lib/obj

# Dependencies files
touch core/hal/.depend
touch core/kernel/.depend
touch core/lib/.depend