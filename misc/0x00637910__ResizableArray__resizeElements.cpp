// FUNC_NAME: ResizableArray::resizeElements
void ResizableArray::resizeElements(int newCount)
{
    // +0x1c: current element count (int)
    // +0x0c: pointer to data array (each element 8 bytes)
    int oldCount = *(int *)(this + 0x1c);
    
    // Allocate new buffer (likely via internal allocator which may free old buffer)
    int* newBuffer = FUN_006279a0(oldCount * 8, newCount * 8);
    *(int **)(this + 0xc) = newBuffer;
    
    // Zero only the first 4 bytes of newly added elements
    for (int i = oldCount; i < newCount; ++i)
    {
        *(int *)(newBuffer + i * 2) = 0; // each element is 2 ints (8 bytes)
    }
    
    *(int *)(this + 0x1c) = newCount;
}