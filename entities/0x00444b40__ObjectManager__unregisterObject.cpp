// FUNC_NAME: ObjectManager::unregisterObject
void ObjectManager::unregisterObject(int id) {
    // Iterate over 16 slots (0x14 to 0x14 + 15*0x18 = 0x14 + 0x168 = 0x17C)
    uint slotIndex = 0;
    int* slotBase = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x14);

    do {
        if (slotBase != nullptr) { // always true, but kept for clarity
            ListNode* node = *reinterpret_cast<ListNode**>(slotBase + 0x3); // slotBase + 0xc (since int* offset 3 -> 12 bytes
            ListNode* prevNode = node;

            goto skip_recheck; // compensate for decompiler's goto

            while (node != nullptr) {
                if (node->id == id) {
                    // Remove node from free list prepend
                    *reinterpret_cast<ListNode**>(node) = *reinterpret_cast<ListNode**>(reinterpret_cast<char*>(this) + 0x2d8);
                    *reinterpret_cast<ListNode**>(reinterpret_cast<char*>(this) + 0x2d8) = node;

                    if (node != prevNode) {
                        *reinterpret_cast<ListNode**>(prevNode) = node->next;
                        node = prevNode;
                        break;
                    } else {
                        // Update head pointer in slot
                        *reinterpret_cast<ListNode**>(slotBase + 0x3) = node->next;
                        node = node->next;
                        prevNode = node;
                        if (node == nullptr) {
                            // Clear bit 0 of slot flags
                            *reinterpret_cast<uint*>(slotBase + 0x2) &= ~0x1U; // slotBase + 0x8 (int offset 2)
                            goto end_slot;
                        }
                    }
                }
                // Advance
skip_recheck:
                prevNode = node;
                node = node->next;
            }
        }
end_slot:
        slotIndex++;
        slotBase = reinterpret_cast<int*>(reinterpret_cast<char*>(slotBase) + 0x18);
    } while (slotIndex <= 15);

    // Remove from dynamic array at +0x10
    DynamicArray* dynArray = *reinterpret_cast<DynamicArray**>(reinterpret_cast<char*>(this) + 0x10);
    uint count = dynArray->count;
    if (count != 0) {
        int* data = dynArray->data;
        int* found = data;
        uint index = 0;
        while (id != *found) {
            index++;
            found++;
            if (index >= count) {
                return;
            }
        }
        // Replace found with last element
        if (index != count - 1) {
            data[index] = data[count - 1];
        }
        dynArray->count--;
    }
}