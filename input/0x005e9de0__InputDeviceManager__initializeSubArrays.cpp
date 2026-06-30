// FUNC_NAME: InputDeviceManager::initializeSubArrays
// 0x005e9de0 - Initializes 4 sub-arrays each with capacity 16, for game input states
// Each sub-array is 0x30 bytes (12 uint32_t) with dynamic allocation for ints.
__thiscall InputDeviceManager* InputDeviceManager::initializeSubArrays(InputDeviceManager* this)
{
    // Zero out first 5 fields (offsets 0x00 through 0x10)
    this->field_0x00 = 0;
    this->field_0x04 = 0;
    this->field_0x08 = 0;
    this->field_0x0C = 0;
    this->field_0x10 = 0;

    // Pointer to the first sub-array (offset +0x14)
    uint32_t* subBase = reinterpret_cast<uint32_t*>(&this->subArray[0]);

    for (int i = 0; i < 4; i++)
    {
        // Zero 11 of 12 words in the sub‑array block (indices 0-9 and 11, skipping 10)
        subBase[0] = 0;   // +0x00: unknown
        subBase[1] = 0;   // +0x04: unknown
        subBase[2] = 0;   // +0x08: data pointer
        subBase[3] = 0;   // +0x0C: element count
        subBase[4] = 0;   // +0x10: capacity
        subBase[5] = 0;   // +0x14
        subBase[6] = 0;   // +0x18
        subBase[7] = 0;   // +0x1C
        subBase[8] = 0;   // +0x20
        subBase[9] = 0;   // +0x24
        subBase[11] = 0;  // +0x2C (skipping +0x28, likely padding)

        // Update internal state (e.g., tick counter)
        someUpdateFunction(); // FUN_005ef9a0

        // Reallocate if capacity is less than 16 (0x10)
        if (subBase[4] < 16)
        {
            int* newBuffer = (int*)allocateMemory(0x40); // allocate 64 bytes (16 ints)

            // Copy existing data if present
            if (subBase[2] != 0)
            {
                uint32_t count = subBase[3];
                if (count != 0)
                {
                    int* src = reinterpret_cast<int*>(subBase[2]);
                    int* dst = newBuffer;
                    for (uint32_t j = 0; j < count; j++)
                    {
                        if (dst != nullptr)
                        {
                            *dst = *src;
                        }
                        src++;
                        dst++;
                    }
                }
                // Free the old buffer
                freeMemory(reinterpret_cast<void*>(subBase[2]));
            }

            // Store new pointer and set capacity to 16
            subBase[2] = reinterpret_cast<uint32_t>(newBuffer);
            subBase[4] = 16;
        }

        // Move to the next sub-array (12 uint32_t = 0x30 bytes)
        subBase += 12;
    }

    return this;
}