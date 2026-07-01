// FUNC_NAME: Array::reserve
// Address: 0x00812790
// Role: Resizes internal buffer to accommodate at least 'newCapacity' elements (each 16 bytes). Copies existing elements, frees old buffer.

class Array {
public:
    // +0x00: pointer to element data (each element 16 bytes)
    void* mData;
    // +0x04: number of elements currently stored
    uint32_t mSize;
    // +0x08: allocated capacity (max elements)
    uint32_t mCapacity;

    void reserve(uint32_t newCapacity) {
        if (mCapacity < newCapacity) {
            // Allocate new buffer: newCapacity * sizeof(Element) (16 bytes)
            void* newData = operator new(newCapacity << 4); // FUN_009c8e80

            if (mData != nullptr) {
                uint32_t i = 0;
                if (mSize != 0) {
                    // Copy each element (16 bytes = 4 uint32_t)
                    uint32_t* src = static_cast<uint32_t*>(mData);
                    uint32_t* dst = static_cast<uint32_t*>(newData);
                    do {
                        dst[0] = src[0];
                        dst[1] = src[1];
                        dst[2] = src[2];
                        dst[3] = src[3];
                        src += 4;
                        dst += 4;
                        i++;
                    } while (i < mSize);
                }
                operator delete(mData); // FUN_009c8f10
            }

            mData = newData;
            mCapacity = newCapacity;
        }
    }
};