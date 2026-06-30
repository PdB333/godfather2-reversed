// FUNC_NAME: SetGlobalVectorAndReleaseMemory
void SetGlobalVectorAndReleaseMemory(void)
{
    // Copy 16 bytes from ESI to global vector data (likely a Vector4 or similar)
    // ESI is assumed to be pointing to a source vector
    _DAT_011f6880 = *unaff_ESI;
    uRam011f6884 = unaff_ESI[1];
    uRam011f6888 = unaff_ESI[2];
    uRam011f688c = unaff_ESI[3];

    // If the global resource manager pointer is valid, release two buffer allocations
    if (DAT_012058e8 != 0) {
        // +0x1c is a pointer to a buffer, +0x10 is its size (or identifier)
        if (*(int *)(DAT_012058e8 + 0x1c) != 0) {
            MemoryDeallocate(*(undefined4 *)(DAT_012058e8 + 0x10), *(int *)(DAT_012058e8 + 0x1c));
        }
        // +0x6c is another buffer pointer, +0x14 is its size (or identifier)
        if (*(int *)(DAT_012058e8 + 0x6c) != 0) {
            MemoryDeallocate(*(undefined4 *)(DAT_012058e8 + 0x14), *(int *)(DAT_012058e8 + 0x6c));
        }
    }
}