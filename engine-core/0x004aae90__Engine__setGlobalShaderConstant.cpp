// FUNC_NAME: Engine::setGlobalShaderConstant
void __thiscall Engine::setGlobalShaderConstant(void* pData)
{
    // Get global buffer base from TLS: FS:[0x2C] -> then dereference twice, add 8
    int** ppTlsBlock = (int**)__readfsdword(0x2C);
    int* pGlobalArray = *(int**)(*(int*)ppTlsBlock + 8);
    
    // Offset stored in this+0x18 (byte offset into the global buffer)
    int byteOffset = *(int*)((int)this + 0x18); // +0x18: byte offset for this object's data
    
    // Write 4 dwords (16 bytes) to base + 0x50 + offset
    int* pDest = (int*)((int)pGlobalArray + 0x50 + byteOffset);
    pDest[0] = ((int*)pData)[0];
    pDest[1] = ((int*)pData)[1];
    pDest[2] = ((int*)pData)[2];
    pDest[3] = ((int*)pData)[3];
    
    // Notify the engine that the shader constant block has changed
    FUN_004aa8f0();
}