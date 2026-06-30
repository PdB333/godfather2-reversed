// FUNC_NAME: GetObjectActionByIndex
int GetObjectActionByIndex(uint32_t index) {
    // Global flag indicating if action system is active
    int result = g_someFlag; // DAT_012054f8

    // Check if flag is zero and index is valid
    if (g_someFlag == 0 && 
        (int)index >= 0 && 
        index < *(uint32_t*)(g_objectManager + 0x0C)) // +0x0C: count of objects
    {
        // Retrieve pointer to object from table at +0x04 (array base)
        int** objectPtr = *(int***)(*(int32_t*)(g_objectManager + 0x04) + index * 4);
        if (objectPtr != nullptr) {
            // Call virtual method at vtable+0x0C on object, returns another object
            int* actionObj = (**(int*(__thiscall**)(int*))(*objectPtr + 0x0C))(objectPtr);
            if (actionObj != nullptr) {
                // Call virtual method at vtable+0x50 on actionObj
                result = (**(int(__thiscall**)(int*))(*actionObj + 0x50))(actionObj);
                return result;
            }
        }
    }
    return result;
}