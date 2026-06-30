// FUNC_NAME: PendingPacket::submitToQueue
// Address: 0x004562f0
// Role: Creates a Packet object from this PendingPacket's buffer and tries to add it to the given PacketQueue.
// Returns pointer to Packet on success, or null if queue is not accepting packets.

class PendingPacket;
class PacketQueue;
class Packet;

// --- External functions ---
extern void* allocateMemory(int size);               // FUN_009c8e50
extern bool isQueueAcceptingPackets(PacketQueue* queue); // FUN_004c8ae0
extern void growPacketArray(int newCapacity);        // FUN_00456a20 (operates on global or queue static?)

// VTable for Packet (0x00e365f0)
extern void** PACKET_VTABLE;

// --- Packet class (size 0x20) ---
class Packet {
public:
    void** vtable;               // +0x00: vtable (PTR_FUN_00e365f0)
    int refCount;                // +0x04: set to 0
    int flags;                   // +0x08: set to 0 later
    int dataSize;                // +0x0C: from PendingPacket::m_nDataSize
    int sequenceNumber;          // +0x10: from PendingPacket::m_nSequenceNumber
    int someFlag;                // +0x14: set to 0
    void* data;                  // +0x18: from PendingPacket::m_pData
    char bLastByte;              // +0x1C: set to 0
};

// --- PendingPacket class (source) ---
// Size unknown, but we only use offsets 0x10,0x14,0x18,0x1c
class PendingPacket {
public:
    // Many fields...
    void* m_pData;               // +0x10: pointer to data buffer
    int m_nDataSize;             // +0x14: size of data
    int m_nSequenceNumber;       // +0x18: sequence number
    int m_nReserved;             // +0x1C: used as next? (cleared)
};

// --- PacketQueue class (destination) ---
class PacketQueue {
public:
    // Many fields...
    Packet** m_ppPackets;        // +0x1C: dynamic array of Packet*
    int m_nCount;               // +0x20: number of packets in array
    int m_nCapacity;            // +0x24: capacity of array
    bool m_bAccepting;          // +0x4C: flag whether queue accepts new packets
};

// This function is a member of PendingPacket (this in EAX)
Packet* pendingPacketSubmitToQueue(PendingPacket* thisPacket, PacketQueue* queue) {
    int dataSize = thisPacket->m_nDataSize;
    void** oldData = nullptr;
    int capacity = 0;

    // Take ownership of the data from thisPacket
    if (dataSize != 0) {
        oldData = thisPacket->m_pData;           // +0x10
        thisPacket->m_nDataSize = 0;             // +0x14
        thisPacket->m_pData = nullptr;           // +0x10
        thisPacket->m_nReserved = 0;             // +0x1C
        capacity = dataSize;                     // keep original size for new packet
    }

    // Allocate new Packet object
    Packet* newPacket = (Packet*)allocateMemory(0x20);
    if (newPacket == nullptr) {
        return nullptr;
    }

    int seqNum = thisPacket->m_nSequenceNumber;  // +0x18

    // Initialize Packet fields
    newPacket->vtable = &PACKET_VTABLE;
    newPacket->refCount = 0;                    // [1] = 0
    newPacket->flags = 0;                      // later set to 0 again
    newPacket->dataSize = capacity;            // [3] = iVar6
    newPacket->sequenceNumber = seqNum;        // [4] = uVar2
    newPacket->someFlag = 0;                    // [5] = 0
    newPacket->data = oldData;                  // [6] = piVar7
    newPacket->bLastByte = 0;                   // (byte at +0x1C)

    if (oldData != nullptr) {
        // Call a function on oldData's vtable? Possibly retain reference
        // The decompiled: (**(code **)(*piVar7 + 8))();
        // This suggests that oldData points to an object with a vtable,
        // and we call its function at offset 8 (maybe addRef).
        ((void**)(oldData))[2](); // call function at offset 8
    }

    newPacket->flags = 0;                      // [2] = 0 again (redundant?)

    // Check if queue is accepting packets
    if (queue->m_bAccepting && isQueueAcceptingPackets(queue)) {
        // Dynamically grow array if needed
        if (queue->m_nCount == queue->m_nCapacity) {
            int newCapacity = (queue->m_nCapacity == 0) ? 1 : (queue->m_nCapacity * 2);
            growPacketArray(newCapacity);
        }

        // Append packet to queue
        Packet** targetSlot = (Packet**)(queue->m_ppPackets + queue->m_nCount);
        queue->m_nCount = queue->m_nCount + 1;
        if (targetSlot != nullptr) {
            *targetSlot = newPacket;
        }
        return newPacket;
    } else {
        // Queue not accepting: destroy the packet via vtable destructor
        ((void(*)(int))newPacket->vtable[0])(1); // likely operator delete
        return nullptr;
    }
}