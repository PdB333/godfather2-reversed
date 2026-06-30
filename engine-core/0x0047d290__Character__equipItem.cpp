// FUNC_NAME: Character::equipItem
int Character::equipItem() {
    // Check if player possesses any of the four items/slots
    if (m_ownedItems[0] != 0 || m_ownedItems[1] != 0 || m_ownedItems[2] != 0 || m_ownedItems[3] != 0) {
        // If there is already an equipped item, destroy it
        if (m_pEquippedItem != 0) {
            FUN_005e6820(m_pEquippedItem, 0, 0); // Detach item from character
            FUN_005e6660(m_pEquippedItem);       // Destroy item object
        }

        // Prepare creation parameters (likely item type, position, etc.)
        ItemCreationParams creationParams;
        creationParams.param0 = 0;
        creationParams.param1 = 0;
        creationParams.param2 = 0;
        creationParams.param3 = 0;
        // Local label address used as a callback or error handler? Not used directly.
        // void* callback = &errorHandler; // &LAB_0047d4d0

        // Create a new item of the appropriate type
        m_pEquippedItem = FUN_005e4950(DAT_012234bc, &creationParams);

        // If creation succeeded and initialization passes, return success
        if (m_pEquippedItem != 0 && FUN_0047d3c0()) {
            return 1;
        }
    }
    return 0;
}