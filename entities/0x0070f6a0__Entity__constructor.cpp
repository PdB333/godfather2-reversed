// FUNC_NAME: Entity::constructor
undefined4 * __thiscall Entity::constructor(undefined4 *this, undefined4 initData)
{
    // Call base class constructor
    FUN_0046c590(initData);
    
    // Set vtable pointer (offset +0x00)
    *this = &PTR_FUN_00d618a4;
    
    // Set additional function table pointers
    this[0xf] = &PTR_LAB_00d61894;   // +0x3C
    this[0x12] = &PTR_LAB_00d61890;  // +0x48
    
    // Zero out fields
    *(undefined4 *)((int)this + 0x50) = 0;          // +0x50: 4 bytes
    *(undefined2 *)((int)this + 0x54) = 0;          // +0x54: 2 bytes (short)
    *(undefined2 *)((int)this + 0x56) = 0;          // +0x56: 2 bytes (short)
    *(undefined4 *)((int)this + 0x58) = 0;          // +0x58: 4 bytes
    *(undefined4 *)((int)this + 0x5C) = 0;          // +0x5C: 4 bytes
    *(undefined4 *)((int)this + 0x60) = 0;          // +0x60: 4 bytes
    *(undefined4 *)((int)this + 0x64) = 0;          // +0x64: 4 bytes
    
    // Assign global singleton pointers
    *(undefined4 *)((int)this + 0x68) = DAT_00e446c0; // +0x68
    *(undefined4 *)((int)this + 0x6C) = DAT_00d5d740; // +0x6C
    *(undefined4 *)((int)this + 0x70) = 0;            // +0x70
    
    return this;
}