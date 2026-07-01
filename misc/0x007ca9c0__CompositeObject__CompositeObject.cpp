// FUNC_NAME: CompositeObject::CompositeObject

// This function acts as a constructor for a composite object that initializes two sub-components.
// It calls the constructors of two base classes or embedded sub-objects at 0x006fbca0 and 0x006fc560.
// The single parameter (param_1) is the 'this' pointer, passed in ECX (__fastcall convention).

#include <cstdint>

class CompositeObject {
public:
    CompositeObject();
};

void __fastcall CompositeObject::CompositeObject(uint32_t thisPtr)
{
    // Initialize first sub-object (likely a base class or member)
    reinterpret_cast<void (__fastcall *)(uint32_t)>(0x006fbca0)(thisPtr);
    // Initialize second sub-object
    reinterpret_cast<void (__fastcall *)(uint32_t)>(0x006fc560)(thisPtr);
    return;
}