// FUNC_NAME: stridedCopy
// Address: 0x00614ed0
// Role: Copies data from source to destination with possibly different strides per element.
// Parameters:
//   src - source pointer (this in __thiscall)
//   dst - destination pointer
//   dstStride - stride between destination elements
//   srcStride - stride between source elements
//   elementSize - size of each element to copy
//   count - number of elements (passed in EAX in original assembly)
void __thiscall stridedCopy(void* src, void* dst, size_t dstStride, size_t srcStride, size_t elementSize, int count) {
    size_t srcStrideOrig = srcStride; // preserve original source stride for advancing
    // If all strides equal element size, it's a contiguous block
    if (dstStride == srcStride && dstStride == elementSize) {
        memcpy(dst, src, srcStride * count);
        return;
    }
    // Otherwise, copy each element with separate strides
    int remaining = count;
    if (remaining != 0) {
        do {
            memcpy(dst, src, elementSize);
            src = (void*)((int)src + srcStrideOrig);
            dst = (void*)((int)dst + dstStride);
            remaining--;
        } while (remaining != 0);
    }
}