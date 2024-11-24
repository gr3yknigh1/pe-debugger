
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <windows.h>

// #define STILL_ACTIVE                        STATUS_PENDING
// #define EXCEPTION_ACCESS_VIOLATION          STATUS_ACCESS_VIOLATION
// #define EXCEPTION_DATATYPE_MISALIGNMENT     STATUS_DATATYPE_MISALIGNMENT
// #define EXCEPTION_BREAKPOINT                STATUS_BREAKPOINT
// #define EXCEPTION_SINGLE_STEP               STATUS_SINGLE_STEP
// #define EXCEPTION_ARRAY_BOUNDS_EXCEEDED     STATUS_ARRAY_BOUNDS_EXCEEDED
// #define EXCEPTION_FLT_DENORMAL_OPERAND      STATUS_FLOAT_DENORMAL_OPERAND
// #define EXCEPTION_FLT_DIVIDE_BY_ZERO        STATUS_FLOAT_DIVIDE_BY_ZERO
// #define EXCEPTION_FLT_INEXACT_RESULT        STATUS_FLOAT_INEXACT_RESULT
// #define EXCEPTION_FLT_INVALID_OPERATION     STATUS_FLOAT_INVALID_OPERATION
// #define EXCEPTION_FLT_OVERFLOW              STATUS_FLOAT_OVERFLOW
// #define EXCEPTION_FLT_STACK_CHECK           STATUS_FLOAT_STACK_CHECK
// #define EXCEPTION_FLT_UNDERFLOW             STATUS_FLOAT_UNDERFLOW
// #define EXCEPTION_INT_DIVIDE_BY_ZERO        STATUS_INTEGER_DIVIDE_BY_ZERO
// #define EXCEPTION_INT_OVERFLOW              STATUS_INTEGER_OVERFLOW
// #define EXCEPTION_PRIV_INSTRUCTION          STATUS_PRIVILEGED_INSTRUCTION
// #define EXCEPTION_IN_PAGE_ERROR             STATUS_IN_PAGE_ERROR
// #define EXCEPTION_ILLEGAL_INSTRUCTION       STATUS_ILLEGAL_INSTRUCTION
// #define EXCEPTION_NONCONTINUABLE_EXCEPTION  STATUS_NONCONTINUABLE_EXCEPTION
// #define EXCEPTION_STACK_OVERFLOW            STATUS_STACK_OVERFLOW
// #define EXCEPTION_INVALID_DISPOSITION       STATUS_INVALID_DISPOSITION
// #define EXCEPTION_GUARD_PAGE                STATUS_GUARD_PAGE_VIOLATION
// #define EXCEPTION_INVALID_HANDLE            STATUS_INVALID_HANDLE
// #define EXCEPTION_POSSIBLE_DEADLOCK         STATUS_POSSIBLE_DEADLOCK
// #define CONTROL_C_EXIT                      STATUS_CONTROL_C_EXIT

const char *
ExceptionCodeToString(DWORD ExceptionCode)
{
    const char *Result = "(null)";

    switch (ExceptionCode) {
    case STILL_ACTIVE:
        Result = "STILL_ACTIVE";
        break;
    case EXCEPTION_ACCESS_VIOLATION:
        Result = "EXCEPTION_ACCESS_VIOLATION";
        break;
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        Result = "EXCEPTION_DATATYPE_MISALIGNMENT";
        break;
    case EXCEPTION_BREAKPOINT:
        Result = "EXCEPTION_BREAKPOINT";
        break;
    case EXCEPTION_SINGLE_STEP:
        Result = "EXCEPTION_SINGLE_STEP";
        break;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        Result = "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
        break;
    case EXCEPTION_FLT_DENORMAL_OPERAND:
        Result = "EXCEPTION_FLT_DENORMAL_OPERAND";
        break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        Result = "EXCEPTION_FLT_DIVIDE_BY_ZERO";
        break;
    case EXCEPTION_FLT_INEXACT_RESULT:
        Result = "EXCEPTION_FLT_INEXACT_RESULT";
        break;
    case EXCEPTION_FLT_INVALID_OPERATION:
        Result = "EXCEPTION_FLT_INVALID_OPERATION";
        break;
    case EXCEPTION_FLT_OVERFLOW:
        Result = "EXCEPTION_FLT_OVERFLOW";
        break;
    case EXCEPTION_FLT_STACK_CHECK:
        Result = "EXCEPTION_FLT_STACK_CHECK";
        break;
    case EXCEPTION_FLT_UNDERFLOW:
        Result = "EXCEPTION_FLT_UNDERFLOW";
        break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        Result = "EXCEPTION_INT_DIVIDE_BY_ZERO";
        break;
    case EXCEPTION_INT_OVERFLOW:
        Result = "EXCEPTION_INT_OVERFLOW";
        break;
    case EXCEPTION_PRIV_INSTRUCTION:
        Result = "EXCEPTION_PRIV_INSTRUCTION";
        break;
    case EXCEPTION_IN_PAGE_ERROR:
        Result = "EXCEPTION_IN_PAGE_ERROR";
        break;
    case EXCEPTION_ILLEGAL_INSTRUCTION:
        Result = "EXCEPTION_ILLEGAL_INSTRUCTION";
        break;
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:
        Result = "EXCEPTION_NONCONTINUABLE_EXCEPTION";
        break;
    case EXCEPTION_STACK_OVERFLOW:
        Result = "EXCEPTION_STACK_OVERFLOW";
        break;
    case EXCEPTION_INVALID_DISPOSITION:
        Result = "EXCEPTION_INVALID_DISPOSITION";
        break;
    case EXCEPTION_GUARD_PAGE:
        Result = "EXCEPTION_GUARD_PAGE";
        break;
    case EXCEPTION_INVALID_HANDLE:
        Result = "EXCEPTION_INVALID_HANDLE";
        break;
    // case EXCEPTION_POSSIBLE_DEADLOCK:
    //     Result = "EXCEPTION_POSSIBLE_DEADLOCK";
    //     break;
    case CONTROL_C_EXIT:
        Result = "CONTROL_C_EXIT";
        break;
    default:
        Result = "UNKNOWN";
        break;
    }

    return Result;
}

