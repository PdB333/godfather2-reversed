// FUNC_NAME: FillMemoryPattern
// Address: 0x00614f30
// Role: Pattern fill memory function - fills a buffer with a repeated pattern, supporting stride between blocks.
// Note: pattern byte was originally passed in EAX register

void __cdecl FillMemoryPattern(size_t stride, void* dest, int count, size_t blockSize, uint8_t pattern)
{
    if (stride != blockSize) {
        if (count != 0) {
            do {
                memset(dest, pattern, blockSize);
                dest = reinterpret_cast<void*>(reinterpret_cast<intptr_t>(dest) + stride);
                count--;
            } while (count != 0);
        }
        return;
    }
    memset(dest, pattern, stride * count);
}