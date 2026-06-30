// FUNC_NAME: Mat4x4::setTranslation
void __thiscall Mat4x4::setTranslation(Mat4x4* this, const float* translationVec) {
    // Fetch thread-local data pointer (FS:[0x2D] + 8) - likely a per-thread scratch buffer
    // This function copies the first 48 bytes of the matrix (identity/rotation/scale) 
    // from itself, and writes the last 16 bytes from the provided translation vector.
    
    // +0x18 is the offset into a per-thread buffer (stored in this object)
    int bufferOffset = *(int*)((char*)this + 0x18);
    int* basePtr = (int*)(getTLSBuffer() + bufferOffset);
    
    // Read and preserve the first 12 floats (positions 0–44) of the matrix
    int a0 = basePtr[0];
    int a1 = basePtr[1];
    int a2 = basePtr[2];
    int a3 = basePtr[3];
    int a4 = basePtr[4];
    int a5 = basePtr[5];
    int a6 = basePtr[6];
    int a7 = basePtr[7];
    int a8 = basePtr[8];
    int a9 = basePtr[9];
    int a10 = basePtr[10];
    int a11 = basePtr[11];
    
    // Read the 4 floats from the translation vector (parameter)
    int t0 = *(int*)&translationVec[0];
    int t1 = *(int*)&translationVec[1];
    int t2 = *(int*)&translationVec[2];
    int t3 = *(int*)&translationVec[3];
    
    // Write back the entire 64-byte matrix: first 48 bytes from original, then translation
    basePtr[0]  = a0;
    basePtr[1]  = a1;
    basePtr[2]  = a2;
    basePtr[3]  = a3;
    basePtr[4]  = a4;
    basePtr[5]  = a5;
    basePtr[6]  = a6;
    basePtr[7]  = a7;
    basePtr[8]  = a8;
    basePtr[9]  = a9;
    basePtr[10] = a10;
    basePtr[11] = a11;
    basePtr[12] = t0;
    basePtr[13] = t1;
    basePtr[14] = t2;
    basePtr[15] = t3;
}