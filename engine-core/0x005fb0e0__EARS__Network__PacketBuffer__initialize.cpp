// FUNC_NAME: EARS::Network::PacketBuffer::initialize
// Function address: 0x005fb0e0
// Reconstructed C++ for PacketBuffer (EARS engine packet buffer initializer)

class BufferManager; // forward declaration

// Represents a packet buffer object (size unknown, at least 32 bytes)
class PacketBuffer {
public:
    void** vtable;      // +0x00
    uint32_t flags;     // +0x04 (cleared to zero)
    uint32_t sizeTag;   // +0x08 (expected to be 0x10 for this path)
    uint32_t field_0c;  // +0x0C
    uint32_t data1;     // +0x10
    uint32_t data2;     // +0x14
    uint32_t data3;     // +0x18
    uint32_t data4;     // +0x1C
};

// Represents a node in a doubly linked list of buffers (12 bytes)
struct BufferNode {
    int key;      // +0x00
    BufferNode* prev; // +0x04
    PacketBuffer* buffer; // +0x08
};

// Manager class that holds allocator, free list, and head of buffer list
class BufferManager {
public:
    // +0x10: pointer to allocator vtable (first entry is allocation function)
    void** allocVtable;
    // +0x14: head of free list (or null)
    PacketBuffer* freeListHead;
    // +0x28: pointer to a structure that contains a list head (offset 0x04 is the head pointer)
    BufferNode** listHeadPtr;
};

// Global constant for output or logging (likely)
extern uint32_t DAT_01222228;

// External functions used
void FUN_00601c80(); // unknown – likely some global init or log
void FUN_005fc010(); // unknown – likely list insertion helper
void FUN_00408a00(void* param1, int param2); // debug/log function

// __thiscall: first parameter (this) is BufferManager*, second is descriptor pointer
PacketBuffer* __thiscall PacketBuffer::initialize(BufferManager* manager, void* descriptor) {
    PacketBuffer* puVar1;        // Buffer being initialized
    BufferNode* newNode;         // Newly allocated list node
    BufferNode* listHeadNode;    // Node that holds the list head
    uint32_t uVar2, uVar3, uVar4; // Data copied from descriptor
    int keyValue;                // Value from manager->listHeadPtr->field_4

    // Step 1: Locate the raw buffer inside the descriptor (offset 0x14)
    puVar1 = *(PacketBuffer**)((char*)descriptor + 0x14);
    // Record it also as the return value and for later insertion
    *(PacketBuffer**)((char*)descriptor + 0x1c) = puVar1;

    // Step 2: Validate buffer alignment and size tag
    if ( (((uint32_t)puVar1 & 0xF) == 0) && (puVar1->sizeTag == 0x10) ) {
        // Initialize the buffer object
        puVar1->flags = 0;                         // +0x04: clear flags
        puVar1->vtable = (void**)&PTR_FUN_00e40838; // +0x00: set vtable (external symbol)
        FUN_00601c80();                            // Global init (logging?)

        // Copy 4 words from descriptor+0x04 into buffer fields +0x10..+0x1C
        // This transfers metadata (e.g., size, type, etc.)
        uint32_t* src = (uint32_t*)((char*)descriptor + 0x04);
        uVar2 = src[0];
        uVar3 = src[1];
        uVar4 = src[3];
        puVar1->data1 = src[2];  // +0x18
        puVar1->data2 = uVar2;   // +0x10
        puVar1->data3 = uVar3;   // +0x14
        puVar1->data4 = uVar4;   // +0x1C

        // Step 3: Obtain key from manager's list head structure
        keyValue = *(int*)(*(int*)((char*)manager + 0x28) + 0x04);

        // Step 4: Prepare local free list or use manager's free list head
        PacketBuffer* localList[3] = {0, 0, 0}; // local stack buffer for free list head
        PacketBuffer** freeListPtr = (PacketBuffer**)((char*)manager + 0x14);
        if (*freeListPtr == 0) {
            // No free list – use local dummy
            freeListPtr = &localList[0];
        }

        // Step 5: Allocate a new BufferNode (12 bytes) via manager's allocator
        // Allocator is at offset +0x10 of manager (first entry in vtable)
        void* allocFunc = *(void**)((char*)manager + 0x10);
        newNode = (BufferNode*)(**(code**)(allocFunc))(12, freeListPtr); // size 12

        if (newNode != 0) {
            newNode->key = keyValue;          // +0x00
            newNode->prev = (BufferNode*)unaff_ESI; // +0x04 (ESI register saved earlier – likely previous node)
            newNode->buffer = puVar1;         // +0x08
        }

        // Step 6: Insert the node into the linked list (list managed by manager+0x28)
        FUN_005fc010(); // probably adjusts list pointers

        // Retrieve list head node from manager structure
        BufferNode** headPtr = *(BufferNode***)((char*)manager + 0x28);
        // Insert newNode after head node:
        *(BufferNode**)((char*)headPtr + 0x04) = newNode;      // head->next = newNode
        *(BufferNode**)((char*)newNode->prev) = newNode;        // newNode->prev->next = newNode

        // Step 7: Call debug/log function with a buffer description
        uint32_t stackVar1 = DAT_01222228;
        uint8_t stackVar2 = 0;
        PacketBuffer* stackBuf = puVar1;
        FUN_00408a00(&stackVar1, 0);

        // Return the initialized buffer pointer
        return puVar1;
    }
    return 0; // validation failed
}