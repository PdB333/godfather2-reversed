// FUNC_NAME: RandomNumberGenerator::generate64Bit

void RandomNumberGenerator::generate64Bit(void)
{
    // Local storage for 64-bit value returned by FUN_0064b9e0
    uint lowPart;                                  // +0x00
    uint highPart;                                 // +0x04

    // Call helper to generate a 64-bit random value (size hint 0x40 = 64)
    FUN_0064b9e0(0x40, &lowPart);

    // Store result into this object's 64-bit field
    *ESI = lowPart;
    ESI[1] = highPart;
}