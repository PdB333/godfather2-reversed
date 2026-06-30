// FUNC_NAME: Container::clearElements
void Container::clearElements(int byteOffset, int elementIndex, size_t elementSize, int count)
{
    // +0x04: stride (int) – size of each element in the container
    // +0x0C: dataPtr (int) – base address of the data array
    void *dst = (void *)(*(int *)(this + 4) * elementIndex + *(int *)(this + 0xC) + byteOffset);
    if (count > 0)
    {
        do
        {
            memset(dst, 0, elementSize);
            dst = (void *)((int)dst + *(int *)(this + 4));
            count--;
        } while (count != 0);
    }
}