// FUNC_NAME: Player::constructor
void __fastcall Player::constructor(undefined4 *self)
{
    // vtable pointer at offset 0x00
    *self = &PTR_FUN_00d8314c;
    
    // Additional function pointer at offset 0x3C (self[0xF])
    self[0xF] = &PTR_LAB_00d8313c;
    
    // Additional function pointer at offset 0x48 (self[0x12])
    self[0x12] = &PTR_LAB_00d83138;
    
    // Construct base class/subobject at offset 0x18 (self + 0x18)
    FUN_004086d0(self + 0x18);
    
    // Further initialization of that subobject
    FUN_00408310(self + 0x18);
    
    // Global initialization (likely registering with manager or setting up singleton)
    FUN_0046c640();
    
    return;
}