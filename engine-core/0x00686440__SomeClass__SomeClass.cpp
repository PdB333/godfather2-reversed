// FUNC_NAME: SomeClass::SomeClass

class SomeClass {
public:
    // Constructor with allocation flag (param_2 bit 0 controls allocation)
    // Vtable pointers:
    //   this[0] -> Primary vtable at 0x00d58958
    //   this[0x3C] -> Secondary vtable at 0x00d58948
    //   this[0x48] -> Tertiary vtable at 0x00d58944
    // Object size: 0x70 bytes
    SomeClass(uint8_t param_2) {
        // Set up vtable pointers (likely multiple inheritance)
        this->vtable = &PTR_FUN_00d58958;          // +0x00
        *(void**)((uint32_t)this + 0x3C) = &PTR_LAB_00d58948; // +0x3C
        *(void**)((uint32_t)this + 0x48) = &PTR_LAB_00d58944; // +0x48

        // Call base class constructor/initializer
        FUN_00895330();

        // If param_2 bit 0 is set, perform additional allocation/cleanup
        if (param_2 & 1) {
            // Likely operator new or memory manager call for size 0x70
            // (EA EARS pattern: if flag set, allocate memory for object)
            FUN_0043b960(this, 0x70);
        }
    }
};