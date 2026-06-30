// FUNC_NAME: getObjectData
void SomeClass::getObjectData(void)
{
    // this pointer in in_EAX (ECX)
    int* thisPtr;  // in_EAX
    undefined4 buffer[3]; // 12-byte buffer
    
    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    
    // Call virtual function at offset 0x10 (vtable entry) 
    // with parameter: count (offset 0x20) * 12 (size per element)
    // and pointer to 12-byte output buffer
    (**(code **)(*(void***)thisPtr + 4))( // offset 0x10 -> vtable slot index? Actually indirect
        *(int*)((char*)thisPtr + 0x20) * 0xc,
        buffer
    );
    return;
}