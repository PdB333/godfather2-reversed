// FUNC_NAME: PacketQueue::insertPacket

#include <windows.h>

// Forward declarations
struct PacketNode;
struct ListNode;

// Global data (from DAT_012224c0, DAT_012224ac, DAT_01205868)
extern CRITICAL_SECTION gPacketQueueCriticalSection; // 0x012224c0
extern ListNode* gPacketListHead;                    // 0x012224ac
extern void* (*gAllocFunc)(size_t, int*);            // 0x01205868

// Helper functions (FUN_0060d260, FUN_0060d150, FUN_0060ba00)
void insertBeforeNode(PacketNode** list, PacketNode* node); // FUN_0060d260
void appendToList(PacketNode** list);                       // FUN_0060d150
void handleEmptyFlag();                                     // FUN_0060ba00

struct PacketNode {
    uint64_t field_00;      // +0x00
    uint64_t field_08;      // +0x08
    uint32_t field_10;      // +0x10
    uint32_t sequenceNumber; // +0x14
    uint64_t field_18;      // +0x18 (includes byte at +0x1c)
    PacketNode* selfPointer; // +0x20
};

struct ListNode {
    PacketNode* packet; // +0x00
    ListNode* next;     // +0x04
};

void PacketQueue::insertPacket(PacketNode* packet) {
    // Check if packet's flag at +0x1c is zero
    if (*(char*)((int)packet + 0x1c) == '\0') {
        handleEmptyFlag();
        return;
    }

    // If packet's field at +0x04 is zero, allocate a new node and copy data
    if (*(int*)((int)packet + 4) == 0) {
        int allocParams[3] = {2, 0x10, 0}; // allocation parameters
        PacketNode* newNode = (PacketNode*)(*gAllocFunc)(0x30, allocParams);
        // Copy 5 qwords (40 bytes) from packet to newNode
        newNode->field_00 = packet->field_00;
        newNode->field_08 = packet->field_08;
        newNode->field_10 = packet->field_10;
        newNode->sequenceNumber = packet->sequenceNumber;
        newNode->field_18 = packet->field_18;
        // Set self-pointer at offset 0x20
        newNode->selfPointer = newNode;
        packet = newNode;
    }

    PacketNode* localList = packet; // local_14

    EnterCriticalSection(&gPacketQueueCriticalSection);

    ListNode* current = gPacketListHead;
    while (current != nullptr) {
        // Compare sequence numbers: insert before if packet's sequence is smaller
        if (packet->sequenceNumber < current->packet->sequenceNumber) {
            insertBeforeNode(&localList, packet);
            LeaveCriticalSection(&gPacketQueueCriticalSection);
            return;
        }
        current = current->next;
    }

    // If not inserted, append to the end of the list
    appendToList(&localList);
    LeaveCriticalSection(&gPacketQueueCriticalSection);
}