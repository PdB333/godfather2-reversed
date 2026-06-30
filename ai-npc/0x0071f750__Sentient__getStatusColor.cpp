// FUNC_NAME: Sentient::getStatusColor
// Address: 0x0071f750
// This function appears to retrieve a status color for an entity based on its current state.
// It navigates through a member pointer chain to obtain the entity object,
// then checks an integer field at offset +0x50 (likely representing a status index).
// If the index is in range [1,5], it looks up a color from a global table and returns it;
// otherwise, it returns the high 24 bits of the original input (in_EAX zero-extended?).

uint __fastcall Sentient::getStatusColor(void* pMemberPtr)
{
    uint result;
    void* pObj;
    void* pEntity;
    int statusIndex;
    int statusColor;

    // Preserve the high 24 bits of the input register (in_EAX)
    result = in_EAX & 0xffffff00;

    // Navigate from member pointer to containing object by subtracting offset 0x48
    if (*(int*)((char*)pMemberPtr + 4) == 0) {
        pObj = 0;
    } else {
        pObj = (void*)(*(char**)((char*)pMemberPtr + 4) - 0x48);
    }

    // From that object, get another pointer at offset 0x200c and adjust by -0x3c
    if (pObj == 0) {
        pEntity = 0;
    } else {
        void* pTemp = *(void**)((char*)pObj + 0x200c);
        if (pTemp == 0) {
            pEntity = 0;
        } else {
            pEntity = (void*)((char*)pTemp - 0x3c);
        }
    }

    // Repeat the same navigation for a second pointer (iVar3) likely for consistency
    void* pObj2;
    void* pEntity2;
    // Recompute pObj2 (identical code as above)
    if (*(int*)((char*)pMemberPtr + 4) == 0) {
        pObj2 = 0;
    } else {
        pObj2 = (void*)(*(char**)((char*)pMemberPtr + 4) - 0x48);
    }
    if (pObj2 == 0) {
        pEntity2 = 0;
    } else {
        void* pTemp2 = *(void**)((char*)pObj2 + 0x200c);
        if (pTemp2 == 0) {
            pEntity2 = 0;
        } else {
            pEntity2 = (void*)((char*)pTemp2 - 0x3c);
        }
    }

    // Check the integer at entity offset +0x50 (status index)
    // It is used as an index into a global table after subtraction of 1
    if (pEntity2 != 0) {
        statusIndex = *(int*)((char*)pEntity2 + 0x50);
        if ((statusIndex - 1U) < 5) {
            // Lookup from global table DAT_00e517b8 – each entry is 8 bytes
            // Use index * 8, take first 4 bytes, and also take the value at entity +0x4c
            result = FUN_00705bc0(
                *(undefined4*)(&DAT_00e517b8 + statusIndex * 8),
                *(undefined4*)((char*)pEntity + 0x4c)   // Note: uses pEntity (first navigation) but pEntity2 should be same? They are equal but code uses iVar2 (first) here.
            );
        }
    }

    return result;
}