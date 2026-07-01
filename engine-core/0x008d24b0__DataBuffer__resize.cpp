// FUNC_NAME: DataBuffer::resize
void __thiscall DataBuffer::resize(uint newSize)
{
    // +0x4: current size (uint)
    uint* size = (uint*)((int)this + 4);
    if (*size < newSize) {
        // Grow: reallocate underlying storage to accommodate new size
        FUN_008d2380(newSize);
        *size = newSize;
        return;
    }
    if (newSize < *size) {
        // Shrink: only update size, no deallocation
        *size = newSize;
    }
}