#!/bin/sh

# If .NET 6 SDK is in not in PATH, add it here
PATH=$HOME/opt/dotnet/64/:$PATH

dotnet build
