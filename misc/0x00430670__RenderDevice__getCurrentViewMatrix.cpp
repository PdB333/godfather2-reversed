// FUNC_NAME: RenderDevice::getCurrentViewMatrix
void __fastcall getCurrentViewMatrix(float *outMatrix)
{
    // FS segment: TLS pointer at offset 0x2c (Thread Local Storage)
    // Dereference twice to get thread-specific data, then offset 0x24 to access the render context
    int tlsBase = *(int *)(*(int *)(__readfsdword(0x2c)) + 0x24);
    
    // Read 16 floats (4x4 matrix) from tlsBase+0x40 to tlsBase+0x7C
    outMatrix[0]  = *(float *)(tlsBase + 0x40);
    outMatrix[1]  = *(float *)(tlsBase + 0x44);
    outMatrix[2]  = *(float *)(tlsBase + 0x48);
    outMatrix[3]  = *(float *)(tlsBase + 0x4c);
    
    outMatrix[4]  = *(float *)(tlsBase + 0x50);
    outMatrix[5]  = *(float *)(tlsBase + 0x54);
    outMatrix[6]  = *(float *)(tlsBase + 0x58);
    outMatrix[7]  = *(float *)(tlsBase + 0x5c);
    
    outMatrix[8]  = *(float *)(tlsBase + 0x60);
    outMatrix[9]  = *(float *)(tlsBase + 0x64);
    outMatrix[10] = *(float *)(tlsBase + 0x68);
    outMatrix[11] = *(float *)(tlsBase + 0x6c);
    
    outMatrix[12] = *(float *)(tlsBase + 0x70);
    outMatrix[13] = *(float *)(tlsBase + 0x74);
    outMatrix[14] = *(float *)(tlsBase + 0x78);
    outMatrix[15] = *(float *)(tlsBase + 0x7c);
}