// FUNC_NAME: Utility::removeArrayElement

// Global variables for array of 8-byte elements
extern uint8_t* gArrayBase; // +0x00: pointer to array (actually DAT_01218f28)
extern uint32_t gArrayCount; // +0x00: number of elements (DAT_01218f2c)

void __fastcall removeArrayElement(uint32_t removeIndex)
{
    // Only shift if the element being removed is not the last one
    if (removeIndex < gArrayCount - 1U)
    {
        // Shift each subsequent 8-byte element down by one slot
        do
        {
            // Copy the 8-byte element at index+1 to index
            *(uint64_t*)(gArrayBase + removeIndex * 8) = *(uint64_t*)(gArrayBase + (removeIndex + 1) * 8);
            removeIndex++;
        } while (removeIndex < gArrayCount - 1U);
    }

    // Decrement the total element count
    gArrayCount--;
}