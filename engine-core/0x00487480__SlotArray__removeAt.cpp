// FUNC_NAME: SlotArray::removeAt
// 00487480: Removes a slot at the given index from a fixed-size array (0x24 bytes per slot).
// The array holds entries with potential linked list nodes (singly-linked via field0/field1).
// Shifts subsequent entries down, and unlinks the removed entry from its linked list if necessary.

struct SlotEntry {
    int* pHead;       // +0x00: Pointer to the head of a linked list (singly-linked) that this entry belongs to.
    int  pNext;       // +0x04: Next pointer in the linked list (or magic sentinel 0x2a7ed975 if not part of a list)
    int  field_08;    // +0x08: Unknown
    int  field_0C;    // +0x0C: Unknown
    int  field_10;    // +0x10: Unknown
    int  field_14;    // +0x14: Unknown
    int  inUse;       // +0x18: Non-zero if the slot is active (used for linked‑list check)
    int  data0;       // +0x1C: First data field (copied during shift)
    int  data1;       // +0x20: Second data field (copied during shift)
};

class SlotArray {
public:
    int slotCount;                       // +0x90: Number of occupied slots
    __thiscall void removeAt(int index); // 0x00487480
private:
    SlotEntry slots[1];                 // Actual array, size determined by capacity (unknown)
};

// External helper functions (identified from Ghidra callees)
void destroyEntry(SlotEntry* entry);    // 0x00407640
void clearEntry(SlotEntry* entry);      // 0x00487200

void __thiscall SlotArray::removeAt(int index) {
    if (index >= this->slotCount) {
        return;
    }

    int newCount = this->slotCount - 1;

    // ---- Shifting entries left when not removing the last one ----
    if (index < newCount) {
        // iVar6 points to the entry at index+1 (start of the span to shift)
        SlotEntry* dst = &this->slots[index];
        SlotEntry* src = &this->slots[index + 1];
        int remaining = newCount - index; // number of entries to move

        do {
            // If the current entry is linked into a list, free it first
            if (dst->inUse != 0 && dst->pNext != 0x2a7ed975) {
                destroyEntry(dst);
            }
            clearEntry(dst);

            // Copy the two data fields from the next entry
            dst->data0 = src->data0;
            dst->data1 = src->data1;

            dst++;
            src++;
            remaining--;
        } while (remaining > 0);
    }

    // ---- Remove the now‑empty last slot ----
    SlotEntry* lastSlot = &this->slots[newCount];  // The slot that became vacant after shifting
    if (lastSlot->inUse != 0 && lastSlot->pNext != 0x2a7ed975 && lastSlot->pHead != nullptr) {
        // Unlink from singly‑linked list using the head pointer
        int* headNode = lastSlot->pHead;                      // head of the linked list
        int** headNextPtr = (int**)(headNode + 1);            // &(headNode->next)
        if (*headNextPtr == (int*)lastSlot) {
            // The head node pointed directly to this slot; update head's next to skip it
            *headNextPtr = (int*)lastSlot->pNext;
        } else {
            // Traverse the list to find the predecessor node
            int* currentNode = *headNextPtr;
            int* nextNode = (int*)(currentNode[1]);
            while (nextNode != (int*)lastSlot) {
                currentNode = nextNode;
                nextNode = (int*)(currentNode[1]);
            }
            // Update predecessor's next pointer to skip the removed slot
            currentNode[1] = lastSlot->pNext;
        }
        lastSlot->pHead = nullptr;
    }

    // Clear the vacated slot (head, inUse, data0, data1)
    lastSlot->pHead = nullptr;
    lastSlot->inUse = 0;
    lastSlot->data0 = 0;
    lastSlot->data1 = 0;

    this->slotCount = newCount;
}