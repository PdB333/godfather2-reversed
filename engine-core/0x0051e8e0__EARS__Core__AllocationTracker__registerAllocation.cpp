// FUNC_NAME: EARS::Core::AllocationTracker::registerAllocation
// Address: 0x0051e8e0
// Registers a new allocation node in a global linked list, using a vtable to retrieve size and constructor.
// The node is inserted at the head of the list, and a global counter is incremented.

#include <cstddef>

// External memory allocator (likely custom or operator new)
extern void* __cdecl allocMemory(size_t size);

// VTable structure for the class being registered
struct ClassVTable {
    // +0x00: probably another function pointer or virtual destructor
    size_t (*getAllocSize)();          // +0x04: returns size needed for one instance
    // +0x08: unknown
    // +0x0C: unknown
    void (*construct)();              // +0x10: placement constructor or initializer
};

// Global variables from the data section
extern ClassVTable* g_classVtablePtr;    // PTR_PTR_011252d8: pointer to class vtable
extern void* g_currentAllocation;       // _DAT_011252e0: pointer to newly allocated memory
extern void* g_previousNode;            // _DAT_011252dc: previous head of the list
extern int32_t g_currentNodeIndex;      // _DAT_011252e4: index of this node

extern void* g_headNode;                // DAT_012058ec: head of the global allocation list
extern int32_t g_nodeCounter;           // DAT_012058f8: global allocation counter

// The function
void EARS::Core::AllocationTracker::registerAllocation() {
    // 1. Obtain the size of the object to allocate from the class vtable
    size_t allocSize = g_classVtablePtr->getAllocSize();

    // 2. Allocate memory for the object
    g_currentAllocation = allocMemory(allocSize);

    // 3. Call the class constructor/initializer via vtable
    g_classVtablePtr->construct();

    // 4. Link the node into the global list (insert at head)
    // Save the current head as previous node
    g_previousNode = g_headNode;      // +0x94: store old head

    // Increment the global node counter
    g_nodeCounter++;                  // +0x98: counter increment

    // Update the head to point to this node (the vtable pointer location)
    g_headNode = &g_classVtablePtr;  // +0x9C: head now points to this registration

    // Record the current counter value as this node's index
    g_currentNodeIndex = g_nodeCounter; // +0xA0: store index
}