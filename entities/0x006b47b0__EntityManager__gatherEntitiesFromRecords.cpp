// FUNC_NAME: EntityManager::gatherEntitiesFromRecords
int EntityManager::gatherEntitiesFromRecords(int* recordsArray, int recordCount, DynamicArray<int>& outEntityIds)
{
    if (recordCount == 0) {
        return 0;
    }

    // recordsArray points to an array of structs of size 0x14 (20 bytes):
    //   offset 0: uint entityId (4 bytes)
    //   offset 4: byte data[16] (passed to FUN_008c1320)
    // The loop processes each record, skipping the first 4 bytes initially.
    int* currentRecordData = recordsArray + 1; // skip the first ID field, now points to the data portion
    int remaining = recordCount;

    do {
        uint entityId = *(currentRecordData - 1); // ID is at offset -4 (i.e., the original record's first field)

        // Check if the entity ID is valid (non-zero)
        if (FUN_008c74d0(entityId) != 0) {
            // Try to get a pointer to the entity from the data portion
            int* entityData = FUN_008c1320(currentRecordData);
            if (entityData == 0) {
                // Fallback: try another interpretation of the data
                entityData = FUN_00446100(currentRecordData, 0);
                if (entityData == 0) {
                    goto nextRecord;
                }
            }

            // Extract the entity's ID or pointer from offset 8 of the returned structure
            int entityValue = *(entityData + 2); // offset 8 (since sizeof(int)=4)

            if (entityValue != 0) {
                // Manage the dynamic array's capacity (param_3 = outEntityIds)
                int& count = outEntityIds.count;
                int& capacity = outEntityIds.capacity;
                if (count == capacity) {
                    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
                    FUN_006b1e10(newCapacity); // resize the internal buffer to newCapacity
                }
                // Append the entity value to the array
                int* buffer = outEntityIds.buffer;
                buffer[count] = entityValue;
                count++;
            }
        }
nextRecord:
        // Advance to the next record (0x14 = 20 bytes total, but we already skipped the ID, so step by 0x14)
        currentRecordData = (int*)((char*)currentRecordData + 0x14);
        remaining--;
    } while (remaining != 0);

    // Return total size of the input array in bytes
    return recordCount * 0x14;
}