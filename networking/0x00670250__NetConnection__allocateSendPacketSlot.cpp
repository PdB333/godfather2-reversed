// FUNC_NAME: NetConnection::allocateSendPacketSlot
// Address: 0x00670250
// Role: Allocates a slot in the send packet window for a new reliable packet.
// This is part of TNL reliable packet delivery system (32-slot window).

#include <cstdint>

// Forward declarations (types guessed from context)
class NetConnection;
typedef struct NetPacket NetPacket;       // 28+ bytes, offset 0x1c is a byte, 0x2c and 0x30 are ints
typedef struct SendWindow SendWindow;     // contains slots array, nextSendSeq counter, a pointer to "connection state"

// Internal helper functions (likely part of same module)
extern int __stdcall getNextSequence(uint32_t* outFlag); // FUN_00672e60
extern void* allocatePacket();                           // FUN_00673070
extern void initPacket(void* packet, void* context);     // FUN_00671930
extern uint32_t getSlotFlags(uint16_t slotIndex, void* context); // FUN_00671870

// Structure for a send window slot (20 bytes)
struct SendSlot {
    int     sequenceNum;   // +0x00 (slot[1] in decompiled, actually index 1 in array)
    int     connection;    // +0x04 (slot[2] = param_1 / 8 bytes from slot start)
    void*   packet;        // +0x08 (slot[3])
    uint16_t flags;        // +0x0C (slot[4] low 16 bits)
    // padding? actually 5 ints total, so maybe one more int at +0x10? Not used.
};

// SendWindow structure (contains header and 32 slots)
struct SendWindow {
    int     headerPtr;            // +0x00  (points to some "connection state" structure)
    int     unknown_0x04;         // +0x04
    int     unknown_0x08;         // +0x08
    int     unknown_0x0C;         // +0x0C
    int     activeSlotCount;      // +0x10  (set to 1 after allocation)
    int     nextSendSeqAndFlags;  // +0x14  (low 16 bits = next send sequence number, high bits reserved)
    // then slots array at offset 0x18 (6 ints after start: param_2+6, each slot 5 ints)
    SendSlot slots[32];           // 32 slots, each 20 bytes (5 ints)
};

uint32_t __thiscall NetConnection::allocateSendPacketSlot(NetConnection* thisPtr, SendWindow* sendWindow, int payloadSize)
{
    // Read current sequence number (low 16 bits of the int at sendWindow+0x14)
    uint16_t slotIndex = (uint16_t)(sendWindow->nextSendSeqAndFlags);
    // Increment the whole int (high bits might be reserved)
    sendWindow->nextSendSeqAndFlags++;

    // Compute pointer to the slot
    SendSlot* slot = &sendWindow->slots[slotIndex];

    // Set slot fields
    slot->connection = (int)thisPtr;    // store pointer to connection
    uint32_t seqNum = getNextSequence(nullptr);  // get proper sequence number for packet
    slot->sequenceNum = (int)seqNum;

    // Store slot index at stack (local_1c) for return
    local_1c = slotIndex;

    // Allocate a NetPacket structure
    NetPacket* packet = (NetPacket*)allocatePacket();
    packet->connection = (int)thisPtr;          // +0x00
    packet->field_4 = 0;                        // +0x04
    packet->field_C = 0;                        // +0x0C (unknown)
    packet->field_18 = 0;                       // +0x18
    packet->field_1C = 0;                       // +0x1C (byte)
    packet->field_10 = 0;                       // +0x10
    packet->sequenceNum = (int)seqNum;          // +0x14 (offset 5 ints)
    packet->payloadSize = payloadSize;          // +0x08 (offset 2 ints)
    packet->someType = 3;                       // +0x10 (byte? cast at piVar3+4 = 3)

    slot->packet = packet;                      // store packet pointer in slot

    // Initialize the packet (set up payload pointers, etc.)
    initPacket(packet, nullptr);

    // Prepare local buffer for getSlotFlags? 
    uint32_t localBuffer[5] = {0xC0000, 0, 0, 0xC0000}; // local_18..local_c
    uint32_t flags = getSlotFlags(slotIndex, nullptr);
    slot->flags = (uint16_t)(flags & 0xFFFF);

    // Modify some state pointed by sendWindow->headerPtr
    int* header = (int*)sendWindow->headerPtr;
    header[0x2c/sizeof(int)] = 0;   // offset 0x2c
    header[0x30/sizeof(int)] = 0;   // offset 0x30
    *(char*)(header + 0x1c/sizeof(int)) = 0;  // offset 0x1c byte

    // Mark that we have active slots
    sendWindow->activeSlotCount = 1;

    return local_1c;  // return the slot index
}