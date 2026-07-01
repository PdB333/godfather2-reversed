// Xbox PDB: AptCharacterSpriteInstBase::updateObjectMethods
// FUNC_NAME: setEntityFlagFromType

void __cdecl setEntityFlagFromType(const char* unusedFlagName, EntityFlags* entity, FlagCallbackData callbackData, int32_t bClear)
{
    // Walk the string to the end (strlen; unused in this function)
    char c;
    do {
        c = *unusedFlagName;
        unusedFlagName++;
    } while (c != '\0');

    ActionFlagManager* flagMgr = getGlobalFlagManager();  // FUN_005b46c0
    if (flagMgr == nullptr) {
        return;
    }

    int32_t typeId = *(int32_t*)(flagMgr + 4);  // +0x4: m_actionType
    if (typeId <= 199) {
        return;
    }

    int32_t tableIndex = typeId - 200;          // Types 200..217 map to table indices 0..17
    if (tableIndex < 0 || tableIndex > 17) {
        FUN_0059bf00();                         // assertion/error handler
        return;
    }

    uint32_t bitMask = *(uint32_t*)(&kActionFlagMaskTable[tableIndex]);  // DAT_00e2bc88[tableIndex]
    if (bitMask == 0xFFFFFFFF) {
        FUN_0059bf00();                         // invalid mask
        return;
    }

    uint32_t* flags = (uint32_t*)((uint8_t*)entity + 0x14);  // +0x14: m_actionFlags
    if (bClear != 0) {
        // Clear only the low 24 bits of the mask; preserve upper byte
        *flags &= ~(bitMask | 0xFF000000);
    } else {
        // Set the low 24 bits of the mask
        *flags |= (bitMask & 0x00FFFFFF);
        if (!isGameplayPaused()) {              // FUN_005b4030
            onFlagChanged(callbackData);        // FUN_005b8660
        }
    }
}