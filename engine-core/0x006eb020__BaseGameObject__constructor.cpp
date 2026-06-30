// FUNC_NAME: BaseGameObject::constructor
// Address: 0x006eb020
// This function is the constructor for a base game object that sets up multiple vtables (likely for multiple inheritance) and constructs sub-objects.
// The flag parameter may indicate dynamic allocation (bit 0 = allocated with new) – if set, the object is freed after construction? (unusual)
// Offsets: +0x00 vtable, +0x3C interface vtable A, +0x48 interface vtable B, +0x14 sub-object

class BaseGameObject {
public:
    void** vtable;               // +0x00: primary vtable (e.g., PTR_FUN_00d5fe00)
    // padding / other members
    void* interfaceVtableA;      // +0x3C: secondary vtable (PTR_LAB_00d5fdf0)
    void* interfaceVtableB;      // +0x48: secondary vtable (PTR_LAB_00d5fdec)
    // sub-object at +0x14 (20 bytes) – constructed by subConstructor1 and subConstructor2
    // Sub-object size unknown
    // Total object size appears to be 0x8C (140 bytes)
};

// Callees (forward declarations)
void __thiscall subConstructor1(void* subObj);   // FUN_004086d0
void __thiscall subConstructor2(void* subObj);   // FUN_00408310
void __cdecl globalInit(void);                   // FUN_0046c640
void __cdecl operatorDelete(BaseGameObject* ptr, uint size); // FUN_0043b960 (size = 0x8C)

// Constructor
BaseGameObject* __thiscall BaseGameObject::constructor(BaseGameObject* this, byte flag) {
    // Set the primary vtable pointer to the class's vtable
    this->vtable = &PTR_FUN_00d5fe00;

    // Set two interface/derived vtable pointers (likely for multiple inheritance stubs)
    this->interfaceVtableA = &PTR_LAB_00d5fdf0;   // +0x3C
    this->interfaceVtableB = &PTR_LAB_00d5fdec;   // +0x48

    // Construct the sub-object at offset 0x14 (e.g., base class or embedded member)
    subConstructor1((void*)((uint)this + 0x14));
    subConstructor2((void*)((uint)this + 0x14));

    // Call a global initialization routine (e.g., reference counting, manager registration)
    globalInit();

    // If the lowest bit of the flag is set, deallocate the object immediately.
    // This pattern is unusual but may indicate a custom placement new / failure path.
    if ((flag & 1) != 0) {
        operatorDelete(this, 0x8C);
    }

    return this;
}