// FUNC_NAME: PacketManager::insertPacket
// Function at 0x00672b00: Inserts a packet node into a hash table and a linked list.
// The function takes a manager handle (pointer to pointer), two short IDs, an int value, and an output error code.
// It allocates a node, copies data from the manager's template, and inserts into hash bucket and a separate list.

#include <cstdint>

// Forward declarations
int* allocatePacketNode(); // FUN_00672d10
void reportError(uint32_t param1, int param2, int param3, int* errorCode); // FUN_00674d40

// Structure for a packet node (size unknown, but many fields)
struct PacketNode {
    // +0x00: next pointer in hash bucket
    // +0x04: previous pointer in hash bucket
    // +0x08: next pointer in separate list? (set to 0)
    // +0x0C: previous pointer in separate list? (set to 0)
    // +0x10: next pointer in separate list? (set to old head)
    // +0x14: short field (copied from manager+0xCC)
    // +0x18: int field (copied from manager+0xD0)
    // +0x1C: int field (copied from manager+0xD4)
    // +0x20: int field (copied from manager+0xD8)
    // +0x24: int field (copied from manager+0xDC)
    // +0x28: int field (copied from manager+0xE0)
    // +0x2C: int field (copied from manager+0xE4)
    // +0x30: short field (copied from manager+0xE8)
    // +0x34: int field (copied from manager+0xEC)
    // +0x38: int field (copied from manager+0xF0)
    // +0x3C: int field (copied from manager+0xF4)
    // +0x40: int field (copied from manager+0xF8)
    // +0x44: int field (copied from manager+0xFC)
    // +0x48: int field (copied from manager+0x100)
    // +0x4C: int field (copied from manager+0x10C)
    // +0x50: int field (copied from manager+0x110)
    // +0x54: int field (copied from manager+0x114)
    // +0x58: short field (copied from manager+0x120)
    // +0x5C: short field (copied from manager+0x108)
    // +0x5A: short field (set based on manager+0x118)
    // +0x60: short (param_4)
    // +0x62: short (param_3)
    // +0x64: int (param_5)
};

// Structure for the manager (partial)
struct PacketManager {
    // +0x00: vtable? (not used directly)
    // +0x20: pointer to allocator/pool structure
    // +0x38: pointer to something (maybe a function table)
    // +0x3C: function pointer (virtual)
    // +0xCC: short field (copied to node+0x14)
    // +0xD0: int field (copied to node+0x18)
    // +0xD4: int field (copied to node+0x1C)
    // +0xD8: int field (copied to node+0x20)
    // +0xDC: int field (copied to node+0x24)
    // +0xE0: int field (copied to node+0x28)
    // +0xE4: int field (copied to node+0x2C)
    // +0xE8: short field (copied to node+0x30)
    // +0xEC: int field (copied to node+0x34)
    // +0xF0: int field (copied to node+0x38)
    // +0xF4: int field (copied to node+0x3C)
    // +0xF8: int field (copied to node+0x40)
    // +0xFC: int field (copied to node+0x44)
    // +0x100: int field (copied to node+0x48)
    // +0x10C: int field (copied to node+0x4C)
    // +0x110: int field (copied to node+0x50)
    // +0x114: int field (copied to node+0x54)
    // +0x118: int field (determines node+0x5A)
    // +0x120: short field (copied to node+0x58)
    // +0x108: short field (copied to node+0x5C)
};

// Structure for the allocator/pool
struct PacketAllocator {
    // +0x00: unknown
    // +0x04: pointer to current free node? (set to 0 initially)
    // +0x08: pointer to allocated node buffer? (used as node pointer)
    // +0x0C: pointer to hash table (array of 128 pointers)
    // +0x14: head of separate linked list
    // +0x18: tail of separate linked list? (set to first node)
};

