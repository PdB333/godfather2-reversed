// FUNC_NAME: ArgumentReader::invokeCallback
void __thiscall ArgumentReader::invokeCallback(void* thisPtr, void (**callbackPtr)(uint32_t, uint32_t, uint32_t, uint32_t, uint8_t, uint32_t))
{
    // thisPtr + 0x18 holds current read pointer (adjusted to align to 4 bytes)
    uint8_t* currentReadPos = *(uint8_t**)((int)thisPtr + 0x18);
    uint8_t* alignedData = (uint8_t*)((uint32_t)currentReadPos & 0xFFFFFFFC); // align down to 4 bytes

    // Update the read pointer after alignment
    *(uint8_t**)((int)thisPtr + 0x18) = alignedData;

    // Read 12 bytes from the aligned buffer: two 64-bit values and one 32-bit value
    uint64_t arg1 = *(uint64_t*)alignedData;                    // offset 0..7
    uint64_t arg2 = *(uint64_t*)(alignedData + 8);              // offset 8..15
    uint32_t arg3 = *(uint32_t*)(alignedData + 16);             // offset 16..19

    // Advance the stored pointer by 20 bytes (total read size)
    *(int*)((int)thisPtr + 0x18) = (int)(alignedData + 0x14);

    // Compute temporary stack pointer: align (alignedData + 0x23) to 16 bytes, then add 0x40 (64 bytes)
    uint32_t tmpStackTop = ((uint32_t)alignedData + 0x23) & 0xFFFFFFF0;
    *(uint32_t*)((int)thisPtr + 0x18) = tmpStackTop + 0x40;   // store as new read pointer? Possibly reused.

    // Split the 64-bit arguments into high/low parts
    uint32_t arg1_low  = (uint32_t)(arg1 & 0xFFFFFFFF);
    uint32_t arg1_high = (uint32_t)(arg1 >> 32);
    uint32_t arg2_low  = (uint32_t)(arg2 & 0xFFFFFFFF);
    uint32_t arg2_high = (uint32_t)(arg2 >> 32);
    uint8_t  arg3_byte = (uint8_t)(arg3 & 0xFF);               // only the low byte used

    // Call the callback via the double function pointer
    (*(*callbackPtr))(arg1_low, arg1_high, arg2_low, arg2_high, arg3_byte, tmpStackTop);
}
```