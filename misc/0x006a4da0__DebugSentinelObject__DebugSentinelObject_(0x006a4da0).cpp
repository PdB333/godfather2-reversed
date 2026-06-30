// FUNC_NAME: DebugSentinelObject::DebugSentinelObject (0x006a4da0)
// Constructor for a debug/sentinel object used for tracking initialization state.
// Called with an initialization parameter (likely a pointer to some configuration or debug manager).
// Setups vtable, two function table pointers, four sentinel magic values, and a flag byte.

class DebugSentinelObject {
public:
    // Member function - __thiscall constructor
    __thiscall DebugSentinelObject* DebugSentinelObject(DebugSentinelObject* this, int initData) {
        // Call base/helper initialization (likely sets up some internal state)
        FUN_0046c590(initData);

        // Virtual function table pointer at offset 0x00
        this->vtable = &PTR_FUN_00d5d768;

        // Pointers to additional function tables (possibly for debug hooks or type info)
        // offset +0x3C (param_1[0xf])
        this->debugTable1 = &PTR_LAB_00d5d758;

        // offset +0x48 (param_1[0x12])
        this->debugTable2 = &PTR_LAB_00d5d754;

        // Sentinel values to detect uninitialized or corrupted memory (EA debug pattern)
        // offset +0x50
        this->sentinel1 = 0xBADBADBA;

        // offset +0x54
        this->sentinel2 = 0xBEEFBEEF;

        // offset +0x58
        this->sentinel3 = 0xEAC15A55;

        // offset +0x5C
        this->sentinel4 = 0x91100911;

        // offset +0x60 (single byte flag, set to 0 indicating initial state)
        this->initFlag = 0;

        return this;
    }

private:
    // Reconstructed fields based on offset documentation above
    void* vtable;               // +0x00
    // ... other fields ...
    void* debugTable1;          // +0x3C
    void* debugTable2;          // +0x48
    int sentinel1;              // +0x50
    int sentinel2;              // +0x54
    int sentinel3;              // +0x58
    int sentinel4;              // +0x5C
    unsigned char initFlag;     // +0x60
};

// The actual function definition (note: the class definition above is illustrative;
// in the binary the fields are accessed via direct offset arithmetic).
// The full decompiled version with explicit offsets:

// DebugSentinelObject* __thiscall FUN_006a4da0(DebugSentinelObject* this, int initData) {
//     FUN_0046c590(initData);                                    // base init
//     this->vtable = &PTR_FUN_00d5d768;                         // +0x00
//     *(void**)((unsigned char*)this + 0x3C) = &PTR_LAB_00d5d758; // +0x3C
//     *(void**)((unsigned char*)this + 0x48) = &PTR_LAB_00d5d754; // +0x48
//     *(int*)((unsigned char*)this + 0x50) = 0xBADBADBA;        // +0x50
//     *(int*)((unsigned char*)this + 0x54) = 0xBEEFBEEF;        // +0x54
//     *(int*)((unsigned char*)this + 0x58) = 0xEAC15A55;        // +0x58
//     *(int*)((unsigned char*)this + 0x5C) = 0x91100911;        // +0x5C
//     *(unsigned char*)((unsigned char*)this + 0x60) = 0;       // +0x60
//     return this;
// }