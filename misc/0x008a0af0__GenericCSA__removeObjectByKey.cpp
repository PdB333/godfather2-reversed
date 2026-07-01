// FUNC_NAME: GenericCSA::removeObjectByKey
void __thiscall GenericCSA::removeObjectByKey(void* this, IKeyProvider* keyProvider) {
    // this + 0xB4: pointer to a linked list node member (offset 0x1c inside the container object)
    int* pLinkField = (int*)((char*)this + 0xB4);
    int linkValue = *pLinkField;
    
    // Sentinel values: 0 and 0x1c indicate an empty/invalid link
    if (linkValue != 0 && linkValue != 0x1c) {
        // The link field is at offset 0x1c in the container, so recover the container base
        int containerBase;
        if (linkValue == 0) {
            containerBase = 0;
        } else {
            containerBase = linkValue - 0x1c;
        }
        
        // Read the two key components from the container (offsets +0x24 and +0x28)
        int keyPart1 = *(int*)(containerBase + 0x28);
        int keyPart2 = *(int*)(containerBase + 0x24);
        
        // Get comparison keys from the external key provider via virtual function
        // keyProvider->vptr + 4 points to getKeyPair(int (&out)[2])
        int keyPairBuffer[2];
        int* pKey = (int*)(**(int (__thiscall***)(void*, int*))(*(int*)((char*)keyProvider + 0x58) + 4))(keyProvider, keyPairBuffer);
        
        if (keyPart2 == *pKey && keyPart1 == pKey[1]) {
            // Recalculate container pointer (might be needed again)
            int containerToDelete;
            if (linkValue == 0) {
                containerToDelete = 0;
            } else {
                containerToDelete = linkValue - 0x1c;
            }
            
            // Delete the container object itself
            FUN_0089fee0(containerToDelete);
            
            // Remove the link from the list (removes the pointer at this+0xB4)
            if (linkValue != 0) {
                FUN_004daf90(pLinkField);
                *pLinkField = 0;
            }
        }
    }
}