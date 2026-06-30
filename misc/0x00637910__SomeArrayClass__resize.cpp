// FUNC_NAME: SomeArrayClass::resize
void SomeArrayClass::resize(int newSize)
{
    // Reallocate array to new size (each element is 8 bytes)
    int* oldArray = *(int**)(this + 0xc);
    int oldCount = *(int*)(this + 0x1c);
    
    // Allocate new array with newSize elements (8 bytes each)
    int* newArray = (int*)FUN_006279a0(newSize * 8, oldCount * 8);
    *(int**)(this + 0xc) = newArray;
    
    // Zero out elements from oldCount to newSize
    for (int i = oldCount; i < newSize; i++) {
        *(int*)(*(int*)(this + 0xc) + i * 8) = 0; // Zero first 4 bytes of element
        // Note: second 4 bytes (offset +4) are not zeroed - likely intentional
    }
    
    // Update count
    *(int*)(this + 0x1c) = newSize;
}