// FUNC_NAME: Array::ensureCapacity
// Function address: 0x0077b550
// EA EARS engine container: ensures capacity for an array of 8-byte elements (pairs of 32-bit values)
// Custom allocator functions: allocate (0x009c8e80) and deallocate (0x009c8f10)

class Array {
public:
    int* mData;        // +0x00: pointer to element array
    int  mSize;        // +0x04: number of elements currently stored
    int  mCapacity;    // +0x08: allocated capacity (max elements)

    void ensureCapacity(int newCapacity) {
        if (mCapacity < newCapacity) {
            int* newData = (int*)allocate(newCapacity * 8); // allocate 8 bytes per element
            if (mData != nullptr) {
                int idx = 0;
                int* dst = newData;
                if (mSize > 0) {
                    do {
                        if (dst != nullptr) {
                            int* src = mData;
                            *dst = *(src + idx * 2);
                            *(dst + 1) = *(src + 1 + idx * 2);
                        }
                        idx++;
                        dst += 2;
                    } while (idx < mSize);
                }
                deallocate(mData);
            }
            mData = newData;
            mCapacity = newCapacity;
        }
    }
};