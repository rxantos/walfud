

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Tue Jan 01 16:55:57 2013
 */
/* Compiler settings for DropOnTarget.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0595 
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

#ifndef __DropOnTarget_i_h__
#define __DropOnTarget_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDropOnTargetImpl_FWD_DEFINED__
#define __IDropOnTargetImpl_FWD_DEFINED__
typedef interface IDropOnTargetImpl IDropOnTargetImpl;

#endif 	/* __IDropOnTargetImpl_FWD_DEFINED__ */


#ifndef __DropOnTargetImpl_FWD_DEFINED__
#define __DropOnTargetImpl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DropOnTargetImpl DropOnTargetImpl;
#else
typedef struct DropOnTargetImpl DropOnTargetImpl;
#endif /* __cplusplus */

#endif 	/* __DropOnTargetImpl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDropOnTargetImpl_INTERFACE_DEFINED__
#define __IDropOnTargetImpl_INTERFACE_DEFINED__

/* interface IDropOnTargetImpl */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDropOnTargetImpl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2AE1CD01-18EB-447E-B45A-FE2201CD222F")
    IDropOnTargetImpl : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IDropOnTargetImplVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDropOnTargetImpl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDropOnTargetImpl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDropOnTargetImpl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDropOnTargetImpl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDropOnTargetImpl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDropOnTargetImpl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDropOnTargetImpl * This,
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
    } IDropOnTargetImplVtbl;

    interface IDropOnTargetImpl
    {
        CONST_VTBL struct IDropOnTargetImplVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDropOnTargetImpl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDropOnTargetImpl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDropOnTargetImpl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDropOnTargetImpl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDropOnTargetImpl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDropOnTargetImpl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDropOnTargetImpl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDropOnTargetImpl_INTERFACE_DEFINED__ */



#ifndef __DropOnTargetLib_LIBRARY_DEFINED__
#define __DropOnTargetLib_LIBRARY_DEFINED__

/* library DropOnTargetLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_DropOnTargetLib;

EXTERN_C const CLSID CLSID_DropOnTargetImpl;

#ifdef __cplusplus

class DECLSPEC_UUID("8B0A9875-C9E1-4C59-8C9A-0DF0D4754EAD")
DropOnTargetImpl;
#endif
#endif /* __DropOnTargetLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


