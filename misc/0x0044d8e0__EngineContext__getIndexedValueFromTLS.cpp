// FUNC_NAME: EngineContext::getIndexedValueFromTLS
int __thiscall EngineContext::getIndexedValueFromTLS() {
    // TLS access via FS:[0x2C] (pointer to per-thread TLS array)
    int* tlsArray = *(int**)__readfsdword(0x2C);
    // First TLS slot holds a pointer to a per-thread structure
    int* perThreadStruct = (int*)*tlsArray;
    // Read first dword of that structure (likely a base pointer)
    int base = *perThreadStruct;
    // Read pointer at offset +0x08 within the same structure
    int* tablePtr = (int*)*(int*)(base + 8);
    // Index from this object at offset +0x18
    int index = *(int*)((char*)this + 0x18);
    // Final address: table pointer + 0x80 + index (in bytes)
    return *(int*)((char*)tablePtr + 0x80 + index);
}