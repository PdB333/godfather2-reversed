// FUNC_NAME: Unknown::checkAndSetPointer
#include <cstdint>

// Function at 0x006e51f0
// Likely a member function of a class with a large object (size > 0x100).
// Access a pointer at offset 0x100 from 'this', then call a function at offset 0x10 from that pointer.
// The argument 0x383225a1 is probably a hash or identifier.
// Sets a pointer (possibly at this) based on the result.

typedef char (__fastcall *CheckFunc)(int hash); // __fastcall for simplicity

void __thiscall Unknown::checkAndSetPointer(void* thisPtr) {
    int* thisInt = (int*)thisPtr;
    
    // Pointer stored at offset 0x100 from this
    char* basePtr = *(char**)((char*)thisInt + 0x100); // +0x100

    // Function pointer at offset 0x10 from basePtr
    CheckFunc func = *(CheckFunc*)(basePtr + 0x10);

    // Call the function with a constant hash
    char result = func(0x383225a1);

    // Depending on result, set something (possibly a member at this)
    // Note: decompilation shows *thisInt = (int)&thisInt in both branches.
    // This is likely a misrepresentation; actual code probably sets a different pointer.
    // Possibly sets a member to either a valid pointer or null.
    if (result) {
        // Set a member (maybe at offset 0x00?) to address of thisInt on stack? Unlikely.
        // Assume it sets a pointer stored at this to some value.
        // The warning about unreachable block suggests control flow is different.
        // Placeholder: assign a meaningful value.
        *(int**)thisInt = (int*)0x0; // example: null pointer
    } else {
        *(int**)thisInt = (int*)0x0; // same as above, but original may differ
    }
}