int
main(void)
{
    puts("Hello world!");

    STARTUPINFOW StartupInfo = {0};
    StartupInfo.cb = sizeof(StartupInfo);

    PROCESS_INFORMATION ProcessInformation = {0};

    WCHAR CommandLine[] = LR"(P:\pe-debugger\build\Debug\pe-debuggee.exe)";
    LPCWSTR CurrentDirectory = nullptr;

    assert(CreateProcessW(
        nullptr, CommandLine, nullptr, nullptr, false, DEBUG_ONLY_THIS_PROCESS | CREATE_NEW_CONSOLE, nullptr,
        CurrentDirectory, &StartupInfo, &ProcessInformation));
    assert(GetLastError() == NO_ERROR);

    while (1) {
        DWORD ContinueStatus = DBG_EXCEPTION_NOT_HANDLED;
        DEBUG_EVENT DebugEvent = {0};
        assert(WaitForDebugEventEx(&DebugEvent, INFINITE));

        switch (DebugEvent.dwDebugEventCode) {
        case EXCEPTION_DEBUG_EVENT: {
            EXCEPTION_RECORD *ExceptionRecord = &DebugEvent.u.Exception.ExceptionRecord;

            printf("DBGEVENT: Exception (%s)\n", ExceptionCodeToString(ExceptionRecord->ExceptionCode));
        } break;
        case CREATE_THREAD_DEBUG_EVENT:
            puts("DBGEVENT: CREATE_THREAD_DEBUG_EVENT");
            break;
        case CREATE_PROCESS_DEBUG_EVENT:
            puts("DBGEVENT: CREATE_PROCESS_DEBUG_EVENT");
            break;
        case EXIT_THREAD_DEBUG_EVENT:
            puts("DBGEVENT: EXIT_THREAD_DEBUG_EVENT");
            break;
        case EXIT_PROCESS_DEBUG_EVENT:
            puts("DBGEVENT: EXIT_PROCESS_DEBUG_EVENT");
            break;
        case LOAD_DLL_DEBUG_EVENT:
            puts("DBGEVENT: LOAD_DLL_DEBUG_EVENT");
            break;
        case UNLOAD_DLL_DEBUG_EVENT:
            puts("DBGEVENT: UNLOAD_DLL_DEBUG_EVENT");
            break;
        case OUTPUT_DEBUG_STRING_EVENT: {
            LPOUTPUT_DEBUG_STRING_INFO OutputDebugStringInfo = &DebugEvent.u.DebugString;
            size_t StringBufferSize = OutputDebugStringInfo->nDebugStringLength + 1;
            char *StringBuffer = reinterpret_cast<char *>(malloc(StringBufferSize));
            ZeroMemory(StringBuffer, StringBufferSize);
            assert(ReadProcessMemory(
                ProcessInformation.hProcess, OutputDebugStringInfo->lpDebugStringData, StringBuffer,
                OutputDebugStringInfo->nDebugStringLength, nullptr));

            printf("DBGEVENT: OutputDebugString=(%s)\n", StringBuffer);

            free(StringBuffer);

            ContinueStatus = DBG_CONTINUE;
        } break;
        case RIP_EVENT:
            puts("DBGEVENT: RIP_EVENT");
            break;
        default:
            printf("DBGEVENT: UNHANDLED(%ld)\n", DebugEvent.dwDebugEventCode);
            break;
        }

        if (DebugEvent.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) {
            break;
        }

        assert(ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId, ContinueStatus));
    }

    return 0;
}
