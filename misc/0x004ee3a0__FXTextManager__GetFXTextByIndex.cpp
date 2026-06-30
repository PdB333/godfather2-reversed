// FUNC_NAME: FXTextManager::GetFXTextByIndex

class FXText
{
public:
    virtual int GetType() = 0;                           // vtable+0x08, returns non-zero for valid objects
    char* m_pName;                                       // +0x04
    int m_nActiveFlag;                                   // +0x24 (index 9 in piVar1)
    // ... other fields
};

struct FXTextEntry                                                  // size 0x14
{
    uint32_t field_0x00;                                            // +0x00
    FXText* pObject;                                                // +0x04
    uint32_t field_0x08;                                            // +0x08
    uint32_t field_0x0C;                                            // +0x0C
    uint32_t field_0x10;                                            // +0x10
};

// This function finds the nIndex-th FXText object (0-based) in the manager's internal array.
// Returns nullptr if not found.
FXText* FXTextManager::GetFXTextByIndex(int nIndex)
{
    // *this (param_1) is a FXTextManager instance; its first member (offset +0) is a pointer
    // to an array descriptor (FXTextArray).
    void* pArrayDesc = *(void**)this;                               // *param_1
    int count = 0;
    if (pArrayDesc != nullptr)
    {
        // The array descriptor stores the number of entries as a short at offset +0x80.
        count = *(short*)((char*)pArrayDesc + 0x80);
    }
    if (count == 0)
        return nullptr;

    int foundCount = 0;
    // Entries begin at offset +0xF0 from pArrayDesc, each entry is 0x14 bytes.
    int entryOffset = 0xF0;
    for (uint i = 0; i < (uint)count; i++)
    {
        FXTextEntry* pEntry = nullptr;
        if (pArrayDesc != nullptr)
        {
            pEntry = (FXTextEntry*)((char*)pArrayDesc + entryOffset);
        }
        if (pEntry != nullptr && pEntry->pObject != nullptr)
        {
            // Call vtable+0x08 (virtual function) – returns non-zero if object is "active"
            int virtualResult = pEntry->pObject->GetType();
            if (virtualResult != 0)
            {
                // Check if the object's class name is "FXText" (string compare, 7 characters including null terminator)
                const char* target = "FXText";
                char* name = pEntry->pObject->m_pName;
                bool isFXText = true;
                for (int cmpIdx = 0; cmpIdx < 7; cmpIdx++)
                {
                    if (name[cmpIdx] != target[cmpIdx])
                    {
                        isFXText = false;
                        break;
                    }
                }
                // Also require the flag at offset +0x24 to be non-zero
                if (isFXText && pEntry->pObject->m_nActiveFlag != 0)
                {
                    if (foundCount == nIndex)
                        return pEntry->pObject;
                    foundCount++;
                }
            }
        }
        entryOffset += 0x14; // next entry
    }
    return nullptr;
}