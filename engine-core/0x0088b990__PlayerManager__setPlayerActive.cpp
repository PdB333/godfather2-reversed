// FUNC_NAME: PlayerManager::setPlayerActive
void __thiscall PlayerManager::setPlayerActive(int this, char active, uint slotIndex)
{
    byte* flagPtr;
    SlotData* slotData;
    int entity;
    int state;
    uint totalEntities;
    uint entityIndex;
    uint slot;

    slot = slotIndex & 0xFF;
    *(char*)(slot + 0xBC + this) = active; // Set active flag for this slot

    if (active != '\0') {
        initializeSlot(); // FUN_0088a7b0 - spawn/initialize player for this slot
    }

    slotData = *(SlotData**)(this + 0xB0 + slot * 4); // Array of slot data pointers at +0xB0
    if ((slotData != 0) && (*(char*)(slot + 0xBC + this) != '\0')) {
        totalEntities = (uint)(byte)slotData->count3 + (uint)(byte)slotData->count2 + (uint)(byte)slotData->count1; // +0x80,0x81,0x82
        entityIndex = 0;
        if (totalEntities != 0) {
            do {
                // Get handle from slotData's entity array at +0x68
                slotIndex = *(undefined4*)(*(int*)(slotData->entityArray + entityIndex * 4)); // double dereference? Actually: *(undefined4*)(*(int*)(slotData + 0x68) + entityIndex*4)
                entity = resolveHandle(&slotIndex); // FUN_00889ee0 - resolve handle to entity pointer
                if (entity != 0) {
                    slotIndex = entity; // reuse slotIndex as entity pointer
                    state = getEntityState(entityIndex); // FUN_0088e1e0 - get state for this entity index
                    if (state == 2) {
                        flagPtr = (byte*)(*(int*)(entity + 0x14) + 0x51);
                        *flagPtr = *flagPtr & 0xEF; // Clear bit 4 (0x10)
                    } else {
                        flagPtr = (byte*)(*(int*)(entity + 0x14) + 0x51);
                        *flagPtr = *flagPtr | 0x10; // Set bit 4
                    }
                    if (*(short*)(entity + 0x12) == 0) { // Check if entity is "dead" or inactive
                        removeEntity(&slotIndex); // FUN_00888410 - remove entity
                        scheduleEvent(entity, 500); // FUN_0088ae10 - schedule respawn/event after 500ms
                        int subObj = *(int*)(entity + 0x14);
                        // Check if bounding box min <= max and not culled (bit 3 of +0x54)
                        if ((((*(float*)(subObj + 0x30) < *(float*)(subObj + 0x40) ||
                               *(float*)(subObj + 0x30) == *(float*)(subObj + 0x40)) &&
                             (*(float*)(subObj + 0x34) < *(float*)(subObj + 0x44) ||
                              *(float*)(subObj + 0x34) == *(float*)(subObj + 0x44))) &&
                            (*(float*)(subObj + 0x38) < *(float*)(subObj + 0x48) ||
                             *(float*)(subObj + 0x38) == *(float*)(subObj + 0x48))) &&
                           ((*(byte*)(subObj + 0x54) & 8) == 0)) {
                            debugDrawBoundingBox(*(undefined4*)(entity + 8), subObj + 0x30, subObj + 0x40); // FUN_00429430
                        }
                    }
                }
                entityIndex = entityIndex + 1;
            } while (entityIndex < totalEntities);
        }
    }
    return;
}