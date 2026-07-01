// FUNC_NAME: Event::create
// Function address: 0x009473d0
// Allocates and constructs a reference-counted Event object with 6 parameters.
// Object size: 0x38 bytes (14 ints). Layout:
// +0x00: vtable pointer (PTR_LAB_00d8b4e8)
// +0x04: unknown (piVar2[1])
// +0x08: reference count (piVar2[2])
// +0x0c: unknown (piVar2[3])
// +0x10: unknown (piVar2[4])
// +0x14: pointer to self+0x18 (piVar2[5] = piVar2+6)
// +0x18: vtable2 pointer (PTR_LAB_00d8b480)
// +0x1c: function pointer (LAB_00946eb0)
// +0x20: param_1 (piVar2[8])
// +0x24: param_2 (piVar2[9])
// +0x28: param_3 (piVar2[10])
// +0x2c: param_4 (piVar2[0xb])
// +0x30: param_5 (piVar2[0xc])
// +0x34: param_6 (byte, piVar2[0xd])

class Event {
public:
    // Vtable structure assumed
    struct VTable {
        void* destructor; // offset 0
        // ... other virtual functions
    };

    VTable* vtable;          // +0x00
    int field_4;             // +0x04
    int refCount;            // +0x08
    int field_C;             // +0x0c
    int field_10;            // +0x10
    int* selfPtr;            // +0x14 (points to vtable2)
    VTable* vtable2;         // +0x18
    void (*funcPtr)();       // +0x1c
    int param1;              // +0x20
    int param2;              // +0x24
    int param3;              // +0x28
    int param4;              // +0x2c
    int param5;              // +0x30
    unsigned char param6;    // +0x34 (byte)

    static Event* create(int param1, int param2, int param3, int param4, int param5, unsigned char param6) {
        // Allocate memory (0x38 bytes)
        Event* evt = (Event*)FUN_009c8e50(0x38); // likely operator new
        if (evt != nullptr) {
            // Initialize reference counting system
            FUN_004b1da0(1, 1);
            // Set vtable pointers and function pointer
            evt->vtable = (VTable*)&PTR_LAB_00d8b4e8;
            evt->vtable2 = (VTable*)&PTR_LAB_00d8b480;
            evt->funcPtr = &LAB_00946eb0;
            // Another initialization
            FUN_004a8f30(0);
            // Set self-pointer to point to vtable2 offset
            evt->selfPtr = (int*)(&evt->vtable2);
            // Increment reference count
            evt->refCount++;
        }
        // Set parameters
        evt->param2 = param2;
        evt->param1 = param1;
        evt->param3 = param3;
        evt->param5 = param5;
        evt->param4 = param4;
        evt->param6 = param6;
        // Finalize initialization
        FUN_004b1e60();
        // Decrement reference count and possibly delete
        if (evt != nullptr) {
            int* refPtr = &evt->refCount;
            (*refPtr)--;
            if (*refPtr == 0) {
                // Call destructor via vtable
                (evt->vtable->destructor)();
                return nullptr; // object deleted
            }
        }
        return evt;
    }
};