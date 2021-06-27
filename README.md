# EnumMemberRefs demo

This example compares the behaviour of [IMetaDataImport::EnumMemberRefs](https://docs.microsoft.com/en-us/dotnet/framework/unmanaged-api/metadata/imetadataimport-enummemberrefs-method)
in .NET 5 and .NET 6 Preview.

1. Compile [profiler library](profiler/README.md)
2. Compile [demo](demo/README.md)
3. Run the demo with the profiler library: `bash profiler.sh`

Example output:

<pre>
6.0.100-preview.5.21302.13

Running demo in .NET 5.0
Hello World
TypeRefs:   451
MemberRefs: 657

Running demo in .NET 6.0
Hello World
TypeRefs:   556
<strong>MemberRefs: 0</strong>
</pre>

Here's the code snippet from [CorProfiler.cpp](profiler/src/CorProfiler.cpp) which counts *MemberRefs*:

<pre>
    while (SUCCEEDED(metaDataImport->EnumMemberRefs(&enumerator, typeRef, &memberRef, 1, &read)))
    {
        if (read == 0)
        {
            break;
        }
        <strong>_totalEnumeratedMemberRefs++;</strong>
    }
</pre>
