// FUNC_NAME: NPCDialogManager::NPCDialogManager
undefined4* __thiscall NPCDialogManager::NPCDialogManager(undefined4* this, undefined4 unknownParam)
{
    undefined4 uVar1;
    
    // Call base class constructor (likely EARS::Framework::Object or similar)
    FUN_00473d90(unknownParam);
    
    // Set up vtable pointer (offsets: +0x00)
    uVar1 = DAT_00d5e288; // Some global pointer
    *this = &PTR_FUN_00d5f590; // VTable assignment
    
    // Initialize member pointers at various offsets
    this[0xf] = &PTR_LAB_00d5f580;  // +0x3C
    this[0x12] = &PTR_LAB_00d5f57c; // +0x48
    this[0x14] = &PTR_LAB_00d5f578; // +0x50
    this[0x18] = uVar1;             // +0x60
    this[0x19] = _DAT_00d5780c;     // +0x64
    uVar1 = _DAT_00d5cf70;          // +0x68
    this[0x1a] = _DAT_00d5cf70;     // +0x68
    this[0x1b] = uVar1;             // +0x6C
    
    // Zero-initialize remaining fields
    this[0x1f] = 0; // +0x7C
    this[0x1e] = 0; // +0x78
    this[0x1d] = 0; // +0x74
    this[0x1c] = 0; // +0x70
    this[0x20] = 0; // +0x80
    
    return this;
}