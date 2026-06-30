// FUN_004a57f0: SomeClass::hasAnyActiveObject
bool __thiscall SomeClass::hasAnyActiveObject(void)
{
    // Check first array: 8-byte structs, flags at offset +0x4 (bit 0x200 = connected/enabled)
    uint32_t count1 = *(uint32_t *)(this + 0x78);
    if (count1 != 0)
    {
        uint16_t *flagsPtr = (uint16_t *)(*(uint32_t *)(this + 0x74) + 4);
        for (uint32_t i = 0; i < count1; i++)
        {
            if (*flagsPtr & 0x200)
                return true;
            flagsPtr += 4; // advance 8 bytes (4 ushorts)
        }
    }

    // Check second array: 16-byte structs, flags at offset +0x4 (same flag)
    uint32_t count2 = *(uint32_t *)(this + 0x6C);
    if (count2 != 0)
    {
        uint16_t *flagsPtr = (uint16_t *)(*(uint32_t *)(this + 0x68) + 4);
        for (uint32_t i = 0; i < count2; i++)
        {
            if (*flagsPtr & 0x200)
                return true;
            flagsPtr += 8; // advance 16 bytes (8 ushorts)
        }
    }

    // Check third array: array of object pointers; each object has a virtual method at vtable+0x14
    uint32_t count3 = *(uint32_t *)(this + 0x60);
    if (count3 != 0)
    {
        uint32_t **objectArray = *(uint32_t ***)(this + 0x5C);
        for (uint32_t i = 0; i < count3; i++)
        {
            uint32_t *obj = objectArray[i];
            if (obj != nullptr)
            {
                // Call virtual function at vtable offset 0x14 (5th function)
                bool (*checkActive)(void *) = (bool (*)(void *))(*((uint32_t **)*obj + 5));
                if (checkActive(obj))
                    return true;
            }
        }
    }

    return false;
}