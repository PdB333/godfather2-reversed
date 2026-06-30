// FUNC_NAME: SimManager::findEntityByComponentID
void __thiscall SimManager::findEntityByComponentID(int thisPtr, int componentId, char* outType, int* outEntityNode)
{
    // This function searches through a linked list of entities (starting at +8)
    // for an entity whose component array contains an entry with a matching ID.
    // The entity's data block (+0xC from list node) has an array of component entries
    // at +0x30 (size 0x18 each), a count at +0x38, and a table at +0x58 indexed by entry's +4 field.
    // On match, it outputs the type byte from data+4 and the entity node pointer,
    // and returns if the indexed table value is nonzero.

    if (*(short*)(thisPtr + 0x12) != 0) {  // check if any entities exist (count at +0x12?)
        for (int node = *(int*)(thisPtr + 8); node != 0; node = *(int*)(node + 4)) {
            int entityData = *(int*)(node + 0xC);
            if (entityData != 0) {
                int entryBase = *(int*)(entityData + 0x30);
                unsigned int count = *(unsigned int*)(entityData + 0x38);
                if (count != 0) {
                    for (unsigned int i = 0; i < count; i++) {
                        int entry = entryBase + i * 0x18;
                        if (*(int*)(entry + 0x14) == componentId) {
                            int tableIndex = *(int*)(entry + 4);  // index into the table at +0x58
                            int tableValue = *(int*)(entityData + 0x58 + tableIndex * 4);
                            *outType = *(char*)(entityData + 4);  // type byte from entity data
                            *outEntityNode = node;                 // return the node pointer
                            if (tableValue != 0) {
                                return;   // found a valid entry with non-zero table entry
                            }
                            break;   // table value is zero, stop searching this entity
                        }
                    }
                }
            }
        }
    }
}