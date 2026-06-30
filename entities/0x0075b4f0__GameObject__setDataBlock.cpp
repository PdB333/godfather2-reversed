// FUNC_NAME: GameObject::setDataBlock
void __thiscall GameObject::setDataBlock(int thisObj, uint64_t* inputData)
{
    // Set flag bit 2 at offset 0x80 to mark this data as present
    *(uint32_t*)(thisObj + 0x80) |= 4;

    // Copy first 8 bytes (probably a pointer or 64-bit ID) to offset 0x8c
    *(uint64_t*)(thisObj + 0x8c) = *inputData;

    // Copy next 4 bytes (additional integer) to offset 0x94
    *(uint32_t*)(thisObj + 0x94) = *(uint32_t*)((uint8_t*)inputData + 8);
}