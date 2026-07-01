// FUNC_NAME: RefCounted::releaseReference
// Address: 0x008fe120
// Description: Releases a reference on the object if a certain flag is set.
// The flag at offset +0x80 (bit 1) indicates whether the object is still referenced.
// The reference count at offset +0x84 is decremented after clearing the flag.

void __thiscall RefCounted::releaseReference(void)
{
    // Check if bit 1 of the flags word at +0x80 is set.
    if ((*(byte *)(this + 0x80) >> 1) & 1)
    {
        // Clear that bit in the ushort at +0x80.
        *(ushort *)(this + 0x80) &= 0xfffd;

        // Notify some global resource manager (DAT_012069c4) about the release.
        g_resourceManager->notifyRelease();

        // Decrement the reference count at +0x84.
        *(int *)(this + 0x84) -= 1;
    }
    return;
}