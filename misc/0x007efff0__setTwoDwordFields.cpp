// FUNC_NAME: setTwoDwordFields
void __thiscall setTwoDwordFields(void* this, uint32_t value1, uint32_t value2)
{
    // Store first value at offset +0xD4
    *(uint32_t*)((uint8_t*)this + 0xD4) = value1;
    // Store second value at offset +0xD8
    *(uint32_t*)((uint8_t*)this + 0xD8) = value2;
}