// FUN_004c4990: TNLConnection::processAck
void __thiscall TNLConnection::processAck(PacketNode** list, uint32_t* keyPair, int32_t param) {
    PacketNode* current = list[0]; // this+0x24
    if (current == nullptr) return;

    // First level: find node with matching first key
    while (current->key < keyPair[0]) {
        current = current->next;
        if (current == nullptr) return;
    }
    if (current->key != keyPair[0]) return;

    // Second level: traverse child list with second key
    PacketNode* child = current->child; // offset +0x0c (puVar1[3])
    if (child == nullptr) return;

    while (child->key < keyPair[1]) {
        child = child->next;
        if (child == nullptr) return;
    }
    if (child->key != keyPair[1]) return;

    // Found exact match – call helper to get sub-object
    int32_t* subObj = (int32_t*)helperFunc(); // FUN_004c46d0 (returns pointer or zero)
    if (subObj != nullptr) {
        // Adjust slot index by base offset (this+0x10)
        subObj[3] = (param - baseTime) >> 5; // offset 0x0c = slot index / window size
    }
}