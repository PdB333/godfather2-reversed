// FUNC_NAME: EARSObject::releaseRef
#include <cstddef>

// Forward declaration
class EARSObject;

// Typedefs for virtual function pointers
typedef bool (__thiscall* CanReleaseFunc)(EARSObject* obj, int caller);
typedef void (__thiscall* DestroyFunc)(EARSObject* obj);

// Structure representing a ref-counted object (vtable + ref count at +0x04)
class EARSObject {
public:
    void** vtable;      // +0x00
    int   refCount;     // +0x04
};

// __fastcall: first arg (unused) in ECX, second arg (caller) in EDX, third arg (obj) on stack
bool __fastcall EARSObject::releaseRef(void* /*unused*/, int caller, EARSObject* obj)
{
    // If the object pointer is null, return false
    if (!obj)
        return false;

    // Call virtual function at vtable offset 0x08 (index 2) to determine success flag
    bool canRelease = reinterpret_cast<CanReleaseFunc>(obj->vtable[2])(obj, caller);

    // Decrement reference count (located at offset +0x04)
    obj->refCount--;

    // If reference count reached zero, call virtual destructor at vtable offset 0x04 (index 1)
    if (obj->refCount == 0) {
        reinterpret_cast<DestroyFunc>(obj->vtable[1])(obj);
    }

    // Return the success flag: true if canRelease returned non-zero, false otherwise
    return canRelease;
}