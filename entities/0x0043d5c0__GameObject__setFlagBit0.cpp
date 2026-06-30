// FUNC_NAME: GameObject::setFlagBit0
void __thiscall GameObject::setFlagBit0(void* thisPtr, bool enable)
{
    // Sets or clears bit 0 of the flags field at offset +0x04
    uint32_t* flags = (uint32_t*)((char*)thisPtr + 4);
    if (enable)
    {
        *flags |= 1;         // Set bit 0
    }
    else
    {
        *flags &= ~1;        // Clear bit 0
    }
}