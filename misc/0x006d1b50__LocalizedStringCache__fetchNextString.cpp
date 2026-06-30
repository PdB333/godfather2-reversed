// FUNC_NAME: LocalizedStringCache::fetchNextString
// Address: 0x006d1b50
// This function manages a cache for localized strings. It checks the type of the string resource,
// and if not yet loaded, loads the string and marks it as initialized.
// On subsequent calls with the same resource handle, it advances to the next string in the sequence
// and returns true if the string has changed compared to the previous call.

#include <cstddef> // for NULL

// Forward declarations of called functions (unknown signatures from decompiled code)
// FUN_00424c90: likely returns an enum or type code for a resource handle.
// FUN_00425030: likely loads or finds the next string in a sequence for a given resource.
// Both are __fastcall or __thiscall; we assume they take the resource handle and optional current index.

int __fastcall getResourceType(int resourceHandle);
int __fastcall loadString(int resourceHandle, char* buffer, int currentIndex);

// Assuming this is a member function of a class that stores state.
// The structure at `this` (param_1) has the following layout:
// +0x00: bool isInitialized
// +0x04: int resourceHandle (e.g., hash or ID of the string resource)
// +0x08: int currentIndex (cursor for current string)
// +0x0C: int previousIndex (last returned index)
// +0x10: char stringBuffer[?] (buffer to hold the string, size unknown but at least 16 bytes)

bool __fastcall LocalizedStringCache::fetchNextString(char* thisPtr)
{
    int resourceHandle = *(int*)(thisPtr + 0x04);
    int resourceType = getResourceType(resourceHandle);

    if (resourceType == 4) {
        // Type 4 indicates an invalid or end-of-sequence marker
        return false;
    }

    if (*(thisPtr + 0x00) == 0) {
        // First call: load the initial string and mark as initialized
        int resultIndex = loadString(resourceHandle, thisPtr + 0x10, 0);
        *(int*)(thisPtr + 0x08) = resultIndex;
        *(int*)(thisPtr + 0x0C) = resultIndex;
        *(thisPtr + 0x00) = 1; // set initialized flag
        return true;
    }

    // Subsequent calls: load the next string and compare with previous
    int previousIndex = *(int*)(thisPtr + 0x0C);
    int currentIndex = *(int*)(thisPtr + 0x08);
    int newIndex = loadString(resourceHandle, thisPtr + 0x10, currentIndex);
    *(int*)(thisPtr + 0x08) = newIndex;

    // Return true if the string changed (index differs from previous)
    return newIndex != previousIndex;
}