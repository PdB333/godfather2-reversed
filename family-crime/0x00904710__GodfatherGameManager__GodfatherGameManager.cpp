// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

undefined4* __thiscall GodfatherGameManager::GodfatherGameManager(undefined4* this, undefined4 param_2)
{
    undefined4 uVar1;
    
    // Call base class constructor or initialization function
    FUN_00901860(param_2);
    
    // Store global data pointer (DAT_00d81fec) at offset +0x230 (0x8c * 4)
    uVar1 = DAT_00d81fec;
    
    // Zero out three fields at offsets +0x234, +0x238, +0x23C
    this[0x8d] = 0;  // +0x234
    this[0x8e] = 0;  // +0x238
    this[0x8f] = 0;  // +0x23C
    
    // Set primary vtable pointer at offset 0
    *this = &PTR_FUN_00d820d0;
    
    // Set additional vtable/interface pointers at various offsets
    this[0xf]  = &PTR_LAB_00d820c0;  // +0x3C
    this[0x12] = &PTR_LAB_00d820bc;  // +0x48
    this[0x14] = &PTR_LAB_00d820b8;  // +0x50
    this[0x15] = &PTR_LAB_00d82058;  // +0x54
    this[0x16] = &PTR_LAB_00d81ff0;  // +0x58
    
    // Store global data pointer at offset +0x230
    this[0x8c] = uVar1;  // +0x230
    
    return this;
}