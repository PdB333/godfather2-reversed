// FUNC_NAME: DataArray::reserve
void __thiscall DataArray::reserve(uint newCapacity)
{
    // struct DataArray { int* data; uint count; uint capacity; } // +0x00, +0x04, +0x08
    if (this->capacity < newCapacity)
    {
        // Allocate new block of 12-byte elements
        int* newData = reinterpret_cast<int*>(FUN_009c8e80(newCapacity * 12));
        if (this->data != 0)
        {
            uint idx = 0;
            if (this->count != 0)
            {
                int srcOffset = 0;
                int* dst = newData;
                do
                {
                    int* src = this->data + srcOffset; // offset in int* steps (4 bytes)
                    // Copy 12 bytes: 8 bytes (two ints) + 4 bytes
                    reinterpret_cast<undefined8*>(dst) = reinterpret_cast<undefined8*>(src);
                    reinterpret_cast<undefined4*>(reinterpret_cast<int>(dst) + 8) =
                        reinterpret_cast<undefined4*>(reinterpret_cast<int>(src) + 8);
                    idx++;
                    srcOffset += 3;  // 12 bytes = 3 ints
                    dst += 3;       // advance by 3 ints
                } while (idx < this->count);
            }
            // Free old buffer
            FUN_009c8f10(this->data);
        }
        // Update container
        this->data = newData;
        this->capacity = newCapacity;
    }
}