// FUNC_NAME: copyMatrix16ToThreadLocalSlot
void __fastcall copyMatrix16ToThreadLocalSlot(float* srcMatrix, void* object) {
    // object is a pointer to a game object with offset 0x18 storing an index/offset into a per-thread matrix buffer
    if (object == 0) {
        return;
    }
    // Compute destination: TLS base (FS:0x2c -> __tls_array) dereferenced twice, add 8, then add object->field_0x18
    float* destMatrix = (float*)(*(int*)(**(int**)(__readfsdword(0x2c) + 8) + *(int*)((char*)object + 0x18)));
    // Copy 16 floats (4x4 world transform matrix)
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