// FUNC_NAME: ComponentBase::checkOwnerFlag
void __fastcall ComponentBase::checkOwnerFlag(int thisPtr)
{
    // thisPtr + 0x64: pointer to some sub-object (e.g., a state or behavior)
    int* subObjPtr = *(int**)(thisPtr + 0x64);
    
    // Check if the pointer is valid and not a sentinel value (0x48)
    if (subObjPtr != nullptr && subObjPtr != (int*)0x48) {
        // Compute the base of the owner structure by subtracting 0x48
        // (the sub-object is at offset +0x48 within the owner)
        int* ownerBase = (int*)((char*)subObjPtr - 0x48);
        
        // Check bit 1 of the flags field at ownerBase + 0xE8
        // If the bit is clear, call the update/activation function
        if ((*(unsigned int*)(ownerBase + 0xE8) >> 1 & 1) == 0) {
            FUN_00725fc0(); // Likely activates or updates the component
        }
    }
}