// __fastcall: param_1 in ECX, param_2 in EDX, rest on stack
uint32_t __fastcall PacketManager::insertPacket(
    uint32_t callbackContext,      // param_1 (ECX) - passed to virtual call
    int** ppManager,               // param_2 (EDX) - pointer to pointer to PacketManager
    uint32_t param3,               // param_3 - short ID (used as node+0x62)
    uint32_t param4,               // param_4 - short ID (used as node+0x60)
    uint32_t param5,               // param_5 - int value (used as node+0x64)
    int* errorCode                 // param_6 - output error code
)
{
    PacketManager* manager = (PacketManager*)*ppManager;
    PacketAllocator* allocator = (PacketAllocator*)(*(int*)((uint8_t*)manager + 0x20));
    int* somePtr = *(int**)((uint8_t*)manager + 0x38);

    // Clear a field in the allocator
    *(uint32_t*)((uint8_t*)allocator + 4) = 0;

    if (somePtr == 0) {
        // No function table, report error
        reportError(param3, 0, 0, errorCode);
    } else {
        // Call virtual function at manager+0x3C
        void (*virtualFunc)(int, uint32_t, int**, uint32_t, int, int, int, uint32_t) =
            *(void (**)(int, uint32_t, int**, uint32_t, int, int, int, uint32_t))((uint8_t*)manager + 0x3C);
        virtualFunc((int)somePtr, param4, ppManager, param3, 0, 0, 3, callbackContext);
    }

    if (*errorCode != 0) {
        return 0;
    }

    // Re-fetch allocator pointer (might have changed?)
    allocator = (PacketAllocator*)(*(int*)((uint8_t*)manager + 0x20));

    // Check if we need to allocate a new node
    if (*(int*)((uint8_t*)manager + 0x10C) == 0 && *(int*)((uint8_t*)manager + 0x110) == 0) {
        int* nodePtr = allocatePacketNode(); // returns pointer to node+0x68? Actually returns base+0x68
        if (nodePtr != 0) {
            nodePtr = (int*)((uint8_t*)nodePtr + 0x68);
        }
        *(int**)((uint8_t*)allocator + 4) = nodePtr;
    }

    PacketNode* newNode = *(PacketNode**)((uint8_t*)allocator + 8);
    if (newNode == 0) {
        return 0;
    }

    // Fill node fields from parameters
    *(uint16_t*)((uint8_t*)newNode + 0x62) = (uint16_t)param3;
    *(uint16_t*)((uint8_t*)newNode + 0x60) = (uint16_t)param4;
    *(uint32_t*)((uint8_t*)newNode + 0x64) = param5;

    // Copy fields from manager template to node
    *(uint16_t*)((uint8_t*)newNode + 0x14) = *(uint16_t*)((uint8_t*)manager + 0xCC);
    *(uint32_t*)((uint8_t*)newNode + 0x18) = *(uint32_t*)((uint8_t*)manager + 0xD0);
    *(uint32_t*)((uint8_t*)newNode + 0x1C) = *(uint32_t*)((uint8_t*)manager + 0xD4);
    *(uint32_t*)((uint8_t*)newNode + 0x20) = *(uint32_t*)((uint8_t*)manager + 0xD8);
    *(uint32_t*)((uint8_t*)newNode + 0x24) = *(uint32_t*)((uint8_t*)manager + 0xDC);
    *(uint32_t*)((uint8_t*)newNode + 0x28) = *(uint32_t*)((uint8_t*)manager + 0xE0);
    *(uint32_t*)((uint8_t*)newNode + 0x2C) = *(uint32_t*)((uint8_t*)manager + 0xE4);
    *(uint16_t*)((uint8_t*)newNode + 0x30) = *(uint16_t*)((uint8_t*)manager + 0xE8);
    *(uint32_t*)((uint8_t*)newNode + 0x34) = *(uint32_t*)((uint8_t*)manager + 0xEC);
    *(uint32_t*)((uint8_t*)newNode + 0x38) = *(uint32_t*)((uint8_t*)manager + 0xF0);
    *(uint32_t*)((uint8_t*)newNode + 0x3C) = *(uint32_t*)((uint8_t*)manager + 0xF4);
    *(uint32_t*)((uint8_t*)newNode + 0x40) = *(uint32_t*)((uint8_t*)manager + 0xF8);
    *(uint32_t*)((uint8_t*)newNode + 0x44) = *(uint32_t*)((uint8_t*)manager + 0xFC);
    *(uint32_t*)((uint8_t*)newNode + 0x48) = *(uint32_t*)((uint8_t*)manager + 0x100);
    *(uint32_t*)((uint8_t*)newNode + 0x4C) = *(uint32_t*)((uint8_t*)manager + 0x10C);
    *(uint32_t*)((uint8_t*)newNode + 0x50) = *(uint32_t*)((uint8_t*)manager + 0x110);
    *(uint32_t*)((uint8_t*)newNode + 0x54) = *(uint32_t*)((uint8_t*)manager + 0x114);
    *(uint16_t*)((uint8_t*)newNode + 0x58) = *(uint16_t*)((uint8_t*)manager + 0x120);
    *(uint16_t*)((uint8_t*)newNode + 0x5C) = *(uint16_t*)((uint8_t*)manager + 0x108);

    // Set flag based on manager field
    if (*(int*)((uint8_t*)manager + 0x118) == 0) {
        *(uint16_t*)((uint8_t*)newNode + 0x5A) = 1;
    } else {
        *(uint16_t*)((uint8_t*)newNode + 0x5A) = 0;
    }

    // Compute hash bucket index: (field60*16 + field62 + field100) & 0x7F
    uint32_t hashIndex = (*(uint16_t*)((uint8_t*)newNode + 0x60) * 16 +
                          *(uint16_t*)((uint8_t*)newNode + 0x62) +
                          *(uint32_t*)((uint8_t*)newNode + 0x64)) & 0x7F;

    // Get head of hash bucket
    PacketNode** bucketHead = (PacketNode**)((uint8_t*)allocator + 0x0C) + hashIndex;
    PacketNode* oldHead = *bucketHead;

    // Insert node at head of hash bucket
    *bucketHead = newNode;
    newNode->next = oldHead; // +0x00
    newNode->prev = 0;       // +0x04? Actually +0x04 is set to oldHead? Wait, the code sets *(int*)(newNode+4)=oldHead, and *(int*)(newNode+8)=0. So offsets: +0x00=next, +0x04=prev, +0x08=something else.
    // Actually the code: *piVar1 = newNode; *(int*)(newNode+4)=oldHead; *(int*)(newNode+8)=0;
    // So piVar1 is the bucket head pointer, so newNode->next (offset 0) is set to oldHead? No, *piVar1 = newNode sets the bucket head to newNode. Then *(int*)(newNode+4)=oldHead sets the second field (offset 4) to oldHead. Then *(int*)(newNode+8)=0 sets third field to 0.
    // So the node layout: +0x00: pointer to something? Actually the bucket head is a pointer to the node, so the node's first field is not used as next? Wait, the code does:
    // piVar1 = (int*)(allocator+0x0C + hashIndex*4);
    // iVar2 = *piVar1; // old head
    // *piVar1 = newNode; // set bucket head to newNode
    // *(int*)(newNode+4) = iVar2; // set newNode+4 to old head
    // *(int*)(newNode+8) = 0; // set newNode+8 to 0
    // So the node's fields: +0x00 is not set? Actually the bucket head pointer is stored at allocator+0x0C+hashIndex*4, which is an array of pointers. So the node's first field (offset 0) is not used in the hash bucket insertion. The node's second field (offset 4) is used as a "next" pointer? Or maybe the node's first field is something else. Let's re-examine: The code sets *(int*)(newNode+4)=oldHead, so offset 4 is the link. Then offset 8 is set to 0. Then later, if oldHead != 0, it sets *(int*)(oldHead+8)=newNode. So offset 8 is a "prev" pointer. So the node has a doubly linked list with next at +4 and prev at +8. That's unusual but possible.
    // Then later, it inserts into another list: iVar2 = *(int*)(allocator+0x14); if iVar2 != 0, set *(int*)(iVar2+0x0C)=newNode. Then set allocator+0x14 = newNode, and set newNode+0x10 = iVar2, and newNode+0x0C = 0. So that list uses offsets +0x0C and +0x10 as prev/next? Actually: set newNode+0x10 = iVar2 (old head), and newNode+0x0C = 0. So +0x0C is prev, +0x10 is next. Then if allocator+0x18 == 0, set it to newNode. So that's a separate doubly linked list with head at allocator+0x14 and tail at allocator+0x18.
    // So the node has two sets of linked list pointers: one for hash bucket (offsets +4 and +8) and one for a global list (offsets +0x0C and +0x10). The first field (+0x00) is not used in these insertions? Actually the bucket head pointer is stored in the hash table array, not in the node. So the node's first field might be unused or used for something else.
    // I'll keep the code as is.

    // Insert into hash bucket (doubly linked)
    if (oldHead != 0) {
        *(PacketNode**)((uint8_t*)oldHead + 8) = newNode; // set oldHead's prev to newNode
    }

    // Insert into separate linked list (head at allocator+0x14)
    PacketNode* oldListHead = *(PacketNode**)((uint8_t*)allocator + 0x14);
    if (oldListHead != 0) {
        *(PacketNode**)((uint8_t*)oldListHead + 0x0C) = newNode; // set old head's prev to newNode
    }
    *(PacketNode**)((uint8_t*)allocator + 0x14) = newNode; // new head
    *(PacketNode**)((uint8_t*)newNode + 0x10) = oldListHead; // newNode's next
    *(PacketNode**)((uint8_t*)newNode + 0x0C) = 0; // newNode's prev

    if (*(PacketNode**)((uint8_t*)allocator + 0x18) == 0) {
        *(PacketNode**)((uint8_t*)allocator + 0x18) = newNode; // set tail if empty
    }

    return (uint32_t)newNode;
}