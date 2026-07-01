// FUNC_NAME: SaveDataManager::writeOwnershipAndMoney
// Function at 0x00908700: Exports player-owned properties (OWND) and money (MONY) to a data stream.
// Uses global singletons: gObjectManager (0x0112a590), gDataWriter (0x012234e0), gGameState (0x01223484).
void SaveDataManager::writeOwnershipAndMoney(void* stream, int money) {
    // Guard: skip if game state indicates data should not be written (e.g., not ready)
    if (*(int*)(DAT_01223484 + 0xc) == 0) {
        // Get the player object data using a known hash (0x637b907 = "Player" or family hash)
        void* playerData = FUN_008c74d0(0x637b907);

        // Extract IDs from player data: +0x10c = family ID, +0x118 = property zone ID?
        uint familyId = *(uint*)(playerData + 0x10c);
        uint propertyId = *(uint*)(playerData + 0x118);

        // Count all objects in the global object list that are also of type 0x637b907
        uint objectCount = *(uint*)(DAT_0112a590 + 0xc);  // gObjectManager->count
        uint myTypeCount = 0;
        for (uint i = 0; i < objectCount; i++) {
            void* obj = *(void**)(*(int*)(DAT_0112a590 + 8) + i * 4);  // gObjectManager->objectArray[i]
            if (obj != nullptr) {
                int typeHash = FUN_0084a410(obj);
                if (typeHash == 0x637b907) {
                    myTypeCount++;
                }
            }
        }

        // Write ownership data: "OWND" followed by a formatted string of family ID, property ID, and count
        char ownershipBuffer[16];
        __snprintf(ownershipBuffer, 0x10, "%04X%04X%04X",
                   familyId & 0xffff,
                   propertyId & 0xffff,
                   myTypeCount & 0xffff);
        ownershipBuffer[15] = 0;  // null-terminate (though snprintf should do it)

        // Call writer virtual function (offset 0x14) to write a chunk with FourCC "OWND"
        (**(code**)(*DAT_012234e0 + 0x14))(stream, 0x4f574e44, ownershipBuffer);

        // Write money value: "MONY" followed by hex-formatted money integer
        char moneyBuffer[16];
        __snprintf(moneyBuffer, 0x10, "%08X", money);
        moneyBuffer[15] = 0;

        // Call writer virtual function (offset 0x14) to write a chunk with FourCC "MONY"
        (**(code**)(*DAT_012234e0 + 0x14))(stream, 0x4d4f4e59, moneyBuffer);
    }
}