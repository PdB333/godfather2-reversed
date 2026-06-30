// FUNC_NAME: ObjectContainer::releaseAllObjects
void __thiscall ObjectContainer::releaseAllObjects()
{
    // Clear bit 1 (0x2) of flags at +0x184
    *(uint32_t *)(this + 0x184) &= ~2;

    // Number of items in the array at +0x21c
    uint32_t itemCount = *(uint32_t *)(this + 0x220);
    if (itemCount != 0)
    {
        uint32_t i = 0;
        do
        {
            // Each element is 8 bytes; first 4 bytes are an item handle
            uint32_t itemHandle = *(uint32_t *)(*(uint32_t *)(this + 0x21c) + i * 8);
            // Release/destroy the individual item
            releaseObject(itemHandle); // Actually FUN_00558860
            i++;
        } while (i < itemCount);
    }
}