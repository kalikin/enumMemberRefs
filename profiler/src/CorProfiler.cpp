// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include "CorProfiler.h"
#include "corhlpr.h"
#include "CComPtr.h"
#include "profiler_pal.h"
#include <string>
#include <sstream>
#include <assert.h>
#include <cstdlib>
#include <ctime>

using std::shared_ptr;
using std::vector;
using std::mutex;
using std::lock_guard;
using std::map;
using std::thread;

CorProfiler::CorProfiler() :
    _pCorProfilerInfo12(),
    _refCount(0),
    _totalEnumeratedTypeRefs(0),
    _totalEnumeratedMemberRefs(0)
{

}

CorProfiler::~CorProfiler()
{
    if (this->_pCorProfilerInfo12 != nullptr)
    {
        this->_pCorProfilerInfo12->Release();
        this->_pCorProfilerInfo12 = nullptr;
    }
}

HRESULT STDMETHODCALLTYPE CorProfiler::Initialize(IUnknown *pICorProfilerInfoUnk)
{
    HRESULT hr = S_OK;
    if (FAILED(hr = pICorProfilerInfoUnk->QueryInterface(__uuidof(ICorProfilerInfo12), (void **)&_pCorProfilerInfo12)))
    {
        printf("FAIL: failed to QI for ICorProfilerInfo12.\n");
        return hr;
    }

    if (FAILED(hr = _pCorProfilerInfo12->SetEventMask2(COR_PRF_MONITOR_JIT_COMPILATION
                                                        | COR_PRF_MONITOR_MODULE_LOADS
                                                        | COR_PRF_DISABLE_ALL_NGEN_IMAGES,
                                                        0
                                                       )))
    {
        printf("FAIL: ICorProfilerInfo::SetEventMask2() failed hr=0x%x\n", hr);
        return hr;
    }

    return S_OK;
}


HRESULT STDMETHODCALLTYPE CorProfiler::Shutdown()
{
    printf("TypeRefs:   %d\n", _totalEnumeratedTypeRefs);
    printf("MemberRefs: %d\n", _totalEnumeratedMemberRefs);
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CorProfiler::ModuleLoadStarted(ModuleID moduleId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CorProfiler::ModuleLoadFinished(ModuleID moduleId, HRESULT hrStatus)
{
    if (SUCCEEDED(hrStatus))
    {
        CComPtr<IMetaDataImport2> metaDataImport;
        if (SUCCEEDED(_pCorProfilerInfo12->GetModuleMetaData(moduleId, ofRead, IID_IMetaDataImport2, (IUnknown**)&metaDataImport)))
        {
            enumTypeRefs(metaDataImport);
        }
    }
    return S_OK;
}

void CorProfiler::enumTypeRefs(IMetaDataImport2* metaDataImport)
{
    HCORENUM enumerator = NULL;
    mdTypeRef typeRef;
    ULONG read = 0;
    while (SUCCEEDED(metaDataImport->EnumTypeRefs(&enumerator, &typeRef, 1, &read)))
    {
        if (read == 0)
        {
            break;
        }
        _totalEnumeratedTypeRefs++;
        enumMemberRefs(metaDataImport, typeRef);
    }
    metaDataImport->CloseEnum(enumerator);
}

void CorProfiler::enumMemberRefs(IMetaDataImport2* metaDataImport, mdTypeRef typeRef)
{
    HCORENUM enumerator = NULL;
    mdMemberRef memberRef;
    ULONG read = 0;
    while (SUCCEEDED(metaDataImport->EnumMemberRefs(&enumerator, typeRef, &memberRef, 1, &read)))
    {
        if (read == 0)
        {
            break;
        }
        _totalEnumeratedMemberRefs++;
    }
    metaDataImport->CloseEnum(enumerator);
}
