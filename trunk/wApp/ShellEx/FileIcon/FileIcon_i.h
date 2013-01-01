

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Tue Jan 01 17:08:56 2013
 */
/* Compiler settings for FileIcon.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __FileIcon_i_h__
#define __FileIcon_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFileIconImpl_FWD_DEFINED__
#define __IFileIconImpl_FWD_DEFINED__
typedef interface IFileIconImpl IFileIconImpl;

#endif 	/* __IFileIconImpl_FWD_DEFINED__ */


#ifndef __FileIconImpl_FWD_DEFINED__
#define __FileIconImpl_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileIconImpl FileIconImpl;
#else
typedef struct FileIconImpl FileIconImpl;
#endif /* __cplusplus */

#endif 	/* __FileIconImpl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IFileIconImpl_INTERFACE_DEFINED__
#define __IFileIconImpl_INTERFACE_DEFINED__

/* interface IFileIconImpl */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IFileIconImpl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A174FCD4-BB0D-49A0-A7A7-FAF0196FA27D")
    IFileIconImpl : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IFileIconImplVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileIconImpl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileIconImpl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileIconImpl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFileIconImpl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFileIconImpl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFileIconImpl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFileIconImpl * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IFileIconImplVtbl;

    interface IFileIconImpl
    {
        CONST_VTBL struct IFileIconImplVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileIconImpl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileIconImpl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileIconImpl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileIconImpl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFileIconImpl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFileIconImpl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFileIconImpl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFileIconImpl_INTERFACE_DEFINED__ */



#ifndef __FileIconLib_LIBRARY_DEFINED__
#define __FileIconLib_LIBRARY_DEFINED__

/* library FileIconLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_FileIconLib;

EXTERN_C const CLSID CLSID_FileIconImpl;

#ifdef __cplusplus

class DECLSPEC_UUID("1C16A911-78BF-4CA3-8660-DB368F98C612")
FileIconImpl;
#endif
#endif /* __FileIconLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


