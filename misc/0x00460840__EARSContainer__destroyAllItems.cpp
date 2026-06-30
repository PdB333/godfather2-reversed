// FUNC_NAME: EARSContainer::destroyAllItems

void __thiscall EARSContainer::destroyAllItems(void)
{
    // Set the "destroying" flag (bit 1) at offset +0x184
    *(uint32_t *)((uint8_t *)this + 0x184) |= 2;
    
    uint32_t count = *(uint32_t *)((uint8_t *)this + 0x220);  // +0x220: number of elements
    if (count != 0)
    {
        // +0x21c: pointer to an array of 8-byte entries (each is likely a handle + pointer)
        uint32_t *arrayBase = *(uint32_t **)((uint8_t *)this + 0x21c);
        for (uint32_t i = 0; i < count; i++)
        {
            // Each entry is 8 bytes; first 4 bytes are a pointer to the item.
            uint32_t itemPtr = arrayBase[i * 2];
            destroyItem(itemPtr);  // FUN_00558770: release/delete the item
        }
    }
}