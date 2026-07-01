// FUNC_NAME: Presentation::pushTextureHandle
// Function address: 0x007cfdd0
// Role: Two-slot queue push. Stores a resource handle (e.g., texture/sound ID) into a rotating buffer of size 2.
// Respects a global lock flag at ( *(this+0x58) ) +0x8e8 bit 0.
// Offsets: this+0x58 -> pointer to some manager/data; this+0xa4 = slot1; this+0xa8 = slot2.

void __thiscall Presentation::pushTextureHandle(uint handle)
{
    // Check global lock: if bit 0 of byte at (*(this+0x58)) + 0x8e8 is set, ignore
    if ((*(byte *)(*(int *)((char *)this + 0x58) + 0x8e8) & 1) == 0)
    {
        uint *slot1 = (uint *)((char *)this + 0xa4);
        uint *slot2 = (uint *)((char *)this + 0xa8);

        if (*slot1 == 0)
        {
            // First slot empty – store here
            *slot1 = handle;
        }
        else if (*slot2 == 0)
        {
            // Second slot empty – store here
            *slot2 = handle;
        }
        else
        {
            // Both slots full – evict oldest, shift slot2 into slot1, store new handle in slot2
            *slot1 = *slot2;
            *slot2 = handle;
        }
    }
}