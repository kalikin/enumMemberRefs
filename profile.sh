#!/bin/bash

# If .NET 6 SDK is in not in PATH, add it here
PATH=$HOME/opt/dotnet/64/:$PATH

dotnet --version
echo

export CORECLR_ENABLE_PROFILING=1
export CORECLR_PROFILER="{0F23A0CA-08B7-4FCA-ACCC-B4A87A90C060}"
export CORECLR_PROFILER_PATH_64="profiler/bin/libCorProfiler.so"

if [ ! -f "$CORECLR_PROFILER_PATH_64" ] ; then
  echo "ERROR: profiler library does not exist - compile it before running the example"
  exit 1
fi

echo "Running demo in .NET 5.0"
dotnet demo/bin/Debug/net5.0/demo.dll
echo

echo "Running demo in .NET 6.0"
dotnet demo/bin/Debug/net6.0/demo.dll
echo
