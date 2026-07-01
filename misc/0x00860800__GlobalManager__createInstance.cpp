// FUNC_NAME: GlobalManager::createInstance
void GlobalManager::createInstance(void)
{
    // Global singleton pointer (0x0112dfb4)
    if (DAT_0112dfb4 == nullptr) {
        // Allocate 20 bytes (5 * 4) for the singleton structure
        GlobalManager* newManager = (GlobalManager*)FUN_009c8e50(0x14);
        if (newManager != nullptr) {
            struct LocalData {
                int field0;
                int field1;
                int field2;
            } localData = {0, 0, 0};

            // Get the core system object (likely a manager or session)
            int* coreObject = (int*)FUN_004dddd0(); // e.g., GameManager::instance()

            // Generate a unique ID or hash for this singleton
            uint uVar3 = FUN_004265d0(&localData, coreObject); // e.g., HashUtils::compute

            // Store the core object and its derived ID in the singleton
            newManager->m_coreId = uVar3;       // +0x0C
            newManager->m_coreObject = coreObject; // +0x10

            // Call the third virtual function on the core object (offset +8 in vtable)
            (**(code**)(*coreObject + 8))();

            // Zero out the first three fields (size 12 bytes)
            newManager->m_field0 = 0; // +0x00
            newManager->m_field1 = 0; // +0x04
            newManager->m_field2 = 0; // +0x08

            DAT_0112dfb4 = newManager;
        } else {
            DAT_0112dfb4 = nullptr;
        }
    }
}