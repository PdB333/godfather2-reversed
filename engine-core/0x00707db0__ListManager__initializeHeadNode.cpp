// FUNC_NAME: ListManager::initializeHeadNode
void __thiscall ListManager::initializeHeadNode() {
    // +0x180: pointer to head node (ListNode**)
    ListNode** ppHeadNode = reinterpret_cast<ListNode**>(reinterpret_cast<uint8_t*>(this) + 0x180);

    if (*ppHeadNode == nullptr) {
        // Prepare a buffer for node creation (local buffer, likely a struct)
        struct NodeBuffer {
            uint32_t field_00; // offset 0
            uint32_t field_04; // offset 4
            uint32_t field_08; // offset 8
            uint8_t data[56];  // offset 0x0C, size 56
            // total 68 bytes? but local_c and local_8 are placed after data, so total 76
        } buf; // Actually the decompiled local_44 (56 bytes) overlaps with data portion

        // The buffer is initialized: first 12 bytes zeroed
        buf.field_00 = 0;
        buf.field_04 = 0;
        buf.field_08 = 0;

        // Call a resource creation function (passing this, buffer, two globals, and 0)
        // FUN_008c9650 - likely creates or retrieves a resource
        NodeBuffer::createResource(this, &buf, _DAT_00e544b8, _DAT_00e544b4, 0);

        // After that, two global values are loaded into the buffer (offsets within data? or after)
        // The decompiler placed them as local_c and local_8, but they are probably part of the 56-byte data.
        // For simplicity, we treat them as separate fields for now.
        uint32_t globalVal1 = _DAT_00d5c458; // +0x0C
        uint32_t globalVal2 = DAT_00d5ef70; // +0x10 (example offsets)
        // They are not passed to the next function; maybe they overwrite buffer fields.
        // We'll store them in the buffer's data region at known offsets.
        *reinterpret_cast<uint32_t*>(buf.data + 0) = globalVal1; // assuming offset 0 in data
        *reinterpret_cast<uint32_t*>(buf.data + 4) = globalVal2; // offset 4

        // Now call FUN_008ca3b0 on the 56-byte buffer (returns a node pointer)
        ListNode* newNode = reinterpret_cast<ListNode*>(NodeBuffer::allocateNodeFromBuffer(&buf)); // FUN_008ca3b0

        if (*ppHeadNode != newNode) {
            // If current head exists, release it
            if (*ppHeadNode != nullptr) {
                ListNode::releaseNode(ppHeadNode); // FUN_004daf90 – frees node and nullifies pointer?
            }
            *ppHeadNode = newNode;
            if (newNode != nullptr) {
                // newNode+4 is a 'next' field (or back pointer)
                // Save old next value into the manager's field at +0x184
                *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x184) = newNode->next;
                // Then set newNode's next to point to the head pointer address (intrusive list)
                newNode->next = reinterpret_cast<ListNode*>(ppHeadNode);
            }
        }
        // Call a finalization function (global)
        ListManager::updateState(); // FUN_00706bd0
    }
}