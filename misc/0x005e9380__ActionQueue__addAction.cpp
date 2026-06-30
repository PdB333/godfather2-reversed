// FUNC_NAME: ActionQueue::addAction

#include <cstdint>

// Represents a fixed-size circular buffer of actions (max 4 entries).
// Each entry is 0x78 (120) bytes.
class ActionQueue {
public:
    // Offsets in this class (relative to 'this'):
    // +0x1FC: int slotCount (number of occupied slots, 0-4)
    // +0x200: int headIndex (base offset for circular buffer)
    // +0x48C: int defaultData (copied into each new slot's last field)
    // +0x294: uint8_t slots[4 * 0x78] (array of 4 slots, 120 bytes each)

    // Each slot structure (size 0x78):
    // +0x00: int field0 (1st int)
    // +0x04: int fields[27] (from param_4)
    // +0x70: int field28 (last int from param_5)
    // +0x74: int field29 (copied from defaultData at +0x48C)
    // Total: 30 ints = 120 bytes

    // Adds a new action slot with given data.
    // @param data1  First int stored at offset +0x00
    // @param dataBlock  Pointer to 27 integers for the middle of the slot
    // @param data2  Int stored at offset +0x70
    // @return  A handle with low byte set to 1 and high 3 bytes encoding the slot address.
    //          Returns 0x??????01 on success (low bit always 1)
    uint32_t addAction(int data1, const int* dataBlock, int data2) {
        int count = *(int*)((uint8_t*)this + 0x1FC);  // current slot count
        int head = *(int*)((uint8_t*)this + 0x200);   // base index for circular buffer
        int slotIndex;

        if (count < 1) {
            // Buffer empty; start at head=0 and set count=1
            *(int*)((uint8_t*)this + 0x200) = 0;
            *(int*)((uint8_t*)this + 0x1FC) = 1;
            slotIndex = 0;  // after update head is 0, so slotIndex = head + count? Actually it's head + oldCount? Let's compute later.
        } else if (count < 4) {
            // Buffer partially full; increment count and compute next slot index
            slotIndex = head + count;
            if (slotIndex > 3) {
                slotIndex -= 4;
            }
            *(int*)((uint8_t*)this + 0x1FC) = count + 1;
        } else {
            // Buffer full (count == 4); overwrite the oldest slot
            // Slot index = head - 1 + count, wrapped if needed
            slotIndex = head - 1 + count;
            if (slotIndex > 3) {
                slotIndex -= 4;
            }
            // count remains 4
        }

        // Compute pointer to the chosen slot
        int* slotBase = (int*)((uint8_t*)this + 0x294 + slotIndex * 0x78);
        *slotBase = data1;                  // field at +0x00
        slotBase[0x1C] = data2;             // field at +0x70 (28th int)

        // Copy 27 integers from dataBlock into slotBase[1]..slotBase[27]
        int* dest = slotBase;
        for (int i = 0x1B; i != 0; i--) {
            dest++;
            *dest = *dataBlock;
            dataBlock++;
        }

        // Copy defaultData from this object into slotBase[0x1D] (29th int, offset +0x74)
        slotBase[0x1D] = *(int*)((uint8_t*)this + 0x48C);

        // Build return handle: high 3 bytes from slot address shifted by 8, low byte set to 1
        uint32_t handle = ((uint32_t)slotBase & 0xFFFFFF00) | 1;
        return handle;
    }
};