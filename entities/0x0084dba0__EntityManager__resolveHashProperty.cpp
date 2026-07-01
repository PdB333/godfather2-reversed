// FUNC_NAME: EntityManager::resolveHashProperty
int EntityManager::resolveHashProperty(int* outParam, Entity* context) // Assuming context passed in EDI, outParam in ECX (stack param in decompilation)
{
    int result = 0;

    if (outParam != nullptr) {
        // Get the global singleton (likely GameManager or SimManager)
        int* globalMgr = (int*)getSingleton(gGlobalManagerPtr);
        if (globalMgr != nullptr) {
            // Call virtual function at vtable+0x34 to get the current phase/state object
            int currentPhase = (*(int (**)(void))(*globalMgr + 0x34))();
            // Check if phase has a next pointer at offset 0x0c (linked list)
            int* phaseListPtr = nullptr;
            if (*(int*)(currentPhase + 0x0c) == 0) {
                phaseListPtr = (int*)0;
            } else {
                // The actual entry is offset -0x48 from the 'next' pointer (container_of)
                phaseListPtr = (int*)(*(int*)(currentPhase + 0x0c) - 0x48);
            }

            if (phaseListPtr != nullptr) {
                // Check phase type at offset 0x30
                if (*(int*)(currentPhase + 0x30) == 3) {
                    *outParam = 0;
                    char found = (*(char (**)(int*, int*))(*phaseListPtr + 0x10))(0xa5975eb2, outParam);
                    if (found != 0 && *outParam != 0) {
                        // If first hash matches, call another function to get value
                        result = FUN_0084db20(phaseListPtr);
                        return result;
                    }
                }

                // Try second hash
                *outParam = 0;
                char found = (*(char (**)(int*, int*))(*phaseListPtr + 0x10))(0x55859efa, outParam);
                if (found != 0 && context != nullptr) {
                    // Return value from context structure at large offset (0x1ed4)
                    result = *(int*)((int)context + 0x1ed4);
                }
            }
        }
    }
    return result;
}