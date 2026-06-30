// FUNC_NAME: copyMatrixToThreadLocal
void __fastcall copyMatrixToThreadLocal(float* srcMatrix, int slotIndex)
{
    // slotIndex must be non-zero; zero means no-op
    if (slotIndex == 0) {
        return;
    }

    // Access thread-local storage (TLS) via FS segment
    // FS:[0x2c] points to the TLS array (pointer to pointer)
    // Dereference that to get the TLS base, then add 8 to get a pointer to the actual data area
    // Then add an offset derived from slotIndex+0x18 to get the destination address
    float* destMatrix = (float*)(*(int*)(*(int*)(__readfsdword(0x2c)) + 8) + *(int*)(slotIndex + 0x18));

    // Copy 16 floats (64 bytes) – a 4x4 matrix
    destMatrix[0]  = srcMatrix[0];
    destMatrix[1]  = srcMatrix[1];
    destMatrix[2]  = srcMatrix[2];
    destMatrix[3]  = srcMatrix[3];
    destMatrix[4]  = srcMatrix[4];
    destMatrix[5]  = srcMatrix[5];
    destMatrix[6]  = srcMatrix[6];
    destMatrix[7]  = srcMatrix[7];
    destMatrix[8]  = srcMatrix[8];
    destMatrix[9]  = srcMatrix[9];
    destMatrix[10] = srcMatrix[10];
    destMatrix[11] = srcMatrix[11];
    destMatrix[12] = srcMatrix[12];
    destMatrix[13] = srcMatrix[13];
    destMatrix[14] = srcMatrix[14];
    destMatrix[15] = srcMatrix[15];
}