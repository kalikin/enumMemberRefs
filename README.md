# EnumMemberRefs demo

This example compares the behaviour of [IMetaDataImport::EnumMemberRefs](https://docs.microsoft.com/en-us/dotnet/framework/unmanaged-api/metadata/imetadataimport-enummemberrefs-method)
in .NET 5 and .NET 6 Preview.

1. Compile [profiler library](profiler)
2. Compile [demo](demo)
3. Run the demo with the profiler library: `bash profile.sh`

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

Here's the code snippet from [CorProfiler.cpp](https://github.com/kalikin/enumMemberRefs/blob/3b038ef0fe787771e91d4c9c239d342ceff9a8d5/profiler/src/CorProfiler.cpp#L111-L118) which counts *MemberRefs*:

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
