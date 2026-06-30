// Xbox PDB: EARS::Audio::PluginRegistry::PluginRegistry
// FUNC_NAME: PluginChainPool::initializePool

void __thiscall PluginChainPool::initializePool(PluginChainPool* this) {
    // +0x00: vtable pointer
    this->vtable = &PluginChainPool_vtable;
    
    // +0x04: next pool pointer
    this->nextPool = DAT_012054b8;  // link to previous head of pool list
    
    // +0x08: name string
    this->name = "PluginChainPool";
    
    // +0x18: maybe flags or size of some internal array
    this->field_0x18 = 8;
    
    // +0x20: alignment
    this->alignment = 4;
    
    // +0x0C, +0x10, +0x14: unknown zeros
    this->field_0x0C = 0;
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    
    // +0x1C: zeros
    this->field_0x1C = 0;
    this->field_0x20 = 0;
    
    // +0x2C: element size
    this->elementSize = 0x2C;
    
    // +0x28: element size (again)
    this->elementSize2 = 0x2C;
    
    // +0x24: initial count
    this->initialCount = 1;
    
    // +0x5C: another count
    this->field_0x5C = 1;
    
    // +0x3C: pointer to self (for pool list?)
    this->selfPointer = this;
    
    // +0x40: name (again)
    this->name2 = "PluginChainPool";
    
    // +0x44, +0x48, +0x4C, +0x50: zeros
    this->field_0x44 = 0;
    this->field_0x48 = 0;
    this->field_0x4C = 0;
    this->field_0x50 = 0;
    
    // +0x50: max elements for first pool
    this->maxElements = 0x1E;  // 30
    
    // +0x54: zero
    this->field_0x54 = 0;
    
    // +0x58: alignment (again)
    this->alignment2 = 4;
    
    // +0x68: zero
    this->field_0x68 = 0;
    
    // +0x6C: zero
    this->field_0x6C = 0;
    
    // +0x38: another vtable pointer
    this->vtable2 = &PluginChainPool_vtable2;
    
    // +0x64: size for second pool (?)
    this->field_0x64 = 0x50;
    this->field_0x60 = 0x50;
    
    // Update global pool list head to point to the second pool portion
    DAT_012054b8 = &this->secondPool;  // +0x70 offset
    
    // +0x74: pointer to self+0x38 (vtable2)
    this->secondPool.parentPool = &this->vtable2;
    
    // +0x94: flag
    this->secondPool.field_0x94 = 1;
    
    // +0x78: name
    this->secondPool.name = "PluginChainPool";
    
    // +0x7C, +0x80, +0x84, +0x88: zeros
    this->secondPool.field_0x7C = 0;
    this->secondPool.field_0x80 = 0;
    this->secondPool.field_0x84 = 0;
    this->secondPool.field_0x88 = 0;
    
    // +0x88: max elements for second pool
    this->secondPool.maxElements = 100;
    
    // +0x8C: zero
    this->secondPool.field_0x8C = 0;
    
    // +0x90: alignment
    this->secondPool.alignment = 4;
    
    // +0x9C: element size for second pool
    this->secondPool.elementSize = 0x30;
    
    // +0xA0: zero
    this->secondPool.field_0xA0 = 0;
    
    // +0xA4: zero
    this->secondPool.field_0xA4 = 0;
    
    // +0x98: element size again
    this->secondPool.elementSize2 = 0x30;
    
    // Set vtable for second pool
    *(int*)DAT_012054b8 = &PluginChainPool_vtable3;
    
    // +0xA8, +0xAC, +0xB0: zeros
    this->secondPool.field_0xA8 = 0;
    this->secondPool.field_0xAC = 0;
    this->secondPool.field_0xB0 = 0;
    
    // Call common pool initialization helper
    FUN_005e1730();
}