// FUNC_NAME: EntityComponentManager::updateComponentSlots
// Function address: 0x00626dc0
// __thiscall member function of a class managing an array of component slots (0x14 bytes each).
// Uses a linked list (offset +0x18) to traverse multiple instances. The array start is at +0x10,
// and the number of slots is determined by (1 << (*(byte*)(this+7) & 0x1f)).
// Each slot structure:
//   +0x00: int type
//   +0x04: int* pObject (pointer to an object with a byte field at +5)
//   +0x08: int someState (set to 0 when slot is deactivated)
//   +0x0C: ? (unused)
//   +0x10: ? (unused)
// When type == 4, it sets bit 0 at pObject[5] (flag as "used").
// Then if type > 3 and that bit is not set, it clears the slot (type = -1, state = 0).

void EntityComponentManager::updateComponentSlots(void)
{
    int* pThis = reinterpret_cast<int*>(in_EAX);  // __thiscall: eax is this pointer
    if (pThis == 0) {
        return;
    }

    do {
        // Byte at +7 holds shift value for number of slots: count = 1 << (byte & 0x1f)
        unsigned char slotCountRaw = *(unsigned char*)((int)pThis + 7);
        int slotCount = 1 << (slotCountRaw & 0x1f);
        if (slotCount != 0) {
            // Iterate through array at +0x10, each slot 0x14 bytes
            int currentOffset = slotCount * 0x14;  // start one past last slot
            int remaining = slotCount;
            do {
                currentOffset -= 0x14;
                Slot* slot = reinterpret_cast<Slot*>((int)pThis + 0x10 + currentOffset);
                --remaining;

                int type = slot->type;
                if (type == 4) {
                    // Mark object as "active" by setting bit 0 at its offset +5
                    unsigned char* pObjFlags = reinterpret_cast<unsigned char*>(slot->pObject + 5);
                    *pObjFlags |= 1;
                    type = slot->type;  // re-read (might have changed? but no)
                }

                // If type > 3 and the object is not flagged as active, deactivate this slot
                if ((type > 3) && ((*(unsigned char*)(slot->pObject + 5) & 1) == 0)) {
                    slot->someState = 0;
                    slot->type = -1;  // invalid type indicates unused
                }
            } while (remaining != 0);
        }

        // Move to next instance via linked list at +0x18
        pThis = reinterpret_cast<int*>(*(int*)((int)pThis + 0x18));
    } while (pThis != 0);
}

// Internal structure for a slot (size 0x14 = 20 bytes)
struct Slot {
    int type;         // +0x00
    int* pObject;     // +0x04 (pointer to some object)
    int someState;    // +0x08
    int unknown0C;    // +0x0C
    int unknown10;    // +0x10
};