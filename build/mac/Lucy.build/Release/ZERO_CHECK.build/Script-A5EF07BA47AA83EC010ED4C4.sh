#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/verodev/Documents/Iris Technologies/Project Lucy/build/mac"
  make -f /Users/verodev/Documents/Iris\ Technologies/Project\ Lucy/build/mac/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/verodev/Documents/Iris Technologies/Project Lucy/build/mac"
  make -f /Users/verodev/Documents/Iris\ Technologies/Project\ Lucy/build/mac/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/verodev/Documents/Iris Technologies/Project Lucy/build/mac"
  make -f /Users/verodev/Documents/Iris\ Technologies/Project\ Lucy/build/mac/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/verodev/Documents/Iris Technologies/Project Lucy/build/mac"
  make -f /Users/verodev/Documents/Iris\ Technologies/Project\ Lucy/build/mac/CMakeScripts/ReRunCMake.make
fi

