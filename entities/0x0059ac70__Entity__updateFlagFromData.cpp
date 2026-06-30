// FUNC_NAME: Entity::updateFlagFromData
void __fastcall Entity::updateFlagFromData(uint *thisPtr)
{
    // thisPtr is a pointer to the entity object
    // +0x08: pointer to some data structure (param_1[2])
    uint *dataPtr = (uint *)thisPtr[2];
    
    // Check a short at offset +0x02 from dataPtr
    // If it's not 5, call a virtual function from a global vtable
    if (*(short *)((char *)dataPtr + 2) != 5) {
        // DAT_01205590 is a pointer to a vtable; call function at offset 4
        (**(void (__fastcall **)())(*(uint *)DAT_01205590 + 4))();
    }
    
    // Read a byte at offset +0x04 from dataPtr, shift left by 4
    int byteShifted = (int)*(char *)((char *)dataPtr + 4) << 4;
    
    // Set bit 4 (0x10) of *thisPtr to match bit 4 of byteShifted
    // Equivalent to: *thisPtr = (*thisPtr & ~0x10) | (byteShifted & 0x10);
    *thisPtr = *thisPtr ^ ((byteShifted ^ *thisPtr) & 0x10);
}