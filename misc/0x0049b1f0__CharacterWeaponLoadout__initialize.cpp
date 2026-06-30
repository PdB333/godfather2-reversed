// FUNC_NAME: CharacterWeaponLoadout::initialize
void CharacterWeaponLoadout::initialize(int weaponId, ConfigurationData* config, byte someFlag)
{
    byte* weaponTable;
    int convertedId;
    ConfigurationDataEntry* entry;
    int i;
    int* entryPtr;
    uint loopIndex;
    bool isValid;

    // Reset state
    this->field_b0 = 0;       // +0xB0: some counter/flag
    this->field_b4 = 1;       // +0xB4: active flag?
    this->availableMask = 0;  // +0x10C: bitmask of available weapons

    weaponTable = GetGlobalWeaponTable();  // +0x4: pointer to weapon definitions array

    // Convert weapon ID to loadout index if valid
    isValid = (weaponId != 0);
    convertedId = 0;
    if (isValid) {
        convertedId = ConvertWeaponIdForLoadout(weaponId);
    }

    this->field_11c = someFlag;  // +0x11C: misc flag

    // Find matching entry in global weapon table
    i = 0;
    if (*weaponTable != 0) {
        entryPtr = *(int**)(weaponTable + 4);
        do {
            if (*entryPtr == convertedId) {
                this->weaponEntry = *(int**)(weaponTable + 4) + i * 0x2F; // +0xB8: pointer to 47-byte entry
                break;
            }
            if (*entryPtr == DAT_01217f84) { // global default weapon ID
                entry = entryPtr;
            }
            i++;
            entryPtr += 0x2F; // each entry is 0x2F bytes
        } while (i < (int)(uint)*weaponTable);
    }

    // Fallback to default entry if not found
    if (this->weaponEntry == 0) {
        if (DAT_01205468 == 0) {
            this->weaponEntry = (int*)entry;
        } else {
            this->weaponEntry = (int*)DAT_01205468;
        }
    }

    InitializeWeaponSlots(); // clears/resets slot data

    // Build available weapon mask from config
    loopIndex = 0;
    if (config->numSlots != 0) {
        int* slotPtr = &this->slotData; // +0xCC: start of slot array
        do {
            int weaponType = GetWeaponTypeForSlot(loopIndex);
            if (weaponType == 1) {
                // Virtual call: isWeaponUnlocked(this, *slotPtr)
                int unlocked = (*(this->vtable->checkUnlocked))(this->slotData[loopIndex]);
                if (unlocked != 0) {
                    this->availableMask |= (ushort)(1 << (weaponType & 0x1F));
                }
            }
            loopIndex++;
            slotPtr++;
        } while (loopIndex < config->numSlots);
    }

    this->field_10e = 0;       // +0x10E
    this->field_114 = 0;       // +0x114
    this->field_115 = 0;       // +0x115
    this->field_118 = 0xFFFFFFFF; // +0x118: maybe invalid/empty sentinel
}