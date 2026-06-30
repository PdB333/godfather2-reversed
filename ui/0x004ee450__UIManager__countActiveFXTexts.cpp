// FUNC_NAME: UIManager::countActiveFXTexts
int UIManager::countActiveFXTexts()
{
    // m_pData is a pointer to an internal data structure containing the UI element list
    // *this is the m_pData pointer (offset 0 in the UIManager object)
    Data* pData = *this;
    int count = 0;
    
    if (pData == 0) {
        return 0;
    }
    
    // Number of slots in the element array (stored as a short at offset 0x80 from the data base)
    int elementCount = (int)*(short*)((char*)pData + 0x80);
    if (elementCount == 0) {
        return 0;
    }
    
    // Slot array starts at offset 0xF0 (240 bytes) from the data base
    // Each slot is 0x14 (20) bytes. The slot structure:
    //   +0x00: unknown (not used here)
    //   +0x04: pointer to the UI element object (derived from FXText or similar)
    //   +0x08..+0x13: other fields
    int slotOffset = 0xF0;
    do {
        if (pData != 0) {
            void* slotAddr = (char*)pData + slotOffset;
            if (slotAddr != 0) {
                // Get the UI element object pointer from the slot at +4
                int* pObject = *(int**)((char*)slotAddr + 4);
                if (pObject != 0) {
                    // Call virtual function at vtable index 2 (offset 8) to get a type info pointer
                    // This function likely returns a pointer to a type descriptor object
                    typedef void* (*GetTypeInfoFunc)(void*);
                    GetTypeInfoFunc getTypeInfo = *(GetTypeInfoFunc*)(*(int*)pObject + 8);
                    void* pTypeInfo = getTypeInfo(pObject);
                    if (pTypeInfo != 0) {
                        // The type descriptor has a string (class name) at offset 4
                        char* typeNameStr = *(char**)((char*)pTypeInfo + 4);
                        // Compare first 7 characters to "FXText" (including null terminator)
                        bool match = true;
                        int cmpLen = 7;
                        char* pCmp1 = typeNameStr;
                        char* pCmp2 = "FXText";
                        do {
                            if (cmpLen == 0) break;
                            cmpLen--;
                            match = (*pCmp1 == *pCmp2);
                            pCmp1++;
                            pCmp2++;
                        } while (match);
                        // Additionally check if the object's "active" or "visible" flag at offset 36 (9th int) is non-zero
                        if (match && pObject[9] != 0) {
                            count++;
                        }
                    }
                }
            }
        }
        slotOffset += 0x14;  // Move to next slot
        elementCount--;
    } while (elementCount != 0);
    
    return count;
}