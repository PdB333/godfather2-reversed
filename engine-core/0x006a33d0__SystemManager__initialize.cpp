// FUNC_NAME: SystemManager::initialize
void __fastcall SystemManager::initialize(int* pGlobalHandle)
{
    // If the global handle is not yet initialized (null pointer stored)
    if (*pGlobalHandle == 0)
    {
        // Remove all entries from global subsystem list (sentinel-based doubly linked list)
        // The list uses a sentinel at g_subsystemListHead / g_subsystemListTail
        void** nodeIter = (void**)g_subsystemListHead; // PTR_LOOP_00e50c80
        if (nodeIter != &g_subsystemListHead) 
        {
            do {
                void** nextNode = (void**)*nodeIter;       // Save next pointer
                removeNodeFromList(nodeIter);               // FUN_009c8f10 - unlink node
                nodeIter = nextNode;
            } while (nodeIter != &g_subsystemListHead);
        }

        // Reset the sentinel list to empty (point to itself)
        g_subsystemListHead = (void*)&g_subsystemListHead;   // +0x0
        g_subsystemListTail = (void*)&g_subsystemListHead;   // +0x4 (PTR_PTR_LOOP_00e50c84)
        g_subsystemCount = 6;                                // DAT_00e50c7c - maximum subsystems

        // Allocate 4-byte handle (likely a subsystem pointer or ID)
        int* newHandle = (int*)allocateMemory(4);            // FUN_009c8e50(4)
        if (newHandle == nullptr)
        {
            newHandle = 0;
        }
        else
        {
            newHandle = (int*)constructSubsystemObject();    // FUN_00ab54d0 - initialize subsystem
        }

        // Store the constructed handle in the caller-provided pointer
        *pGlobalHandle = (int)newHandle;

        // Register the subsystem with a callback table (LAB_006a3000)
        uint subsystemId = getSubsystemId();                 // FUN_00ab5470
        registerSubsystemCallback(&g_subsystemTable, 0, 0, subsystemId); // FUN_00ab7410
    }
}