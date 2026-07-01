// FUNC_NAME: SomeClass::SomeClass

void * __thiscall SomeClass::SomeClass(SomeClass *this, uint32_t param)
{
    // Call base class constructor (likely)
    FUN_0046c590(param);
    
    // Initialize vtable pointer at offset 0x00
    this->vtable = &PTR_FUN_00d7bee8;
    
    // Set function table pointers
    // +0x3C: pointer to data table
    this->table1 = (uint32_t *)&PTR_LAB_00d7bed8;
    // +0x48: pointer to another table
    this->table2 = (uint32_t *)&PTR_LAB_00d7bed4;
    
    // Zero out fields from 0x50 to 0x7C
    // +0x50: 4-byte field
    this->field_0x50 = 0;
    
    // +0x58: 2-byte field
    *(uint16_t *)((uint8_t *)this + 0x58) = 0;
    // +0x5A: 2-byte field
    *(uint16_t *)((uint8_t *)this + 0x5A) = 0;
    
    // +0x5C: 4-byte field
    this->field_0x5C = 0;
    
    // +0x60: 2-byte field
    *(uint16_t *)((uint8_t *)this + 0x60) = 0;
    // +0x62: 2-byte field
    *(uint16_t *)((uint8_t *)this + 0x62) = 0;
    
    // +0x64: 4-byte field
    this->field_0x64 = 0;
    
    // +0x68: 2-byte field
    *(uint16_t *)((uint8_t *)this + 0x68) = 0;
    // +0x6A: 2-byte field
    *(uint16_t *)((uint8_t *)this + 0x6A) = 0;
    
    // +0x6C: 4-byte field
    this->field_0x6C = 0;
    
    // +0x70, 0x74, 0x78, 0x7C: 4-byte fields
    this->field_0x70 = 0;
    this->field_0x74 = 0;
    this->field_0x78 = 0;
    this->field_0x7C = 0;
    
    return this;
}