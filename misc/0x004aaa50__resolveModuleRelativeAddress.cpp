// FUNC_NAME: resolveModuleRelativeAddress
// Function address: 0x004aaa50
// Role: Utility function to resolve an absolute address from a relative offset stored in a data structure,
// using the process image base address obtained from the Thread Environment Block (TEB) -> Process Environment Block (PEB).
// Used to convert RVAs (Relative Virtual Addresses) to actual memory pointers.

#include <intrin.h> // For __readfsdword

int __fastcall resolveModuleRelativeAddress(int param_1)
{
    // Read the PEB pointer from the TEB (FS segment offset 0x2C)
    void* peb = (void*)__readfsdword(0x2C);
    // PEB+0x08 contains the base address of the executable image (ImageBaseAddress)
    int imageBase = *(int*)((int)peb + 8);
    // The structure at param_1 holds a relative offset at offset 0x18
    int relativeOffset = *(int*)(param_1 + 0x18);
    // Return absolute address = image base + offset
    return imageBase + relativeOffset;
}