// FUNC_NAME: TNLConnection::insertSendPacket
void TNLConnection::insertSendPacket(int thisPtr, PacketHeader* header, Buffer* buffer, int offset)
{
    // thisPtr: pointer to TNLConnection object
    // header: 20-byte packet header (first 8 bytes, next 8 bytes, then 4-byte field)
    // buffer: contains data pointer at +0x0C and bit-size at +0x18
    // offset: added to base sequence number at this+0x64 to form sort key

    // Convert bit-size to byte size (rounded up)
    uint byteSize = (*(int*)((char*)buffer + 0x18) + 7U) >> 3;

    // Allocate node: 0x24 bytes header + data payload
    PacketNode* node = (PacketNode*)malloc(byteSize + 0x24);

    // Copy header fields into node
    *(uint64*)((char*)node + 4) = *(uint64*)header;           // +0x04: first 8 bytes
    *(uint64*)((char*)node + 12) = *(uint64*)(header + 1);    // +0x0C: next 8 bytes
    *(int*)((char*)node + 20) = *(int*)((char*)header + 16);  // +0x14: third field (4 bytes)

    // Compute sort key: base sequence (this+0x64) + offset
    int baseSeq = *(int*)((char*)thisPtr + 0x64);
    node->key = baseSeq + offset;                              // +0x18

    node->dataSize = byteSize;                                 // +0x1C

    // Copy payload data from buffer
    memcpy((char*)node + 0x20, *(void**)((char*)buffer + 0x0C), byteSize);

    // Insert node into sorted linked list (ascending by key)
    // List head at this+0x80
    PacketNode** prev = (PacketNode**)((char*)thisPtr + 0x80);
    PacketNode* current = *prev;
    while (current != nullptr && (uint)node->key > (uint)current->key) {
        prev = &(current->next);
        current = current->next;
    }
    node->next = current;
    *prev = node;
}