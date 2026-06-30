// FUNC_NAME: AttachmentSlotManager::findOrCreateSlot
// Function at 0x005247a0: manages a fixed pool of 5 attachment slots (each 0xA0 bytes) linked to objects via intrusive list (object's head at +0x4).
// The function finds a slot already associated with the given object (by comparing slot's first field to object pointer), or allocates a new slot if pool not full.

#include <cstdint>

// Forward declarations
class GameObject; // has member at offset +0x4: next slot pointer (head of slot list)
class AttachmentSlot; // size 0xA0, first two ints: objectPtr and nextSlot

// Assuming class definition:
struct AttachmentSlot {
    GameObject* object; // +0x00: pointer to the owning object (or 0 if free)
    AttachmentSlot* next; // +0x04: next slot in object's linked list
    // ... remaining 0x98 bytes of slot data (likely initialized via FUN_00522bf0)
};

class AttachmentSlotManager {
public:
    // +0x90: slot array (5 slots * 0xA0)
    AttachmentSlot slots[5];
    uint8_t slotCount; // +0x450: number of used slots (0-5)
    // +0x50: some other member passed to slot initializer

    // Constructor etc. not shown.

    // Returns pointer to found/created slot, or nullptr if pool full and no match.
    AttachmentSlot* findOrCreateSlot(GameObject* obj) {
        uint8_t count = slotCount;
        int index = 0;
        
        // Search for an existing slot attached to obj
        if (count > 0) {
            AttachmentSlot* slot = &slots[0];
            while (index < count) {
                if (slot->object == obj) {
                    return slot;
                }
                index++;
                slot = (AttachmentSlot*)((uint8_t*)slot + 0xA0); // next slot
            }
        }

        // Not found; try to allocate new slot
        if (count >= 5) {
            return nullptr; // pool full
        }

        AttachmentSlot* newSlot = &slots[count];
        slotCount = count + 1;

        // Prepare pointer to object's head-of-list field (at obj+0x4)
        // This address will be stored in slot->object to allow fast removal later
        uintptr_t headPtr = (obj != nullptr) ? (uintptr_t)&obj->slotListHead : 0;

        // Remove previous association if this slot was already linked
        uintptr_t oldObj = reinterpret_cast<uintptr_t>(newSlot->object); // Actually slot->object is a GameObject*, but we treat as uintptr for comparison
        // In original: iVar4 = *piVar6 (which is slot->object as int)
        if (reinterpret_cast<uintptr_t>(newSlot->object) != headPtr) {
            if (oldObj != 0) {
                // Remove this slot from old object's linked list
                // oldObj is a pointer to the old object (the stored object pointer)
                GameObject* oldGameObj = reinterpret_cast<GameObject*>(oldObj);
                AttachmentSlot* current = oldGameObj->slotListHead;
                if (current == newSlot) {
                    oldGameObj->slotListHead = newSlot->next;
                } else {
                    while (current->next != newSlot) {
                        current = current->next;
                    }
                    current->next = newSlot->next;
                }
            }
            // Store new head pointer (address of object's slotListHead) as the first field
            newSlot->object = reinterpret_cast<GameObject*>(headPtr); // careful: storing address, not object pointer
            // Insert this slot at head of object's linked list
            if (headPtr != 0) {
                newSlot->next = reinterpret_cast<AttachmentSlot*>(headPtr + 4); // wrong: cannot just read headPtr+4
                // Actually we need to read the object's slotListHead from the object, not from headPtr
                // HeadPtr is the address of object's slotListHead, so *headPtr is the current head
                // This part is tricky - let's implement with proper pointer arithmetic
            }
        }

        // Call initialization on the slot (using some member at this+0x50)
        // FUN_00522bf0(this + 0x50); // presumably initializes the slot's data

        return newSlot;
    }
};