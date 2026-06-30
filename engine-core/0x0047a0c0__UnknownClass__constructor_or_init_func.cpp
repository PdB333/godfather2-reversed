// FUNC_NAME: UnknownClass::constructor_or_init_func
// Likely derived class constructor, base initialized via FUN_0046c590
// Object size: at least 0x64 bytes (0x14*4 + more)
class UnknownClass : public UnknownBase {
public:
    // Address: 0x0047a0c0
    UnknownClass(void* param_2) {
        // Call base class constructor
        UnknownBase::constructor(param_2); // FUN_0046c590

        // Vtable pointer at +0x00
        *(void**)this = (void*)&PTR_FUN_00e33050;  // vtable

        // Initialize various fields
        // Offset +0x3C (0xF*4): pointer to some static label
        *(void**)((char*)this + 0x3C) = &PTR_LAB_00e3306c;

        // Offset +0x48 (0x12*4): pointer to another static label
        *(void**)((char*)this + 0x48) = &PTR_LAB_00e3307c;

        // Offset +0x50 (0x14*4): int32 = 0
        *(int32*)((char*)this + 0x50) = 0;

        // Offset +0x54: int16 = 0
        *(int16*)((char*)this + 0x54) = 0;

        // Offset +0x56: int16 = 0
        *(int16*)((char*)this + 0x56) = 0;

        // Offset +0x58 (0x16*4): int32 = 0
        *(int32*)((char*)this + 0x58) = 0;

        // Offset +0x5C (0x17*4): int8 = 0
        *(int8*)((char*)this + 0x5C) = 0;

        // Offset +0x5D: int8 = 0
        *(int8*)((char*)this + 0x5D) = 0;

        // Offset +0x5E: int16 = 0
        *(int16*)((char*)this + 0x5E) = 0;

        // Offset +0x60 (0x18*4): int32 = -1 (0xFFFFFFFF)
        *(int32*)((char*)this + 0x60) = 0xFFFFFFFF;
    }
};