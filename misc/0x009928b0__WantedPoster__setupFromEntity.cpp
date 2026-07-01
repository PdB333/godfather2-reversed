// FUNC_NAME: WantedPoster::setupFromEntity
void __thiscall WantedPoster::setupFromEntity(uint32 entityId) {
    // +0x1c: entityId
    // +0x20: someValue
    // +0x24: nameBuffer (char*)
    // +0x28: descriptionBuffer (char*)
    // +0x2c: additionalInfoBuffer (char*)
    // +0x30: infoValue
    // +0x34-0x44: unknown (4-byte each)
    // +0x48: hasTagline (bool)
    // +0x4c: taglineBuffer (char*)
    // +0x50: taglineValue
    // +0x54-0x60: unknown (4-byte each)
    // +0x64: unknown byte
    // +0x68: longTextBuffer (char*)

    // Clear all buffers and fields
    someValue = 0;
    if (nameBuffer) *nameBuffer = 0;
    if (descriptionBuffer) *descriptionBuffer = 0;
    if (additionalInfoBuffer) *additionalInfoBuffer = 0;
    *(uint8*)(this + 0x33) = 0;
    *(uint8*)(this + 0x32) = 0;
    *(uint8*)(this + 0x31) = 0;
    *(uint8*)(this + 0x30) = 0;
    hasTagline = false;
    if (taglineBuffer) *taglineBuffer = 0;
    if (longTextBuffer) *longTextBuffer = 0;
    *(uint8*)(this + 0x53) = 0;
    *(uint8*)(this + 0x52) = 0;
    *(uint8*)(this + 0x51) = 0;
    *(uint8*)(this + 0x50) = 0;
    // Clear 4-byte fields at 0x34-0x44, 0x54-0x60
    *(uint32*)(this + 0x40) = 0;
    *(uint32*)(this + 0x3c) = 0;
    *(uint32*)(this + 0x38) = 0;
    *(uint32*)(this + 0x34) = 0;
    *(uint8*)(this + 0x44) = 0;
    *(uint32*)(this + 0x60) = 0;
    *(uint32*)(this + 0x5c) = 0;
    *(uint32*)(this + 0x58) = 0;
    *(uint32*)(this + 0x54) = 0;
    *(uint8*)(this + 0x64) = 0;

    // Get entity data from the entity ID
    EntityData* entityData = getEntityData(entityId); // FUN_006b0ee0
    if (entityData != nullptr) {
        // Set up poster data from entity
        // FUN_00992740 likely copies some data into buffers at +0x34, +0x54
        setupPosterData(entityData, (uint32*)(this + 0x34), (uint32*)(this + 0x54), &localFlag); // localFlag is a byte

        // Get global string table or manager
        StringTable* stringTable = getStringTable(); // FUN_006b2160
        const char* defaultStr = (const char*)0x0120546e; // "Unknown" or empty string
        const char* nameStr = stringTable->getString(); // first string
        if (nameStr == nullptr) nameStr = defaultStr;
        copyString(nameBuffer, nameStr, 0x40, stringTable->getStringLength()); // FUN_005c4660

        // Get description string from entity data
        StringTable* entityStringTable = getEntityStringTable(entityData->descriptionTable); // FUN_00849e20
        const char* descStr = entityStringTable->getString();
        if (descStr == nullptr) descStr = defaultStr;
        copyString(descriptionBuffer, descStr, 0x40, entityStringTable->getStringLength());

        // Check entity type (9 = certain category)
        if (entityData->type == 9) {
            // Get player info for this entity
            PlayerInfo* playerInfo = getPlayerInfoFromEntity(entityData); // FUN_008ff310
            if (playerInfo != nullptr) {
                // Get current player manager
                getCurrentPlayerManager(); // FUN_008fdfd0
                CurrentPlayer* currentPlayer = getCurrentPlayerInfo(); // FUN_00791540
                if (currentPlayer != nullptr) {
                    infoValue = currentPlayer->reputation; // +0xf8
                    return;
                }
            }
        }
        else {
            // For non-type-9 entities
            // Get additional info from entity data's extra pointer
            if (entityData->extraPointer != nullptr) {
                someValue = *(uint32*)*entityData->extraPointer; // +0x20
            }

            // Get character data from entity's character pointer
            CharacterData* characterData = getCharacterData(entityData->characterPtr); // FUN_008c74d0
            if (characterData != nullptr) {
                const char* addStr = characterData->name; // +0x8c
                if (addStr == nullptr) addStr = defaultStr;
                copyString(additionalInfoBuffer, addStr, 0x20, characterData->nameLength); // +0x90
                infoValue = characterData->someValue; // +0xf8
            }

            // If entity has a tagline (mission description)
            if (entityData->taglinePtr != nullptr) {
                uint32 taglineObj = *(uint32*)(entityData->taglinePtr + 0x14); // +0x14
                CharacterData* taglineChar = getCharacterDataFromObject(taglineObj); // probably same as above
                const char* tagStr = taglineChar->name; // +0x8c
                if (tagStr == nullptr) tagStr = defaultStr;
                copyString(taglineBuffer, tagStr, 0x20, taglineChar->nameLength); // +0x90

                // Build a hash for localized string lookup
                uint32 localHash[3] = {0, 0, 0};
                void* localObj = nullptr;
                uint32 localStrLen = 0;
                uint32 localHash1 = 0;
                uint32 localHash2 = 0;
                code* cleanupFunc = nullptr;

                // Determine hash based on tagline character's subType
                if (taglineChar->subType == 0x637b907) {
                    localHash = 0xdb4df9fa;
                } else {
                    localHash = 0x4c2f9353;
                }

                // Generate the hash object
                generateHash(localHash, &localHashObj); // FUN_00603330

                // Get localized string from database
                char* localizedStr = getLocalizedString(&localHashObj, entityData, 0, &localObj); // FUN_008bec50
                if (localizedStr != nullptr) {
                    const char* lstr = (localObj ? localObj : defaultStr);
                    copyString(longTextBuffer, lstr, 0x100, localStrLen); // FUN_005c4660
                }

                taglineValue = taglineChar->someValue; // +0xf8
                hasTagline = true;

                // Cleanup
                if (localObj != nullptr) {
                    cleanupFunc(localObj); // local_14
                }
                if (localHashObj[0] != 0) {
                    cleanupFunc(localHashObj[0]); // local_4
                }
            }
        }
    }
}