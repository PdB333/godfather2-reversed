// FUNC_NAME: RefCounted::releaseInternal
// Function at 0x004ee9f0: Releases a reference-counted object.
// Decrements the refcount, and if it reaches zero, calls the destructor.
// The vtable function at offset +8 determines if the release should be considered successful.
// param_1 (ecx) is unused, param_2 (edx) is an identifier/context, param_3 is a pointer to the refcount block.
// Struct layout of param_3:
//   +0x00: pointer to vtable (array of function pointers)
//   +0x04: refcount (int)
// vtable[1] (+0x04 from vtable ptr): destructor/cleanup function
// vtable[2] (+0x08 from vtable ptr): query function taking param_2, returns bool

#include <cstdint>

typedef void (__fastcall *DestructorFunc)(void);
typedef bool (__fastcall *ReleaseCheckFunc)(void* param2);

// __fastcall: param_1 in ecx, param_2 in edx, param_3 on stack
bool __fastcall releaseRefCounted(void* unused, void* param2, int* refBlock)
{
    if (refBlock == nullptr)
        return false;

    void** vtable = reinterpret_cast<void**>(*refBlock);  // vtable pointer at +0x00
    ReleaseCheckFunc canRelease = reinterpret_cast<ReleaseCheckFunc>(vtable[2]); // third function at vtable+8

    if (canRelease(param2))
    {
        // Decrement refcount at +0x04
        int* refCount = refBlock + 1; // offset 4
        (*refCount)--;
        if (*refCount == 0)
        {
            // Call destructor at vtable+4
            DestructorFunc destructor = reinterpret_cast<DestructorFunc>(vtable[1]);
            destructor();
        }
        return true; // Successful release
    }
    else
    {
        // Decrement refcount regardless but return false
        int* refCount = refBlock + 1;
        (*refCount)--;
        if (*refCount == 0)
        {
            DestructorFunc destructor = reinterpret_cast<DestructorFunc>(vtable[1]);
            destructor();
        }
        return false; // Release not allowed
    }
}