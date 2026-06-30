// FUNC_NAME: SomeClass::attachToTarget
void __thiscall SomeClass::attachToTarget(void* thisPtr, int* pTarget)
{
    int** ppSlot1 = (int**)((uint)thisPtr + 0x9c);  // pointer to member slot (set 1)
    int* pNewSlot1 = nullptr;
    if (pTarget != nullptr) {
        pNewSlot1 = pTarget + 0x12;                 // offset to first node's link field
    }
    if (*ppSlot1 != pNewSlot1) {
        if (*ppSlot1 != nullptr) {
            FUN_004daf90(ppSlot1);                  // detach old node
        }
        *ppSlot1 = pNewSlot1;
        if (pNewSlot1 != nullptr) {
            *(int*)((uint)thisPtr + 0xa0) = pNewSlot1[1]; // save old back-link
            pNewSlot1[1] = (int)ppSlot1;            // set new back-link to this
        }
    }

    if (pTarget != nullptr) {
        bool bResult;
        pTarget = nullptr;
        // Call virtual function at vtable+0x10 with hash 0x55859efa
        bResult = (*(code**)*pTarget)[0x10](0x55859efa, &pTarget);
        int** ppSlot2 = (int**)((uint)thisPtr + 0xac);  // pointer to second slot
        uint uFlag = -(uint)(bResult) & unaff_EBX;   // unaff_EBX likely a global flag mask
        int* pNewSlot2 = nullptr;
        if (uFlag != 0) {
            pNewSlot2 = (int*)(uFlag + 0x48);        // offset computed from flag value
        }
        if (*ppSlot2 != pNewSlot2) {
            if (*ppSlot2 != nullptr) {
                FUN_004daf90(ppSlot2);               // detach old node
            }
            *ppSlot2 = pNewSlot2;
            if (pNewSlot2 != nullptr) {
                *(int*)((uint)thisPtr + 0xb0) = pNewSlot2[1]; // save old back-link
                pNewSlot2[1] = (int)ppSlot2;         // set new back-link to this
            }
        }
    }
    return;
}