// FUNC_NAME: GameObject::GameObject (constructor at 0x0047c700)
// Initializes a game object with multiple vtable pointers and zeroed fields
// Calls base class constructor then sets up derived-specific vtable entries

// Assumed base class constructor
extern void BaseObject::BaseObject(int param);

// Vtable symbols (extern pointers, defined elsewhere)
extern void* vtable_GameObject;          // PTR_FUN_00e331b0
extern void* vtable_GameObject_sub1;     // PTR_LAB_00e331d0
extern void* vtable_GameObject_sub2;     // PTR_LAB_00e331e0

class GameObject {
public:
    // +0x00: primary vtable pointer
    void* vtable;
    // +0x04 to +0x3B: base object fields (inherited)
    // +0x3C: secondary vtable pointer (offset 0xf)
    void* vtableSub1;
    // +0x40 to +0x47: unknown
    // +0x48: tertiary vtable pointer (offset 0x12)
    void* vtableSub2;
    // +0x4C: unknown
    // +0x50: uint32 (offset 0x14)
    uint32_t field_0x50;
    // +0x54: uint16 (offset 0x15)
    uint16_t field_0x54;
    // +0x56: uint16 (offset 0x56)
    uint16_t field_0x56;
    // +0x58: uint32 (offset 0x16)
    uint32_t field_0x58;

    // Constructor – __thiscall, param2 passed to base ctor
    GameObject(int param2) {
        // Call base constructor (e.g., entity/object base)
        BaseObject::BaseObject(param2);

        // Set vtable pointers for this derived class
        vtable = &vtable_GameObject;              // *this = &PTR_FUN_00e331b0
        vtableSub1 = &vtable_GameObject_sub1;     // this[0xf] = &PTR_LAB_00e331d0
        vtableSub2 = &vtable_GameObject_sub2;     // this[0x12] = &PTR_LAB_00e331e0

        // Zero out remaining fields
        field_0x50 = 0;      // this[0x14] = 0
        field_0x54 = 0;      // *(uint16*)(this + 0x54) = 0
        field_0x56 = 0;      // *(uint16*)((int)this + 0x56) = 0
        field_0x58 = 0;      // this[0x16] = 0
    }
};