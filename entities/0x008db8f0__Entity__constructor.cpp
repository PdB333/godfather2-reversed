// FUNC_NAME: Entity::constructor
// Address: 0x008db8f0
// Role: Constructor for an Entity object (likely a base game object in EARS engine)
// Sets up vtable pointers, initializes fields, and optionally allocates a resource via FUN_00481610

class Entity {
public:
    // offset +0x00: vtable pointer (virtual table)
    // offset +0x04: unknown (4 bytes)
    // offset +0x08: field at index 2
    // offset +0x0C: field at index 3
    // offset +0x10: field at index 4
    // offset +0x14: field at index 5 (pointer to self+0x28)
    // offset +0x18: field at index 6 (zero)
    // offset +0x1C: field at index 7
    // offset +0x20: field at index 8
    // offset +0x24: field at index 9 (set to 1)
    // offset +0x28: field at index 10 (pointer to a vtable, 0x00d7e088)
    // offset +0x2C: field at index 11
    // offset +0x30: field at index 12 (function pointer, 0x008db4a0)
    // offset +0x34: field at index 13 (zero)

    // __thiscall constructor
    // param_2: if non-zero, triggers an allocation/initialization (e.g., resource ID)
    Entity* constructor(int param_2) {
        int uVar1;

        // If param_2 is 0, no allocation; else call FUN_00481610 to obtain some value
        if (param_2 == 0) {
            uVar1 = 0;
        } else {
            uVar1 = FUN_00481610();  // e.g., allocate a resource or generate ID
        }

        // Unknown initialization call (FUN_0064d390) with parameters (1,1)
        FUN_0064d390(1, 1);

        // Set initial vtable (base class vtable, later overwritten)
        this->vfptr = &PTR_LAB_00e317dc;

        // Set field at offset +0x18 (index 6) to 0
        this->field_6 = 0;

        // Call a function with the value obtained from the allocation
        FUN_00454a10(uVar1);

        // Set field at offset +0x24 (index 9) to 1
        this->field_9 = 1;

        // Overwrite vtable with derived class vtable
        this->vfptr = &PTR_LAB_00d7e0dc;

        // Set field at offset +0x28 (index 10) to a secondary vtable (likely for multiple inheritance)
        this->field_10 = &PTR_LAB_00d7e088;

        // Set field at offset +0x30 (index 12) to a function pointer (likely a virtual dispatch or callback)
        this->field_12 = &LAB_008db4a0;

        // Set field at offset +0x34 (index 13) to 0
        this->field_13 = 0;

        // Set field at offset +0x14 (index 5) to point to itself at offset +0x28
        // This is often a self-referential pointer used for a linked list or polymorphic base
        this->field_5 = (int*)((char*)this + 0x28);  // offset 0x28

        return this;
    }

    // Placeholder for external functions (stubs)
    // These would be linked from the game binary
private:
    static int FUN_00481610();
    static void FUN_0064d390(int, int);
    static void FUN_00454a10(int);

    // Vtable pointers (external symbols)
    static void* PTR_LAB_00e317dc;
    static void* PTR_LAB_00d7e0dc;
    static void* PTR_LAB_00d7e088;
    static void* LAB_008db4a0;

    // Fields (order as they appear in memory)
    void* vfptr;               // +0x00
    int unknown_04;            // +0x04
    int field_2;               // +0x08
    int field_3;               // +0x0C
    int field_4;               // +0x10
    void* field_5;             // +0x14 (pointer to self+0x28)
    int field_6;               // +0x18 (set to 0)
    int field_7;               // +0x1C
    int field_8;               // +0x20
    int field_9;               // +0x24 (set to 1)
    void* field_10;            // +0x28 (pointer to secondary vtable)
    int field_11;              // +0x2C
    void* field_12;            // +0x30 (function pointer)
    int field_13;              // +0x34 (set to 0)
};

// Note: Actual implementation of external functions and symbols would be in the binary.
// The field naming is arbitrary; they correspond to param_1[index] where index is byte offset/4.