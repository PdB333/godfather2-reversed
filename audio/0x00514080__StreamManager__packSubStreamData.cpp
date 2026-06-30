// FUNC_NAME: StreamManager::packSubStreamData
void __thiscall StreamManager::packSubStreamData(void *this, undefined4 param_1, void *data, int elementCount, int elementStride)
{
    void *dst;
    int unaff_ESI;
    
    // Dereference and increment the output pointer (this + 0x14 is the current write position)
    **(undefined4 **)(unaff_ESI + 0x14) = param_1;
    *(int *)(unaff_ESI + 0x14) = *(int *)(unaff_ESI + 0x14) + 4;
    
    // Write element count
    **(int **)(unaff_ESI + 0x14) = elementCount;
    *(int *)(unaff_ESI + 0x14) = *(int *)(unaff_ESI + 0x14) + 4;
    
    // Write element stride (size per element)
    **(int **)(unaff_ESI + 0x14) = elementStride;
    
    // Align destination pointer to elementStride boundary
    dst = (void *)(~(elementStride - 1U) & elementStride + 3 + *(int *)(unaff_ESI + 0x14));
    *(void **)(unaff_ESI + 0x14) = dst;
    
    // Copy the data (elementCount * 8 bytes per element? typically 2 ints per element)
    _memcpy(dst, data, elementCount * 8);
    *(int *)(unaff_ESI + 0x14) = *(int *)(unaff_ESI + 0x14) + elementCount * 8;
    
    return;
}