// FUNC_NAME: EntityListManager::removeEntityByID
// Address: 0x007272b0
// Removes an entity from a fixed-size slot array by matching its ID at offset 0x48.
// The array has count entries starting at offset 0xBC, but slot 0 is a dummy/sentinel.
// Uses a linked list pattern via the node pointers at offset 0x4 in the entity objects.

class EntityListManager {
public:
    // Assumed external functions
    void __nodeRemove(int* slotPtr);   // FUN_004daf90
    void __onListEmpty(int a, int b, int c); // FUN_009c6320

    void removeEntityByID(int id) {
        int count = *(short*)((char*)this + 0xB4);
        if (count <= 0) return;

        int i = 0;
        int* curSlot = (int*)((char*)this + 0xC4); // start at slot index 1 (skip dummy)
        do {
            int objPtr = *curSlot;
            int objID;
            if (objPtr == 0) {
                objID = 0;
            } else {
                // ID stored at offset 0x48 from the entity object
                objID = *(int*)(objPtr + 0x48);
            }

            if (objID == id) {
                int* lastSlot = (int*)((char*)this + 0xBC + count * 8);
                int* foundSlot = (int*)((char*)this + 0xC4 + i * 8);
                if (foundSlot != lastSlot) {
                    int lastObj = *lastSlot;
                    if (*foundSlot != lastObj) {
                        if (*foundSlot != 0) {
                            __nodeRemove(foundSlot);
                        }
                        *foundSlot = lastObj;
                        if (lastObj != 0) {
                            // Update linked list: set foundSlot's next pointer to the next of lastObj
                            foundSlot[1] = *(int*)(lastObj + 4);
                            // Set lastObj's next pointer to foundSlot
                            *(int**)(lastObj + 4) = foundSlot;
                        }
                    }
                }
                // Clear the last slot
                int* lastSlotClear = (int*)((char*)this + 0xBC + count * 8);
                if (*lastSlotClear != 0) {
                    __nodeRemove(lastSlotClear);
                    *lastSlotClear = 0;
                }
                break;
            }
            i++;
            curSlot += 2; // advance by 2 ints (8 bytes)
        } while (i < count);

        // Decrement count
        *(short*)((char*)this + 0xB4) = count - 1;

        // If empty and flag set, invoke callback
        if (*(short*)((char*)this + 0xB4) == 0 &&
            (*(unsigned char*)((char*)this + 0x114) & 0x20) != 0) {
            __onListEmpty(*(int*)((char*)this + 0xA0),
                          *(int*)((char*)this + 0xA4),
                          *(int*)((char*)this + 0x50));
            *(unsigned char*)((char*)this + 0x114) &= 0xDF;
        }
    }
};