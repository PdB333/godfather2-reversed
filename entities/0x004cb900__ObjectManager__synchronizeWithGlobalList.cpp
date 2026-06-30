// FUNC_NAME: ObjectManager::synchronizeWithGlobalList
void ObjectManager::synchronizeWithGlobalList(int this)
{
    // Get the global object manager (singleton)
    GlobalObjectManager* pGlobalMgr = reinterpret_cast<GlobalObjectManager*>(FUN_00ad8d40());
    if (pGlobalMgr) {
        // Get the global collection via vtable call at offset 0x34
        pGlobalMgr = reinterpret_cast<GlobalObjectManager*>(pGlobalMgr->vtable[0x34]()); // e.g., getGlobalCollection()
    }
    // Get the global list object via vtable call at offset 0x24
    GlobalList* pGlobalList = reinterpret_cast<GlobalList*>(pGlobalMgr->vtable[0x24]()); // e.g., getList()

    // Local object counts
    int localCount = *(int*)(this + 0xC); // number of objects in local array
    int globalCount = pGlobalList->getCount(); // vtable offset 0x3C

    int i = 0;
    if (localCount > 0) {
        do {
            // Get the i-th local object
            int** localArray = *(int***)(this + 0x14);
            int* pLocalObj = localArray[i];

            // Try to find a matching global object
            int j = 0;
            bool found = false;
            if (globalCount > 0) {
                do {
                    // Get j-th global object
                    int* pGlobalObj = pGlobalList->getItem(j); // vtable offset 0x24
                    int localId = *(int*)(pLocalObj + 0x104);
                    int globalId = pGlobalObj->getId(); // vtable offset 0x0C

                    if (globalId == localId) {
                        found = true;
                        break;
                    }
                    j++;
                } while (j < globalCount);
            }

            if (!found) {
                // Local object not present in global list – remove/destroy it
                FUN_006576b0(*(int*)(pLocalObj + 0x1A4), pLocalObj);
            }

            i++;
        } while (i < localCount);
    }
}