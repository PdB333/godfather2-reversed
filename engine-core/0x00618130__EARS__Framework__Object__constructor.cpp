// FUNC_NAME: EARS::Framework::Object::constructor
// Function address: 0x00618130
// Role: Constructor for a base EARS framework object with vtable initialization and zeroing of three fields at offsets 0xA4, 0xA8, 0xAC.

namespace EARS {
namespace Framework {

class Object {
public:
    // Virtual table pointer at offset 0x00.
    // Base constructor at 0x006126d0.
    // Offsets: +0x0 = vtable*, +0xA4 = field29, +0xA8 = field2A, +0xAC = field2B.
    static void* VTABLE_REF; // &PTR_LAB_00e40d6c
};

} // namespace Framework
} // namespace EARS

__thiscall EARS::Framework::Object* FUN_00618130(void) {
    EARS::Framework::Object* thisPtr;

    // Call base class constructor (returns this in EDX)
    thisPtr = (EARS::Framework::Object*)FUN_006126d0();

    // Initialize three fields to zero (offsets 0xA4, 0xA8, 0xAC)
    thisPtr->field29 = 0;
    thisPtr->field2A = 0;
    thisPtr->field2B = 0;

    // Set vtable pointer
    thisPtr->vtable = &EARS::Framework::Object::VTABLE_REF;

    return thisPtr;
}