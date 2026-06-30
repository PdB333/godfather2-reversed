// FUNC_NAME: BufferHolder::Release
// Function at 0x006a8710
// Releases an internal buffer and resets state while preserving a flags byte.

void __thiscall BufferHolder::Release(void)
{
    byte savedFlags; // +0x10

    // If a global shared buffer pool exists, copy from it (this appears to be a memory copy operation)
    if (DAT_012069c4 != 0) {
        MemoryCopy((void *)this, &DAT_012069c4, 0x8000);
    }

    savedFlags = *(byte *)((int)this + 0x10); // Save the flags field

    // Free the dynamically allocated buffer at offset +0x14
    if (*(int *)((int)this + 0x14) != 0) {
        MemoryFree((void **)((int)this + 0x14));
        *(int *)((int)this + 0x14) = 0;
    }

    *(int *)((int)this + 0x1C) = 0;          // Reset size or counter field at +0x1C
    *(byte *)((int)this + 0x10) = savedFlags; // Restore the saved flags
    *(byte *)((int)this + 0x20) = 0;          // Clear another flag at +0x20
}