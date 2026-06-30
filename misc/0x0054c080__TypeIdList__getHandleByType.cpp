// FUNC_NAME: TypeIdList::getHandleByType
#include <types.h>

// Struct representing a list of type IDs with associated handles.
// Offsets based on decompilation:
// +0x74: int* typeIds; // array of type IDs
// +0x78: int typeCount; // number of entries
struct TypeIdList {
    int* typeIds;     // +0x74
    int typeCount;    // +0x78
};

// Called function: retrieves or creates a handle for the given type ID.
// Probably returns a 32-bit handle/object reference.
void __cdecl getHandleForType(int* outHandle, int typeId); // placeholder for FUN_004af8c0

// Searches the type list for a match with 0x2003.
// If found, retrieves the associated handle and writes it to outHandle.
// Otherwise, writes a predefined invalid handle (0xfe16702f).
// Returns outHandle for chaining.
undefined4* __thiscall TypeIdList::getHandleByType(undefined4* outHandle) {
    int i = 0;
    *outHandle = 0xfe16702f; // default invalid handle
    if (0 < this->typeCount) {
        int* typeIter = this->typeIds;
        // Linear search for type ID 0x2003
        while (*typeIter != 0x2003) {
            i++;
            typeIter++;
            if (this->typeCount <= i) {
                return outHandle;
            }
        }
        // Found: obtain handle for type 0x2003
        int localHandle;
        getHandleForType(&localHandle, 0x2003);
        *outHandle = localHandle;
    }
    return outHandle;
}