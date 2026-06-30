// FUNC_NAME: ObjectManager::removeById
// Address: 0x00447b50
// Role: Removes an object identified by id from an internal array and/or from linked lists.
// The object is first looked up in a compact array at (this+0xB0) with count (this+0xB4).
// If found and the index is valid, a callback is invoked.
// Then, if param_3 is non-zero, the function searches through four linked lists 
// (heads at this+0x90, this+0x98, this+0xA0, this+0xA8) for the same id.
// Removal behavior depends on a flag byte at offset 0x14 of the linked list node.

struct ListNode {
    ListNode* next;       // +0x00
    int field_04;         // +0x04
    int field_08;         // +0x08
    int field_0C;         // +0x0C
    int id;               // +0x10
    unsigned char flags;  // +0x14  // bit0: if set, calls different callback
};

struct ArrayEntry {
    int id;               // +0x00
    int field_04;         // +0x04 (unknown)
};

class ObjectManager {
public:
    ArrayEntry* arrayBase;   // +0xB0
    int arrayCount;          // +0xB4
    ListNode* listHeads[4];  // +0x90, +0x98, +0xA0, +0xA8 (assuming consecutive)

    // Internal callbacks
    void __thiscall onArrayRemoval(int id);       // FUN_00449470
    void __thiscall onListRemoval(int id);        // FUN_004479d0
    void __thiscall onFlaggedListRemoval(int id); // FUN_00447920

    void __thiscall removeById(int id, unsigned char removeFromLists);
};

void __thiscall ObjectManager::removeById(int id, unsigned char removeFromLists)
{
    // --- Array removal ---
    int index = this->arrayCount - 1;
    if (index >= 0) {
        ArrayEntry* entry = &this->arrayBase[index];
        do {
            if (entry->id == id) {
                if (index >= 0) {
                    this->onArrayRemoval();  // callback for array removal
                }
                break;
            }
            index--;
            entry--;
        } while (index >= 0);
    }

    // --- Linked list removal (optional) ---
    if (removeFromLists == 0) {
        return;
    }

    for (int listIndex = 0; listIndex < 4; listIndex++) {
        ListNode* node = this->listHeads[listIndex];
        while (node != nullptr) {
            if (node->id == id) {
                if (node != nullptr) {
                    if ((node->flags & 1) == 0) {
                        this->onListRemoval(id);   // FUN_004479d0(this, id)
                        return;
                    }
                    this->onFlaggedListRemoval(id); // FUN_00447920(param_2)
                    return;
                }
                break;
            }
            node = node->next; // iterate linked list
        }
    }
}