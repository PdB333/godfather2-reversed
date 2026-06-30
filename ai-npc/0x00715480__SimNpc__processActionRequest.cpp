// FUNC_NAME: SimNpc::processActionRequest
bool __thiscall SimNpc::processActionRequest(int thisPtr, int* pComponentMgr, unsigned int actionId, int flags) {
    bool bResult;
    int* pComponent;
    char cHasComponent;
    int localBuffer1;
    char stackBuffer1[12];
    char stackBuffer2[12];

    // Check if the NPC is inactive (bit 1 of flags at +0xC)
    if ((*(unsigned int*)(thisPtr + 0xC) >> 1 & 1) == 0) {
        localBuffer1 = 0;
        // Call vtable function at offset 0x10 on the component manager to find/create component by hash
        cHasComponent = (**(char (__thiscall**)(int*, unsigned int, int*))(*pComponentMgr + 0x10))(pComponentMgr, 0x369AC561, &localBuffer1);
        if (cHasComponent == '\0') {
            pComponent = nullptr;
        } else {
            pComponent = (int*)localBuffer1;
            if (localBuffer1 != 0 && *(int**)(localBuffer1 + 0x22D8) != nullptr) {
                // Check an inner component's condition (vtable+8) using this->+0x10
                cHasComponent = (**(char (__thiscall**)(int, int))(**(int**)(localBuffer1 + 0x22D8) + 8))(*(int*)(localBuffer1 + 0x22D8), *(int*)(thisPtr + 0x10));
                if (cHasComponent != '\0') {
                    return 1;
                }
            }
        }
        // Copy action name into stack buffer
        stringCopy(stackBuffer1, pComponentMgr);
        int checkResult = compareActionId(stackBuffer1, actionId);
        if ((flags != 0) || (checkResult == 1) || (checkResult == 2)) {
            bool bValid = false;
            if (pComponent != nullptr) {
                cHasComponent = isComponentValid(pComponent);
                if (cHasComponent == '\0') {
                    // Component invalid, get default result
                    return getComponentDefaultResult(pComponent);
                }
                bValid = true;
            }
            // Prepare secondary buffer and execute the actual action
            initializeActionBuffer(pComponentMgr, stackBuffer2);
            unsigned char actionResult = executeAction(stackBuffer2, actionId, flags, pComponentMgr);
            if (bValid) {
                storeComponentResult(pComponent, actionResult);
            }
            return actionResult;
        }
    }
    return 0;
}