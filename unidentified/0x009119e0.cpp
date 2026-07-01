// Address: 0x009119e0 - Generic setter for boolean flag at offset 0x50
void __fastcall Entity::setEnabled(void* thisPtr)
{
    // Set the byte at +0x50 to 1 (enable flag)
    *(uint8_t*)((uintptr_t)thisPtr + 0x50) = 1;
}