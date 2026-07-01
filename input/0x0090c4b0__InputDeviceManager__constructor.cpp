// FUNC_NAME: InputDeviceManager::constructor
InputDeviceManager* __thiscall InputDeviceManager::constructor(InputDeviceManager* this)
{
    // +0x00: vtable pointer (set to &PTR_FUN_00d833e0)
    // +0x04: unknown field (set to 1)
    // +0x08: unknown field (set to 0)
    // +0x0C: pointer to label (set twice, possibly base/derived vtable or other)
    // +0x10: unknown (0)
    // +0x14: unknown (0)
    // +0x18: unknown (0)
    // +0x1C: unknown (0xFFFFFFFF)
    // +0x20: unknown (0)
    
    this->field_0x04 = 1;
    this->field_0x08 = 0;
    this->field_0x0C = &PTR_LAB_00d833d8;  // initial pointer
    g_inputDeviceManager = this;           // DAT_011298f8 stores singleton
    this->vtable = &PTR_FUN_00d833e0;      // set vtable
    this->field_0x0C = &PTR_LAB_00d833dc;  // overwritten (chain setup?)
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1C = 0xFFFFFFFF;
    this->field_0x20 = 0;
    
    // Call initialization routine with arguments (this, 2, 2)
    FUN_0068dc50(&this, 2, 2);
    
    return this;
}