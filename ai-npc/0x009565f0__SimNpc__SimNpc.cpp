// FUNC_NAME: SimNpc::SimNpc
// Address: 0x009565f0
// Role: Constructor for SimNpc class. Initializes base object and sets vtable pointers.
// Offsets used: +0x00 (vtable), +0x3C (vtable slot 0xF), +0x48 (vtable slot 0x12), +0x50 (vtable slot 0x14)

class SimNpc : public FrameworkObject { // Base class likely Framework::Object
public:
    // Virtual function table pointer at +0x00
    // Additional vtable-like function pointers at +0x3C, +0x48, +0x50
    SimNpc() {
        // Set base vtable
        this->vtable = (void**)&PTR_FUN_00d8c100;       // +0x00
        *(void**)((uint8*)this + 0x3C) = &PTR_LAB_00d8c0f0; // +0x3C
        *(void**)((uint8*)this + 0x48) = &PTR_LAB_00d8c0ec; // +0x48
        *(void**)((uint8*)this + 0x50) = &PTR_LAB_00d8c0e8; // +0x50

        // Call base object constructor with parameter 0
        baseConstructor(0); // FUN_00976380

        // Override vtable with derived class vtable
        this->vtable = (void**)&PTR_FUN_00e32b30;       // +0x00
        *(void**)((uint8*)this + 0x3C) = &PTR_LAB_00e32b50; // +0x3C
        *(void**)((uint8*)this + 0x48) = &PTR_LAB_00e32b60; // +0x48
        *(void**)((uint8*)this + 0x50) = &PTR_LAB_00e32b64; // +0x50 (first set, later overwritten)
        *(void**)((uint8*)this + 0x50) = &PTR_LAB_00e32854; // +0x50 final override

        // Final initialization
        finalizeInit(); // FUN_0046c640
    }

private:
    void baseConstructor(int flag);  // FUN_00976380
    void finalizeInit();             // FUN_0046c640
};