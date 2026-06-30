// FUNC_NAME: reportTypeMismatch
// Address: 0x00627ac0
// Role: Debug assertion function that prints a type mismatch error and triggers a breakpoint.
// Used in many places to validate that an object's dynamic type matches an expected type name.

#include <cstdint>

// Global table of type name strings indexed by type ID
extern const char* g_typeNames[];

// Returns a pointer to an integer type ID from the current type system context
// Returns nullptr if no context available
extern int* getCurrentTypeId();  // FUN_00625430

// Debug printf function
extern void debugPrintf(const char* format, ...);  // FUN_00625d40

// Abort / break into debugger
extern void debugAssertBreak();  // FUN_00627a20

// __fastcall: ECX = typeSystem, EDX = actualTypeIndex, stack = expectedTypeName
void __fastcall reportTypeMismatch(void* typeSystem, int actualTypeIndex, const char* expectedTypeName)
{
    const char* actualTypeName;
    int* typeIdPtr;

    if (actualTypeIndex < 1) {
        // For non-positive indexes, get the current type ID via system callback
        typeIdPtr = getCurrentTypeId();
        // Fall through to the check below
    }
    else {
        // For positive index, try to look up from the array stored in the type system
        // The array is at *(typeSystem+0xC) - 8, with 8-byte entries.
        // End pointer is at *(typeSystem+0x8)
        int* arrayBase = *(int**)((uintptr_t)typeSystem + 0xC);
        int* entryPtr = arrayBase - 2 + actualTypeIndex * 2;  // -2 because of 8-byte (2 int) entries? Simplified: pointer arithmetic on int*
        if (entryPtr < *(int**)((uintptr_t)typeSystem + 0x8)) {
            typeIdPtr = entryPtr;
            // Check if the entry is valid (first int != -1)
            if (typeIdPtr != nullptr && *typeIdPtr != -1) {
                actualTypeName = g_typeNames[*typeIdPtr];
                goto printError;
            }
        }
        // Fallback: use system callback
        typeIdPtr = getCurrentTypeId();
    }

    // Fallback: check if we got a valid type ID
    if (typeIdPtr != nullptr && *typeIdPtr != -1) {
        actualTypeName = g_typeNames[*typeIdPtr];
    }
    else {
        actualTypeName = "no value";
    }

printError:
    debugPrintf("%s expected, got %s", expectedTypeName, actualTypeName);
    debugAssertBreak();

    // Trigger a debug break via software interrupt
    __asm { int 3 }
}