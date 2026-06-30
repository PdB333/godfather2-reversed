// FUNC_NAME: PacketBuffer::setBuffer
void __thiscall PacketBuffer::setBuffer(uint param_2, int param_3, uint param_4)
{
    // param_1 (this) passed to initBuffer as arg4
    // param_2: likely size in bytes (shifted right 2 to get word count)
    // param_3: pointer to external buffer structure (+0x2c stores flags/size)
    // param_4: possibly some control flags or buffer type

    // Initialize the underlying buffer (0,0,param_4,this,in_EAX)
    initBuffer(0, 0, param_4, this, in_EAX);

    // Set flags at offset 0x2c of the external buffer:
    //  - Lower 30 bits: size in words (param_2 >> 2)
    //  - Upper 2 bits: 0xC0000000 (e.g., buffer type flags, maybe RELIABLE + SEQUENCED)
    *(uint *)(param_3 + 0x2c) = (param_2 >> 2) | 0xc0000000;

    // Assert / debug check
    debugAssert();

    // Log event with code 0x2001 (likely "buffer set")
    logEvent(0x2001, param_4, 0);
}