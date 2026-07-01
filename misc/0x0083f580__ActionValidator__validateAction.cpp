// FUNC_NAME: ActionValidator::validateAction
// Address: 0x0083f580
// Role: Validate whether an action can be executed for an entity (checks table entry, optional debug hash, final validation)

undefined1 __thiscall ActionValidator::validateAction(Entity* pEntity, ActionData* pActionData)
{
    char cVar1;
    undefined1 uVar2;
    uint uVar3;
    int local_8;
    uint* local_4;

    // Null entity check
    if (pEntity == 0) {
        return 0;
    }

    // Check if the action table entry (offset +0x20 base, index at pActionData+4 * 0x24) is enabled
    // pEntity+0x20 likely points to an array of ActionSlot structures (size 0x24)
    cVar1 = checkActionEnabled(pEntity, *(int*)(pEntity + 0x20) + (uint)*(ushort*)(pActionData + 4) * 0x24);
    if (cVar1 == '\0') {
        return 0;
    }

    // If debug flag at this+0x14c bit 0 is set, perform additional hash-based validation
    if ((*(byte*)(this + 0x14c) & 1) != 0) {
        local_8 = 0;
        local_4 = (uint*)0x0;
        // Look up data by hash 0xee654334 using the word at pActionData+8 as key
        cVar1 = lookupHashData(*(ushort*)(pActionData + 8), 0xee654334, &local_8);
        if (cVar1 == '\0') {
            return 0;
        }
        uVar3 = 0;
        // If lookup succeeded and structure at local_8 has byte at +6 == 0x02, read the uint at local_4
        if (((local_4 != (uint*)0x0) && (local_8 != 0)) && (*(char*)(local_8 + 6) == '\x02')) {
            uVar3 = *local_4;
        }
        // Check bit 2 (0x4) in the returned flags; if not set, deny action
        if ((uVar3 & 4) == 0) {
            return 0;
        }
    }

    // Final validation/execution (e.g., apply costs, resolve animation)
    uVar2 = finalizeActionValidation(pEntity, pActionData);
    return uVar2;
}