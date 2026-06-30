// FUNC_NAME: setObjectFields
void __thiscall setObjectFields(void* this, const int64_t* largeData, const int32_t* extraData)
{
    // Copy 8 bytes from largeData to offset 0x5c
    *(int64_t*)((uint8_t*)this + 0x5c) = *largeData;

    // Copy 4 bytes from offset 8 of largeData to offset 0x64 (100 decimal)
    *(int32_t*)((uint8_t*)this + 100) = *(const int32_t*)((const uint8_t*)largeData + 8);

    // Copy 4 bytes from extraData to offset 0x68
    *(int32_t*)((uint8_t*)this + 0x68) = *extraData;
}