// FUNC_NAME: ObjectManager::findAndCleanupInGlobalList
int ObjectManager::findAndCleanupInGlobalList(void* pObject, undefined4 param2, undefined4 param3, void (*pCallback)(void*))
{
    int* pCurrentEntry = (int*)DAT_01129f8c;
    int* pEnd = (int*)DAT_01129f90;
    
    if (pCurrentEntry != pEnd) {
        do {
            int entryValue = *pCurrentEntry;
            int buffer[4] = {0, 0, 0, 0}; // local_14, local_10, local_c, local_8
            void* pLocalCallback = nullptr; // local_4
            
            int* pResult = (int*)FUN_00698c00(buffer, &pObject);
            int resultValue = *pResult;
            bool isMismatch = (resultValue != entryValue + 0xc);
            
            if (isMismatch) {
                // Cleanup the mismatched entry's data (offset +0x20)
                FUN_004d3e20(resultValue + 0x20);
            }
            
            if (buffer[1] != 0) { // local_10
                ((void (*)(int))pLocalCallback)(buffer[1]); // local_4 called with local_10
            }
            
            if (isMismatch) {
                if (pObject != nullptr) {
                    pCallback(pObject);
                }
                return entryValue;
            }
            
            pCurrentEntry++;
        } while (pCurrentEntry != pEnd);
    }
    
    if (pObject != nullptr) {
        pCallback(pObject);
    }
    return 0;
}