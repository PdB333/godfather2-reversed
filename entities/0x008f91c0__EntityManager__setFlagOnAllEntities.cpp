// FUNC_NAME: EntityManager::setFlagOnAllEntities
void __thiscall EntityManager::setFlagOnAllEntities(int this, char enableFlag)
{
    uint count = *(uint *)(this + 0x98); // +0x98: number of entries in the array
    if (count != 0) {
        for (uint i = 0; i < count; i++) {
            int entityId = *(int *)(*(int *)(this + 0x94) + i * 8); // +0x94: pointer to array of 8-byte entries, first 4 bytes are entity ID
            // 0x48 is likely a special invalid/null ID
            if (entityId != 0 && entityId != 0x48) {
                int entity = FUN_00542d70(); // Resolve entity ID to pointer (likely takes entityId as argument, but decompiler omitted)
                if (entity != 0) {
                    // Offset 200 (0xC8) is a ushort flags field; bit 3 (0x0008) controls some state (e.g., visibility)
                    if (enableFlag == 0) {
                        *(ushort *)(entity + 200) &= 0xfff7; // Clear bit 3
                    } else {
                        *(ushort *)(entity + 200) |= 8;      // Set bit 3
                    }
                }
            }
        }
    }
}