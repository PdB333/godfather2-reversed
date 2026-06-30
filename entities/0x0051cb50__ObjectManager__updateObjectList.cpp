// FUNC_NAME: ObjectManager::updateObjectList
// Address: 0x0051cb50
// Role: Iterates through a linked list of simulation nodes (objects), optionally processing a specific node based on a pointer argument stored in EDI.
//        If argument is nullptr (0), processes all nodes; otherwise, only processes the node whose owner container matches the argument.
//        Flags are modified and a sub-function (processNode) is called for qualifying nodes.

#include <cstdint>

// Forward declaration
void processNode(ObjectNode* node); // FUN_0051b0b0

// Global linked list head for simulation nodes
extern ObjectNode* g_objectNodeListHead; // DAT_01205514

// Structure for intrusive list node embedded in larger objects (e.g., at offset 0x48)
struct ObjectNode {
    uint32_t flags;          // +0x0C: Various flags (bits: 0 = active? 16,19,20,31 used)
    void*    parentPtr;      // +0x10: Pointer to a parent structure (has flags at +0x14 e.g., 0x20000000 bit)
    ObjectNode* next;        // +0x14: Next node in linked list
    // ... other fields ...
    void*    ownerPtr;       // +0xC4: Pointer to the owning container object (if non-null, subtract 0x48 to get container start)
};

// Updates simulation nodes based on an optional filter.
// The parameter "containerFilter" is passed via EDI (not captured in standard signature).
void ObjectManager::updateObjectList(void* containerFilter) {
    ObjectNode* currentNode = g_objectNodeListHead;
    if (currentNode == nullptr) {
        return;
    }

    do {
        // Determine whether to process this node
        if (containerFilter == nullptr) {
            // Process all nodes
            goto processNodeLabel;
        } else {
            // Compute the container start from the node's owner pointer
            // ownerPtr points to something inside the container; subtract 0x48 to get container base
            void* containerBase = (currentNode->ownerPtr != nullptr) 
                ? static_cast<uint8_t*>(currentNode->ownerPtr) - 0x48 
                : nullptr;
            if (containerFilter == containerBase) {
                goto processNodeLabel;
            }
        }

        // Skip to next node
        currentNode = currentNode->next;
        continue;

processNodeLabel:
        // Clear bit 20 in flags (0x00100000)
        currentNode->flags &= 0xffefffff;

        // Check if bit 19 (0x80000) is set
        uint32_t currentFlags = currentNode->flags;
        if (currentFlags & 0x80000) {
            // Clear bit 19
            currentNode->flags = currentFlags & 0xfff7ffff;

            // If bit 0 is set AND the parent's flags (at +0x14) have bit 29 (0x20000000) set,
            // then set bit 31 (0x80000000) and also ensure bit 19 remains cleared.
            if ((currentFlags & 1) && 
                (*(uint32_t*)((uint8_t*)currentNode->parentPtr + 0x14) & 0x20000000)) {
                currentNode->flags = currentNode->flags & 0xfff7ffff | 0x80000000;
            }

            // Call the node processing function
            processNode(currentNode);
        }

        // Move to next node
        currentNode = currentNode->next;
    } while (currentNode != nullptr);
}