// FUNC_NAME: AptSystem::validateImportTarget
// Address: 0x0059e490
// From: ..\source\Apt\Apt.cpp (line references: 0xe2=226, 0xe5=229)
// Purpose: Validates that the APT system is initialized before targeting "#import",
//          and emits an assertion error if the deprecated "#import" target is used.

#include <cstring>
#include <cstdint>

// External globals (from Apt.cpp)
extern bool g_bAptIsInitialized;        // DAT_012055b0
extern int g_assertEnabledFlag1;        // DAT_01128f3d
extern int g_assertEnabledFlag2;        // DAT_01128f3e
extern void* (*g_memFree)(void*);       // DAT_0119caf4 (deallocator)

// Internal functions (declared in AptNativeString namespace)
// FUN_005a0980: returns a hidden pointer to the global "empty" AptNativeString object
int* AptNativeString_GetEmpty();
// FUN_005a0a00: initializes an AptNativeString from an internal representation (likely a wide string)
void AptNativeString_InitFromInternal(int* dest);
// FUN_005a2870: assigns one AptNativeString to another
void AptNativeString_Assign(int* dest, int* src);

#define AssertExpression(exprStr, fileStr, lineVal, level, flagPtr) \
    do { \
        const char* _expr = (exprStr); \
        const char* _file = (fileStr); \
        int* _linePtr = reinterpret_cast<int*>((lineVal)); \
        int _level = (level); \
        int* _flagPtr = (flagPtr); \
        if (*_flagPtr != 0) { \
            int* fsBase = *(int**)__readfsdword(0x2C); \
            int* debugObj = *(int**)(*fsBase + 0x30); \
            uint flags = 1; \
            if ((debugObj != nullptr) || ( \
                flags = (reinterpret_cast<uint(__stdcall*)(const char**, const char*)>( \
                    *(void**)(*debugObj + 8)))(&_expr, _file), \
                _flagPtr != nullptr)) { \
                if (flags & 2) { \
                    *_flagPtr = 0; \
                } \
            } \
            if ((debugObj != nullptr) || (_level != 4)) { \
                if ((flags & 1) || (_level == 0 || _level == 1)) { \
                    __asm int 3; \
                    return; \
                } \
            } \
        } \
    } while(0)

void AptSystem::validateImportTarget()
{
    // Step 1: Ensure APT system is initialized before any target manipulation
    if (!g_bAptIsInitialized)
    {
        AssertExpression(
            "bAptIsInitialized",
            "..\\source\\Apt\\Apt.cpp",
            0xe2,               // line 226
            2,
            &g_assertEnabledFlag1
        );
    }

    // Step 2: Compare current target string (stored in some global or internal state) against "#import"
    // The exact source of the target string is not visible in this compound; it may be extracted
    // from a global variable or from the return of a previous call.
    // For reconstruction, we assume the target is accessed through a local AptNativeString.

    int* emptyString = AptNativeString_GetEmpty();        // Get reference to static empty native string
    int* currentTargetPtr = AptNativeString_GetEmpty();   // Second call likely returns a different state

    // local_1c is used as a 2-int buffer for an AptNativeString; puStack_14 points to its data.
    // Declare them as part of the assertion block:
    int local_1c[2];
    char* puStack_14;

    // Simple string comparison (as decompiled):
    bool bEqual;
    bEqual = (local_1c[0] == *currentTargetPtr);
    if (bEqual)
    {
        // Compare byte by byte (ASCII; may be 8-bit characters)
        int i;
        for (i = 0; i < local_1c[0]; i++)
        {
            if (puStack_14[i] != *(char*)(i + currentTargetPtr[2]))
            {
                bEqual = false;
                break;
            }
        }
    }
    else
    {
        bEqual = false;
    }

    // If the target equals "#import", emit deprecation warning
    if (bEqual)
    {
        AssertExpression(
            "sTarget != AptNativeString(\"#import\") && \"Please use AptPreloadFile instead of a target of \\'#import\\' now.\"",
            "..\\source\\Apt\\Apt.cpp",
            0xe5,               // line 229
            2,
            &g_assertEnabledFlag2
        );
    }

    // Initialize the AptNativeString from internal representation (likely from a wider string)
    AptNativeString_InitFromInternal(local_1c);

    // Get an empty string again (maybe to assign the result of the init?)
    int* resultString = AptNativeString_GetEmpty();
    AptNativeString_Assign(resultString, local_1c);

    // Clean up dynamically allocated memory (if line pointer was allocated)
    // Note: In EA's assertion macro, the line pointer may be a dynamically allocated string;
    // here it's a cast of an integer, so this check is unlikely to trigger.
    if ((reinterpret_cast<int*>(0xe2) != &local_1c[0]) && (reinterpret_cast<int*>(0xe2) != nullptr))
    {
        g_memFree(reinterpret_cast<void*>(0xe2));
    }
    if ((puStack_14 != nullptr) && (puStack_14 != reinterpret_cast<char*>(local_1c)))
    {
        g_memFree(puStack_14);
    }
}