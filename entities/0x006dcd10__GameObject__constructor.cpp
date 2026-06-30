// FUNC_NAME: GameObject::constructor
// Function address: 0x006dcd10
// Role: Constructor for a game object with multiple inheritance vtables

class GameObject {
public:
    // Constructor (__thiscall, this in ECX)
    GameObject() {
        // Call base class constructor (likely EARSObject or similar)
        // FUN_004737b0
        baseConstructor();

        // Set primary vtable pointer
        // +0x00
        this->vtable = &VTABLE_GameObject; // PTR_FUN_00d5f678

        // Set additional vtable pointers for derived interfaces
        // +0x3C (0xf * 4)
        this->interfaceVtable1 = &VTABLE_Interface1; // PTR_LAB_00d5f668
        // +0x48 (0x12 * 4)
        this->interfaceVtable2 = &VTABLE_Interface2; // PTR_LAB_00d5f664
        // +0x50 (0x14 * 4)
        this->interfaceVtable3 = &VTABLE_Interface3; // PTR_LAB_00d5f660

        // Initialize four pointer fields to null
        // +0x58 (0x16 * 4)
        this->somePtr1 = nullptr;
        // +0x5C (0x17 * 4)
        this->somePtr2 = nullptr;
        // +0x60 (0x18 * 4)
        this->somePtr3 = nullptr;
        // +0x64 (0x19 * 4)
        this->somePtr4 = nullptr;

        // Call derived class initializer
        // FUN_006dc940
        derivedInit();
    }

private:
    // Base class members (inherited from baseConstructor)
    // ...

    // Vtable pointer (primary)
    void* vtable; // +0x00

    // Interface vtable pointers (multiple inheritance)
    void* interfaceVtable1; // +0x3C
    void* interfaceVtable2; // +0x48
    void* interfaceVtable3; // +0x50

    // Unknown pointer fields
    void* somePtr1; // +0x58
    void* somePtr2; // +0x5C
    void* somePtr3; // +0x60
    void* somePtr4; // +0x64
};