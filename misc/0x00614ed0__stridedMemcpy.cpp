// FUNC_NAME: stridedMemcpy
// Address: 0x00614ed0
// Role: Strided memory copy utility. Copies 'count' elements of size 'elemSize' from source to destination,
// advancing source pointer by srcStride and dest pointer by destStride each iteration.
// Optimized to a single memcpy when all strides equal element size.

void __cdecl stridedMemcpy(void *dst, const void *src, size_t dstStride, size_t srcStride, size_t elemSize, size_t count)
{
    if (dstStride == srcStride && dstStride == elemSize) {
        memcpy(dst, src, elemSize * count);
        return;
    }
    while (count--) {
        memcpy(dst, src, elemSize);
        dst = (char*)dst + dstStride;
        src = (const char*)src + srcStride;
    }
}