#!/bin/sh
export LD_LIBRARY_PATH=.;
export LD_PRELOAD="libft_malloc.so";
#export DYLD_FORCE_FLAT_NAMESPACE=1;
$@;