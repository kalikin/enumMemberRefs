# Profiler library

This is a modified profiler example from [.NET Samples repository](https://github.com/dotnet/samples/tree/main/core/profiling).

For each loaded module profiler enumerates TypeRefs and counts their members using [IMetaDataImport::EnumMemberRefs](https://docs.microsoft.com/en-us/dotnet/framework/unmanaged-api/metadata/imetadataimport-enummemberrefs-method).

## Building (Linux)

Please refer to the original sample. Assuming the [.NET Runtime repository](https://github.com/dotnet/runtime) 
is in `~/git/runtime` and according to the [instructions](https://github.com/dotnet/runtime/blob/main/docs/workflow/building/coreclr/linux-instructions.md) 
is built similar to this: `docker run --rm -v ~/git/runtime:/runtime -w /runtime mcr.microsoft.com/dotnet-buildtools/prereqs:ubuntu-16.04-20200508132555-78cbb55 ./build.sh -subset clr -clang9`,

run `bash build.sh` to compile the profiler library.

The result library should appear in `bin/libCorProfiler.so`. Its GUID is `{0F23A0CA-08B7-4FCA-ACCC-B4A87A90C060}`.
