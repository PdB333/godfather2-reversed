// FUNC_NAME: ObjectArray::Reserve
// Reconstructed from 0x008d7370
// Container class for 0x2c-byte elements with dynamic array
// Offsets:
//   +0x00: int* m_pData (pointer to array of elements, each 0x2c bytes)
//   +0x04: uint m_uSize (number of elements currently stored)
//   +0x08: uint m_uCapacity (allocated capacity in elements)

void __thiscall ObjectArray::Reserve(int *this, uint newCapacity)
{
    // Allocate new buffer if current capacity is insufficient
    if ( (uint)this[2] < newCapacity )
    {
        // Allocate new memory block for newCapacity elements (each 0x2c bytes)
        undefined8 *newBuffer = (undefined8 *)operatorNew(newCapacity * 0x2c); // FUN_009c8e80

        // Copy existing elements to new buffer if there are any
        if ( this[0] != 0 )
        {
            uint copiedCount = 0;
            if ( this[1] != 0 )
            {
                int srcOffset = 0;
                undefined8 *dst = newBuffer;
                do
                {
                    // Copy 0x2c bytes (5 * 8 + 4) from source to destination
                    undefined8 *src = (undefined8 *)(this[0] + srcOffset);
                    if ( dst != (undefined8 *)0x0 )
                    {
                        *dst = *src;
                        dst[1] = src[1];
                        dst[2] = src[2];
                        dst[3] = src[3];
                        dst[4] = src[4];
                        *(undefined4 *)(dst + 5) = *(undefined4 *)(src + 5);
                    }
                    copiedCount = copiedCount + 1;
                    srcOffset = srcOffset + 0x2c;
                    dst = (undefined8 *)((int)dst + 0x2c);
                } while ( copiedCount < (uint)this[1] );
            }
            // Free old buffer
            operatorDelete(this[0]); // FUN_009c8f10
        }

        // Update data pointer and capacity
        this[0] = (int)newBuffer;
        this[2] = newCapacity;
    }
}