

// wWindowsExt.h
// This file contains many undocument functions and structures, which maybe various between different version.

#ifndef W_WINDOWSEXT_H
#define W_WINDOWSEXT_H

#include "wCppExt.h"

namespace w
{

typedef LONG NTSTATUS;   
  
#define STATUS_SUCCESS                  ((NTSTATUS)0x00000000L)   
#define STATUS_UNSUCCESSFUL             ((NTSTATUS)0xC0000001L)   
#define STATUS_NOT_IMPLEMENTED          ((NTSTATUS)0xC0000002L)   
#define STATUS_INVALID_INFO_CLASS       ((NTSTATUS)0xC0000003L)   
#define STATUS_INFO_LENGTH_MISMATCH     ((NTSTATUS)0xC0000004L)   

typedef enum _SYSTEMINFOCLASS
{
 SystemBasicInformation,            // 0x002C
 SystemProcessorInformation,        // 0x000C
 SystemPerformanceInformation,      // 0x0138
 SystemTimeInformation,             // 0x0020
 SystemPathInformation,             // not implemented
 SystemProcessInformation,          // 0x00C8+ per process
 SystemCallInformation,             // 0x0018 + (n * 0x0004)
 SystemConfigurationInformation,    // 0x0018
 SystemProcessorCounters,           // 0x0030 per cpu
 SystemGlobalFlag,                  // 0x0004 (fails if size != 4)
 SystemCallTimeInformation,         // not implemented
 SystemModuleInformation,           // 0x0004 + (n * 0x011C)
 SystemLockInformation,             // 0x0004 + (n * 0x0024)
 SystemStackTraceInformation,       // not implemented
 SystemPagedPoolInformation,        // checked build only
 SystemNonPagedPoolInformation,     // checked build only
 SystemHandleInformation,           // 0x0004  + (n * 0x0010)
 SystemObjectTypeInformation,       // 0x0038+ + (n * 0x0030+)
 SystemPageFileInformation,         // 0x0018+ per page file
 SystemVdmInstemulInformation,      // 0x0088
 SystemVdmBopInformation,           // invalid info class
 SystemCacheInformation,            // 0x0024
 SystemPoolTagInformation,          // 0x0004 + (n * 0x001C)
 SystemInterruptInformation,        // 0x0000, or 0x0018 per cpu
 SystemDpcInformation,              // 0x0014
 SystemFullMemoryInformation,       // checked build only
 SystemLoadDriver,                  // 0x0018, set mode only
 SystemUnloadDriver,                // 0x0004, set mode only
 SystemTimeAdjustmentInformation,   // 0x000C, 0x0008 writeable
 SystemSummaryMemoryInformation,    // checked build only
 SystemNextEventIdInformation,      // checked build only
 SystemEventIdsInformation,         // checked build only
 SystemCrashDumpInformation,        // 0x0004
 SystemExceptionInformation,        // 0x0010
 SystemCrashDumpStateInformation,   // 0x0004
 SystemDebuggerInformation,         // 0x0002
 SystemContextSwitchInformation,    // 0x0030
 SystemRegistryQuotaInformation,    // 0x000C
 SystemAddDriver,                   // 0x0008, set mode only
 SystemPrioritySeparationInformation,// 0x0004, set mode only
 SystemPlugPlayBusInformation,      // not implemented
 SystemDockInformation,             // not implemented
 SystemPowerInfo,					// 0x0060 (XP only!)
 SystemProcessorSpeedInformation,   // 0x000C (XP only!)
 SystemTimeZoneInformation,         // 0x00AC
 SystemLookasideInformation,        // n * 0x0020
 SystemSetTimeSlipEvent,
 SystemCreateSession,				// set mode only
 SystemDeleteSession,				// set mode only
 SystemInvalidInfoClass1,			// invalid info class
 SystemRangeStartInformation,		// 0x0004 (fails if size != 4)
 SystemVerifierInformation,
 SystemAddVerifier,
 SystemSessionProcessesInformation, // checked build only
 MaxSystemInfoClass
}SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_HANDLE_INFORMATION {
    ULONG  ProcessId;
    UCHAR  ObjectTypeNumber;
    UCHAR  Flags;
    USHORT  Handle;
    PVOID  Object;
    ACCESS_MASK  GrantedAccess;
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;
typedef struct _SYSTEM_HANDLE_INFORMATION_EX 
{
  ULONG NumberOfHandles;            //¾ä±úÊýÄ¿
  SYSTEM_HANDLE_INFORMATION Information[1];
} SYSTEM_HANDLE_INFORMATION_EX, *PSYSTEM_HANDLE_INFORMATION_EX;

typedef struct _IO_STATUS_BLOCK
{
    union
    {
        NTSTATUS Status;
        PVOID    Pointer;
    };
 
    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;
 
typedef enum _FILE_INFORMATION_CLASS
{
    FileDirectoryInformation         = 1,
    FileFullDirectoryInformation,   // 2
    FileBothDirectoryInformation,   // 3
    FileBasicInformation,           // 4
    FileStandardInformation,        // 5
    FileInternalInformation,        // 6
    FileEaInformation,              // 7
    FileAccessInformation,          // 8
    FileNameInformation,            // 9
    FileRenameInformation,          // 10
    FileLinkInformation,            // 11
    FileNamesInformation,           // 12
    FileDispositionInformation,     // 13
    FilePositionInformation,        // 14
    FileFullEaInformation,          // 15
    FileModeInformation,            // 16
    FileAlignmentInformation,       // 17
    FileAllInformation,             // 18
    FileAllocationInformation,      // 19
    FileEndOfFileInformation,       // 20
    FileAlternateNameInformation,   // 21
    FileStreamInformation,          // 22
    FilePipeInformation,            // 23
    FilePipeLocalInformation,       // 24
    FilePipeRemoteInformation,      // 25
    FileMailslotQueryInformation,   // 26
    FileMailslotSetInformation,     // 27
    FileCompressionInformation,     // 28
    FileObjectIdInformation,        // 29
    FileCompletionInformation,      // 30
    FileMoveClusterInformation,     // 31
    FileQuotaInformation,           // 32
    FileReparsePointInformation,    // 33
    FileNetworkOpenInformation,     // 34
    FileAttributeTagInformation,    // 35
    FileTrackingInformation,        // 36
    FileIdBothDirectoryInformation, // 37
    FileIdFullDirectoryInformation, // 38
    FileValidDataLengthInformation, // 39
    FileShortNameInformation,       // 40
    FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

typedef struct _FILE_NAME_INFORMATION {
	ULONG FileNameLength;
	WCHAR FileName[1];
} FILE_NAME_INFORMATION, *PFILE_NAME_INFORMATION;

typedef enum _OBJECT_INFORMATION_CLASS {
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectAllInformation,
	ObjectDataInformation
} OBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;

typedef struct _KOBJECT_NAME_INFORMATION {
	ULONG FileNameLength;
	ULONG Unknown;
	WCHAR FileName[1];
} KOBJECT_NAME_INFORMATION, *PKOBJECT_NAME_INFORMATION;

NTSTATUS NTAPI FuncZwQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength OPTIONAL);
NTSTATUS NTAPI FuncZwQueryInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass);
NTSTATUS NTAPI FuncZwQueryObject(HANDLE ObjectHandle, ULONG ObjectInformationClass, PVOID ObjectInformation, ULONG ObjectInformationLength, PULONG ReturnLength);

extern decltype(FuncZwQuerySystemInformation) *ZwQuerySystemInformation;
extern decltype(FuncZwQueryInformationFile) *ZwQueryInformationFile;
extern decltype(FuncZwQueryObject) *ZwQueryObject;


#define ThreadBasicInformation	THREADINFOCLASS(0)

typedef enum _SC_SERVICE_TAG_QUERY_TYPE 
{
	ServiceNameFromTagInformation = 1,
	ServiceNamesReferencingModuleInformation,
	ServiceNameTagMappingInformation
} SC_SERVICE_TAG_QUERY_TYPE, *PSC_SERVICE_TAG_QUERY_TYPE;

typedef struct _SC_SERVICE_TAG_QUERY
{
    ULONG ProcessId;
    ULONG ServiceTag;
    ULONG Unknown;
    PVOID Buffer;
} SC_SERVICE_TAG_QUERY, *PSC_SERVICE_TAG_QUERY;

ULONG NTAPI FuncI_QueryTagInformation(
	__in PVOID Unknown,
	__in SC_SERVICE_TAG_QUERY_TYPE QueryType,
	__inout PSC_SERVICE_TAG_QUERY Query
);

NTSTATUS WINAPI FuncNtQueryInformationThread(
  _In_       HANDLE ThreadHandle,
  _In_       THREADINFOCLASS ThreadInformationClass,
  _Inout_    PVOID ThreadInformation,
  _In_       ULONG ThreadInformationLength,
  _Out_opt_  PULONG ReturnLength
);

NTSYSAPI NTSTATUS NTAPI FuncNtReadVirtualMemory(
	IN HANDLE               ProcessHandle,
	IN PVOID                BaseAddress,
	OUT PVOID               Buffer,
	IN ULONG                NumberOfBytesToRead,
	OUT PULONG              NumberOfBytesReaded OPTIONAL
);
NTSYSAPI NTSTATUS NTAPI FuncNtWow64ReadVirtualMemory64(HANDLE ProcessHandle, 
													   PVOID64 BaseAddress, 
													   PVOID Buffer, 
													   UINT64 NumberOfBytesToRead, 
													   PUINT64 NumberOfBytesReaded);

extern decltype(FuncNtQueryInformationThread) *NtQueryInformationThread;
extern decltype(FuncNtReadVirtualMemory) *NtReadVirtualMemory;
extern decltype(FuncNtWow64ReadVirtualMemory64) *NtWow64ReadVirtualMemory64;
extern decltype(FuncI_QueryTagInformation) *I_QueryTagInformation;

typedef struct 
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID;

typedef LONG KPRIORITY;

typedef struct _THREAD_BASIC_INFORMATION 
{
	NTSTATUS                ExitStatus;
	PVOID                   TebBaseAddress;
	CLIENT_ID               ClientId;
	KAFFINITY               AffinityMask;
	KPRIORITY               Priority;
	KPRIORITY               BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

typedef struct
{
    PVOID64 Filler[4];
    PVOID64 ProcessParameters;
} __PEB64;

typedef struct _UNICODE_STRING64 {
    SHORT Length;
    SHORT MaximumLength;
    DWORD Fill;
    PVOID64  Buffer;
} UNICODE_STRING64;

typedef struct 
{
    //DWORD MaximumLength;
    //DWORD Length;
    //DWORD Flags;
    //DWORD DebugFlags;
    //PVOID64 ConsoleHandle;
    //DWORD ConsoleFlags;
    //PVOID64 StandardInput;
    //PVOID64 StandardOutput;
    //PVOID64 StandardError;
    ////////////////////////////
    //UNICODE_STRING64 DosPath;//CurrentDirectory
    //HANDLE Handle;
    ////////////////////////////
    //UNICODE_STRING64 DllPath;
    //UNICODE_STRING64 ImagePathName;
    //UNICODE_STRING64 CmdLine;
    ////¡­¡­
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    PVOID64 ConsoleHandle;
    ULONG ConsoleFlags;
    PVOID64 StandardInput;
    PVOID64 StandardOutput;
    PVOID64 StandardError;
    UNICODE_STRING64 CurrentDirectory;
	PVOID64 Handle;
    UNICODE_STRING64 DllPath;
    UNICODE_STRING64 ImagePathName;
    UNICODE_STRING64 CommandLine;
    PVOID64 Environment;		// PWSTR.
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING64 WindowTitle;
    UNICODE_STRING64 DesktopInfo;
    UNICODE_STRING64 ShellInfo;
    UNICODE_STRING64 RuntimeData;
//    RTL_DRIVE_LETTER_CURDIR CurrentDirectories[RTL_MAX_DRIVE_LETTERS];
//#if (NTDDI_VERSION >= NTDDI_LONGHORN)
//    SIZE_T EnvironmentSize;
//#endif
//#if (NTDDI_VERSION >= NTDDI_WIN7)
//    SIZE_T EnvironmentVersion;
//#endif
}_RTL_USER_PROCESS_PARAMETERS64;

// end_ntddk end_ntifs 
typedef struct _PROCESS_BASIC_INFORMATION64 
{ 
    PVOID64 Reserved1;
    PVOID64 PebBaseAddress;
    PVOID64 Reserved2[2];
    PVOID64 UniqueProcessId;
    PVOID64 Reserved3;
} PROCESS_BASIC_INFORMATION64,*PPROCESS_BASIC_INFORMATION64; 

NTSTATUS
NTAPI
FuncNtQueryInformationProcess(IN HANDLE ProcessHandle,
							  IN PROCESSINFOCLASS ProcessInformationClass,
							  OUT PVOID ProcessInformation,
							  IN ULONG ProcessInformationLength,
							  OUT PULONG ReturnLength OPTIONAL);
NTSTATUS
NTAPI
FuncNtWow64QueryInformationProcess64(IN HANDLE ProcessHandle,
									 IN PROCESSINFOCLASS ProcessInformationClass,
									 OUT PVOID ProcessInformation,
									 IN ULONG ProcessInformationLength,
									 OUT PUINT64 ReturnLength OPTIONAL);

extern decltype(FuncNtQueryInformationProcess) *NtQueryInformationProcess;
extern decltype(FuncNtWow64QueryInformationProcess64) *NtWow64QueryInformationProcess64;

}

#endif // W_WINDOWSEXT_H