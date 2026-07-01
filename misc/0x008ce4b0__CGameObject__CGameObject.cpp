// FUNC_NAME: CGameObject::CGameObject

// Reconstructed C++ constructor for class CGameObject
// Function address: 0x008ce4b0
// Calls subobject constructor at offset 0x14 (possibly a base class or member)
// Sets three vtable pointers: main at +0x00, secondary at +0x3C, tertiary at +0x48
// Global init call: FUN_0046c640 (likely engine-wide registration)
// If isAllocated flag is set, deallocation function is called for exception safety

class CGameObject {
public:
    void* vtable;               // +0x00
    // +0x04 to +0x38: other members (unknown)
    void* secondaryVtable;      // +0x3C
    void* tertiaryVtable;       // +0x48
    // +0x4C: padding? Then subobject at +0x50
    // Subobject of unknown type starts at offset 0x14 words = 0x50 bytes
};

// Forward declare subobject class (we only need its constructor signatures)
class CSubObject;

// __thiscall constructor
CGameObject* __thiscall CGameObject::CGameObject(CGameObject* this, byte isAllocated) {
    // Set vtable pointers (multiple inheritance support)
    this->vtable = &PTR_FUN_00d7cae8;      // primary vtable
    this->secondaryVtable = &PTR_LAB_00d7cad8;  // +0x3C
    this->tertiaryVtable = &PTR_LAB_00d7cad4;   // +0x48

    // Initialize subobject at offset +0x14 (0x50) – two-step construction
    CSubObject* sub = reinterpret_cast<CSubObject*>(reinterpret_cast<char*>(this) + 0x50);
    FUN_004086d0(sub);  // subobject constructor call (base init)
    FUN_00408310(sub);  // subobject additional initialization

    // Global engine initialization (e.g., registration into a manager)
    FUN_0046c640();

    // If this object was dynamically allocated, register deallocation for exception safety
    if ((isAllocated & 1) != 0) {
        FUN_0043b960(this, 0x6c);  // likely operator delete or an exception cleanup
    }

    return this;
}