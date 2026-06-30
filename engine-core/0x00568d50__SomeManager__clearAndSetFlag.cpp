// FUNC_NAME: SomeManager::clearAndSetFlag
void __fastcall SomeManager::clearAndSetFlag(int thisPtr)
{
    uint i;
    
    // Set flag at offset 0x128 (likely m_bActive or m_bDirty) to 1
    *(byte*)(thisPtr + 0x128) = 1;
    
    // If there are items in the array at offset 0x12C (m_objects), release each one
    if (*(int*)(thisPtr + 0x14c) != 0) {
        uint* objects = (uint*)(thisPtr + 0x12C);
        for (i = 0; i < *(uint*)(thisPtr + 0x14c); i++) {
            FUN_009c8eb0(objects[i]);  // release/destroy object
        }
    }
    
    // Reset count to 0
    *(int*)(thisPtr + 0x14c) = 0;
}