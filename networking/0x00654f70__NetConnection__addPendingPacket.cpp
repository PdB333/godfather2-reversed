// FUNC_NAME: NetConnection::addPendingPacket

// This function inserts a pending packet into a sorted linked list (by timestamp) for later transmission.
// The list head is at this+0x80. The node structure:
//   +0x00: next pointer (ListNode*)
//   +0x04: uint64 sequence number
//   +0x0C: uint64 ack mask
//   +0x14: uint32 flags
//   +0x18: uint32 timestamp (calculated as baseTimestamp + deltaTime)
//   +0x1C: uint32 dataSize (in bytes? or 8-byte words? but memcpy copies this many bytes)
//   +0x20: packet data (size bytes)

struct PacketHeader {
    uint64_t sequence;   // +0
    uint64_t ackMask;    // +8
    uint32_t flags;      // +16
};

struct PacketBuffer {
    void* data;      // +0xc
    uint32_t size;   // +0x18 (data length in bytes)
};

struct PendingPacketNode {
    PendingPacketNode* next; // +0
    uint64_t sequence;       // +4
    uint64_t ackMask;        // +12
    uint32_t flags;          // +20
    uint32_t timestamp;      // +24 (used for ordering, lower = send earlier)
    uint32_t dataSize;       // +28 (bytes of data following)
    uint8_t data[];          // +32
};

void __thiscall NetConnection::addPendingPacket(void* thisPtr, PacketHeader* header, PacketBuffer* buffer, int32_t deltaTime) {
    // Calculate number of bytes for data (assuming buffer->size is in bytes)
    uint32_t dataSize = buffer->size;                         // +0x18 of buffer
    // Allocate node: node header (36 bytes?) + data bytes
    // Note: 0x24 = 36, but header appears to be only 32 bytes; extra 4 may be padding or internal size field
    PendingPacketNode* node = (PendingPacketNode*)malloc(dataSize + 0x24);
    if (node == nullptr) return;

    // Copy header fields
    node->sequence = header->sequence;   // *(uint64*)(node+1)
    node->ackMask   = header->ackMask;   // *(uint64*)(node+3)
    node->flags     = header->flags;     // node[5]

    // Set timestamp: base time from this+0x64 + delta
    int32_t baseTimestamp = *(int32_t*)((uint8_t*)thisPtr + 100); // +0x64
    node->timestamp = baseTimestamp + deltaTime;                 // node[6]

    node->dataSize = dataSize;                           // node[7] (derived from buffer->size? but calculation used extra shift? We'll keep it as is)
    // Copy packet payload
    memcpy(node->data, buffer->data, dataSize);          // memcpy(node+8, data, dataSize)

    // Insert node into sorted linked list (ascending by timestamp)
    ListNode** headPtr = (ListNode**)((uint8_t*)thisPtr + 0x80); // pointer to list head
    ListNode* current = *headPtr;
    ListNode** insertAfter = headPtr; // address of pointer to modify
    while (current != nullptr) {
        if (node->timestamp <= ((PendingPacketNode*)current)->timestamp) {
            break;
        }
        insertAfter = &current->next;
        current = current->next;
    }
    // Insert node after insertAfter (or at head)
    node->next = *insertAfter;
    *insertAfter = (ListNode*)node;
}