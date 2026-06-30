// FUNC_NAME: NetSession::allocatePacket
// Allocates a packet of type 6 with a linked list insertion.
// Allocation size = (dataLen * 4) + 0x18 (header size).
// Header data (two DWORDs) copied from param2 to offsets +0x10 and +0x14.
// __thiscall with this in ECX (unaff_EDI).

#include <cstdint>

// Allocation function pointer (DAT_012059dc)
extern void* (*g_alloc)(int, uint32_t);

// Error/invalid size handlers (placeholders)
extern void __fastcall allocationFailedHandler(void);
extern void __fastcall invalidAllocationSize(void);

// Packet structure (internal, offsets documented)
#pragma pack(push, 1)
struct PacketNode {
    PacketNode* next;      // +0x00
    uint8_t   type;       // +0x04 (constant 0x06)
    uint8_t   flags1;     // +0x05
    uint8_t   flags2;     // +0x06
    uint8_t   dataLen;    // +0x07 (byte copy of dataLen parameter)
    uint8_t   padding[8]; // +0x08..0x0F (uninitialized)
    uint32_t  headerData[2]; // +0x10..0x17 (copied from param2)
    // Additional data follows at +0x18 if dataLen > 2 (size = 0x18 + dataLen*4)
};
#pragma pack(pop)

class NetSession {
public:
    void allocatePacket(int dataLen, uint32_t* headerData);

private:
    // Internal pool structure pointed by this+0x10
    struct PacketPool {
        PacketNode* head;   // +0x0C
        uint32_t    totalAlloc; // +0x24
    };
    PacketPool* m_pool; // offset 0x10 from this
};

void NetSession::allocatePacket(int dataLen, uint32_t* headerData) {
    uint32_t allocSize = dataLen * 4 + 0x18;
    PacketNode* newPacket = nullptr;

    if (allocSize == 0) {
        // Label LAB_006381a4
        newPacket = nullptr;
    }
    else if (allocSize >= 0xFFFFFFFD) {
        invalidAllocationSize(); // FUN_00633920
    }
    else {
        newPacket = (PacketNode*)g_alloc(0, allocSize);
        if (newPacket == nullptr) {
            if (this != nullptr) {
                allocationFailedHandler(); // FUN_00635a80
                return;
            }
            newPacket = nullptr;
        }
    }

    // Update allocation counter if this exists
    if (this && m_pool) {
        uint32_t* counter = (uint32_t*)((uint8_t*)m_pool + 0x24); // +0x24
        *counter += allocSize;
    }

    // Initialize packet (only if newPacket is not null)
    if (newPacket) {
        // Linked list insertion at head
        newPacket->next = m_pool->head;       // *(int*)(pool+0x0C)
        m_pool->head = newPacket;

        // Set type and flags
        ((uint8_t*)newPacket)[4] = 0x06;      // type
        ((uint8_t*)newPacket)[5] = 0;          // flag1
        ((uint8_t*)newPacket)[6] = 0;          // flag2
        ((uint8_t*)newPacket)[7] = (uint8_t)dataLen; // length byte

        // Copy header data (two DWORDs) from param2
        newPacket->headerData[0] = headerData[0]; // puVar4[4]
        newPacket->headerData[1] = headerData[1]; // puVar4[5]
    }
}