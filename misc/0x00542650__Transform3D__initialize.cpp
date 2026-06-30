// FUNC_NAME: Transform3D::initialize

void __thiscall Transform3D::initialize(uint32_t* thisPtr, uint32_t* posVals, uint32_t* rotVals,
                                        uint32_t param4, uint32_t param5, uint32_t param6, uint32_t param7)
{
    // Clear the low byte of the third position component (offset +0x08)
    *((uint8_t*)(thisPtr + 2)) = 0;

    // Clear the handle field at offset +0x24 (index 9)
    thisPtr[9] = 0;

    // Store four extra parameters at offsets +0x34, +0x38, +0x3C, +0x40 (indices 13-16)
    thisPtr[13] = param4;
    thisPtr[14] = param5;
    thisPtr[15] = param6;
    thisPtr[16] = param7;

    // Set a type/size constant (0x3E0 = 992) at offset +0x30 (index 12)
    thisPtr[12] = 0x3E0;

    // Copy position vector (3 ints) to offsets +0x00, +0x04, +0x08
    thisPtr[0] = posVals[0];
    thisPtr[1] = posVals[1];
    thisPtr[2] = posVals[2]; // Low byte will be overwritten below
    thisPtr[3] = 0; // padding at +0x0C

    // Copy rotation/orientation vector (3 ints) to offsets +0x10, +0x14, +0x18
    thisPtr[4] = rotVals[0];
    thisPtr[5] = rotVals[1];
    thisPtr[6] = rotVals[2];
    thisPtr[7] = 0; // padding at +0x1C

    // Set the byte flag at offset +0x08 (low byte of third position component) to 1
    *((uint8_t*)(thisPtr + 2)) = 1;

    // Compute a self-relative handle with flag bit 0x40000000
    // (uintptr_t cast avoids pointer-to-integer truncation warnings)
    thisPtr[9] = ( ((uintptr_t)(thisPtr + 12) >> 2) ) | 0x40000000;
}