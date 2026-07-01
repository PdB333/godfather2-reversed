// Xbox PDB: void __cdecl luaG_typeerror(struct lua_State *,struct lua_TObject const *,char const *)
// FUNC_NAME: SlotManager::removeSlot
void __thiscall SlotManager::removeSlot(uint objectId)
{
    uint* table = *(uint**)(this + 0x14);          // +0x14: pointer to slot table
    int result;
    int dummyFlag = 0;

    uint currentOffset = *table;                    // table[0]: start offset
    do {
        if (table[1] <= currentOffset) {            // table[1]: end offset (exclusive)
            goto cleanup;
        }
        if (objectId == currentOffset) {
            // Calculate index into table: (objectId - baseId) / 8
            int index = (int)(objectId - *(int*)(this + 0x0C)) >> 3;  // +0x0C: base ID
            result = removeEntry(table, index, &dummyFlag);
            if (result != 0) {
                goto cleanup;
            }
            goto cleanup;
        }
        currentOffset += 8;                         // Each slot occupies 8 bytes
    } while (true);

cleanup:
    onRemovalComplete();                            // Always called after removal attempt
}