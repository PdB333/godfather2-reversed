// FUNC_NAME: SequencedPacketQueue::allocatePacketNode
// Function address: 0x00991300
// Role: Allocates a new packet node from a free list, assigns a sequence number, and inserts into an ordered doubly-linked list.
// The list is sorted by a short at node+0x44 (sequence number), starting from 5.
// The caller provides a data identifier (param_2) stored at node+0x40.

struct PacketNode {
    void** vtable;          // +0x00: vtable pointer (set to &PTR_FUN_00d91e00)
    PacketNode* next;       // +0x04
    PacketNode* prev;       // +0x08
    uint32_t field_0x0C;    // +0x0C: cleared
    uint32_t field_0x10;    // +0x10: cleared
    uint32_t field_0x14;    // +0x14: cleared
    uint32_t field_0x18;    // +0x18: cleared
    uint8_t  field_0x1C;    // +0x1C: cleared
    uint32_t field_0x20;    // +0x20: cleared
    uint32_t field_0x24;    // +0x24: cleared
    uint32_t field_0x28;    // +0x28: cleared
    uint32_t field_0x2C;    // +0x2C: cleared
    uint8_t  field_0x30;    // +0x30: cleared
    uint8_t  field_0x31;    // +0x31: cleared
    uint32_t field_0x38;    // +0x38: cleared
    uint32_t field_0x3C;    // +0x3C: cleared
    uint32_t dataId;        // +0x40: packet identifier (param_2)
    uint16_t sequence;      // +0x44: assigned sequence number
    uint16_t field_0x46;    // +0x46: cleared (pad?)
};

// Global data pointer used for copying packet data
extern uint8_t* gPacketDataBuffer; // DAT_0112a5a4

// Forward declarations of helper functions
void onPoolEmpty();               // FUN_004de190
void notifyFirstPacket(void* this, uint32_t label, int32_t flag); // FUN_005c0260
void copyPacketData(void* dest, void* src, int32_t size);         // FUN_00408900

SequencedPacketQueue* __thiscall SequencedPacketQueue::insertPacket(SequencedPacketQueue* this, uint32_t dataId)
{
    PacketNode* currentNode = reinterpret_cast<PacketNode*>(*(int32_t*)((int32_t)this + 0x60));
    uint16_t seqNum = 5;
    // Traverse the list to find a gap in the sequence (starting at 5)
    while (currentNode != nullptr) {
        if (currentNode->sequence != seqNum) {
            break;
        }
        currentNode = currentNode->next;
        ++seqNum;
    }

    uint16_t assignedSeq = seqNum;

    // Check conditions that might trigger pool expansion
    if ((*(int32_t*)((int32_t)this + 0x5C) == 0) &&
        (*(int32_t*)((int32_t)this + 0x58) == 0 || ((*(uint8_t*)((int32_t)this + 0x4C) & 1) == 0))) {
        onPoolEmpty(); // Possibly allocate more nodes
    }

    PacketNode* newNode = reinterpret_cast<PacketNode*>(*(int32_t*)((int32_t)this + 0x5C));
    if (newNode != nullptr) {
        // Pop from free list (singly linked list, head at this+0x5C)
        *(int32_t*)((int32_t)this + 0x5C) = *reinterpret_cast<int32_t*>(newNode); // head = newNode->next
        // Update pool counters
        ++(*(int32_t*)((int32_t)this + 0x38)); // allocated count
        --(*(int32_t*)((int32_t)this + 0x34)); // free count

        // Initialize the new node
        newNode->vtable = &PTR_FUN_00d91e00;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        newNode->field_0x0C = 0;
        newNode->field_0x10 = 0;
        newNode->field_0x14 = 0;
        newNode->field_0x18 = 0;
        newNode->field_0x1C = 0;
        newNode->field_0x20 = 0;
        newNode->field_0x24 = 0;
        newNode->field_0x28 = 0;
        newNode->field_0x2C = 0;
        newNode->field_0x30 = 0;
        newNode->field_0x31 = 0;
        newNode->field_0x38 = 0;
        newNode->field_0x3C = 0;
        newNode->dataId = dataId;
        newNode->sequence = assignedSeq;
        newNode->field_0x46 = 0;

        // If the main ordered list was empty, trigger notification
        if (*(int32_t*)((int32_t)this + 0x60) == 0) {
            notifyFirstPacket(this, /* label */ 0x00991080, 1);
            if (gPacketDataBuffer != nullptr) {
                copyPacketData((void*)((int32_t)this + 0x1C), gPacketDataBuffer, 0x8000);
            }
        }

        // Insert the new node into the ordered list
        PacketNode** head = reinterpret_cast<PacketNode**>((int32_t)this + 0x60);
        PacketNode** tail = reinterpret_cast<PacketNode**>((int32_t)this + 0x64);
        PacketNode* insertAfter = currentNode; // currentNode is the node where sequence gap was found (or null if end)

        if (insertAfter == nullptr) {
            // Append to end of list
            newNode->prev = *tail;
            if (*tail == nullptr) {
                *head = newNode;
                *tail = newNode;
            } else {
                (*tail)->next = newNode;
                *tail = newNode;
            }
        } else {
            // Insert before insertAfter
            newNode->next = insertAfter;
            newNode->prev = insertAfter->prev;
            if (insertAfter->prev == nullptr) {
                *head = newNode;
            } else {
                insertAfter->prev->next = newNode;
            }
            insertAfter->prev = newNode;
        }

    }
    return newNode;
}