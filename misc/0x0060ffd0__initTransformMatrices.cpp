// FUNC_NAME: initTransformMatrices

// Initializes a transform structure containing two 4x4 matrices and 4 extra floats.
// Global DAT_00e2b1a4 provides the diagonal scaling value (likely 1.0f for identity).
void __fastcall initTransformMatrices(undefined4 *thisPointer)
{
    // +0x00: first 4x4 identity matrix (rows: indices 0,1,2,3; 4,5,6,7; 8,9,10,11; 12,13,14,15)
    // +0x40: second 4x4 identity matrix (indices 16-31)
    // +0x80: extra 4 floats (indices 32-35), set to zero
    undefined4 uVar1 = DAT_00e2b1a4;

    thisPointer[0x00] = uVar1;
    thisPointer[0x01] = 0;
    thisPointer[0x02] = 0;
    thisPointer[0x03] = 0;
    thisPointer[0x04] = 0;
    thisPointer[0x05] = uVar1;
    thisPointer[0x06] = 0;
    thisPointer[0x07] = 0;
    thisPointer[0x08] = 0;
    thisPointer[0x09] = 0;
    thisPointer[0x0A] = uVar1;
    thisPointer[0x0B] = 0;
    thisPointer[0x0C] = 0;
    thisPointer[0x0D] = 0;
    thisPointer[0x0E] = 0;
    thisPointer[0x0F] = uVar1;

    thisPointer[0x10] = uVar1;
    thisPointer[0x11] = 0;
    thisPointer[0x12] = 0;
    thisPointer[0x13] = 0;
    thisPointer[0x14] = 0;
    thisPointer[0x15] = uVar1;
    thisPointer[0x16] = 0;
    thisPointer[0x17] = 0;
    thisPointer[0x18] = 0;
    thisPointer[0x19] = 0;
    thisPointer[0x1A] = uVar1;
    thisPointer[0x1B] = 0;
    thisPointer[0x1C] = 0;
    thisPointer[0x1D] = 0;
    thisPointer[0x1E] = 0;
    thisPointer[0x1F] = uVar1;

    thisPointer[0x20] = 0;
    thisPointer[0x21] = 0;
    thisPointer[0x22] = 0;
    thisPointer[0x23] = 0;
}