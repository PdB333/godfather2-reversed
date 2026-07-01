//FUNC_NAME: SomeClass::initializeData
void __thiscall SomeClass::initializeData(void* this, void* pData) {
    // Copy 32-byte data block from pData into member at offset 0x10
    // FUN_004a9cd0 is likely a memcpy or copy constructor for a 32-byte structure
    FUN_004a9cd0(pData, (void*)((int)this + 0x10));
    
    // Initialize a new 32-byte buffer (possibly allocate or fill defaults)
    // FUN_0064b9e0 takes size (0x20) and pointer-to-pointer to update
    FUN_0064b9e0(0x20, &pData);
    
    // Store the (possibly updated) pointer into member at offset 0x20
    *(void**)((int)this + 0x20) = pData;
}