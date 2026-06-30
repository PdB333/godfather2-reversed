// FUNC_NAME: SomeGameObject::constructor
// Function address: 0x00618130
// Purpose: Constructor for a game object. Calls base constructor, zeros three fields at offsets 0xA4, 0xA8, 0xAC, and sets vtable to 0x00e40d6c.
// Likely base class for several game subsystems (NPC, Player, etc.)

// Reconstructed C++ (__thiscall)
class SomeGameObject; // forward declaration

// External base constructor (unknown class)
extern void __thiscall baseCtor(SomeGameObject* this); // Address 0x006126d0

// VTable for this class
extern void* vtable_SomeGameObject; // Address 0x00e40d6c

// Object layout (partial):
// +0x00: vtable pointer
// +0xA4: field_0xA4 (int)
// +0xA8: field_0xA8 (int)
// +0xAC: field_0xAC (int)

class SomeGameObject {
public:
    void** vtable;
    int field_0xA4;  // offset +0xA4
    int field_0xA8;  // offset +0xA8
    int field_0xAC;  // offset +0xAC

    // Constructor
    SomeGameObject() {
        // Call base constructor (address 0x006126d0)
        baseCtor(this);

        // Initialize fields to zero
        field_0xA4 = 0;
        field_0xA8 = 0;
        field_0xAC = 0;

        // Set vtable pointer
        vtable = &vtable_SomeGameObject;
    }
};