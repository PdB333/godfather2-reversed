// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x0094f750
// Constructor for GodfatherGameManager; initializes base class and zeroes many members.

uint32* __thiscall GodfatherGameManager::GodfatherGameManager(uint32* this, uint32 arg) {
    // Call base class constructor (FUN_0046c590)
    FUN_0046c590(arg);

    // Set vtable pointer
    *this = (uint32)&PTR_FUN_00d8bac0;

    // Set function pointers (likely virtual method table entries or callbacks)
    this[0xF] = (uint32)&PTR_LAB_00d8bab0;  // offset +0x3C
    this[0x12] = (uint32)&PTR_LAB_00d8baac; // offset +0x48

    // Zero out fields (various sizes)
    this[0x14] = 0;                           // offset +0x50 (uint32)
    *(uint16*)((uint8*)this + 0x54) = 0;      // offset +0x54 (uint16)
    *(uint16*)((uint8*)this + 0x56) = 0;      // offset +0x56 (uint16)
    this[0x16] = 0;                           // offset +0x58 (uint32)
    *(uint16*)((uint8*)this + 0x5C) = 0;      // offset +0x5C (uint16)
    *(uint16*)((uint8*)this + 0x5E) = 0;      // offset +0x5E (uint16)
    this[0x18] = 0;                           // offset +0x60 (uint32)
    this[0x19] = 0;                           // offset +0x64 (uint32)
    *(uint8*)((uint8*)this + 0x68) = 0;       // offset +0x68 (uint8)

    return this;
}