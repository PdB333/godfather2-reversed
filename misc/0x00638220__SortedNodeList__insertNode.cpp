// FUNC_NAME: SortedNodeList::insertNode
// Function at 0x00638220 - Inserts a node with given key into sorted singly linked list.
// Class member at +0x48 is head pointer; +0x10 points to an allocator/counter structure.

struct SortedNode {
    SortedNode* next;       // +0x00: next node in list
    uint8_t  type;          // +0x04: always 10
    uint8_t  flags;         // +0x05: always 1
    uint16_t pad;           // +0x06: alignment padding
    uint32_t key;           // +0x08: sort key (ascending)
    uint8_t  extra[12];     // +0x0C: remaining 12 bytes (total size 0x14)
};

// Global fallback node for when 'this' is null (emergency allocation)
static SortedNode g_staticNode;

class SortedNodeList {
public:
    SortedNode* head;       // +0x48: pointer to list head
    void*       allocator;  // +0x10: pointer to allocator tracking (byte count at offset 0x24)
    
    // __thiscall
    void insertNode(uint32_t key) {
        SortedNode** prevPtr = &head;      // puVar3
        SortedNode*  curr    = head;       // puVar4
        
        // Traverse sorted list (ascending by key)
        while (curr != nullptr && key >= curr->key) {
            if (curr->key == key) {
                return; // node already exists
            }
            prevPtr = &curr->next;
            curr    = curr->next;
        }
        
        // Allocate new node
        SortedNode* newNode = (SortedNode*)malloc(0x14); // DAT_012059dc is malloc
        if (newNode != nullptr) {
            // Update allocator counter if this object exists
            if (this != nullptr) {
                int* counter = (int*)(*(int*)(this->allocator) + 0x24);
                *counter += 0x14;
            }
            newNode->type  = 10;
            newNode->flags = 1;
            newNode->key   = key;
            // Insert into list
            newNode->next = *prevPtr;
            *prevPtr      = newNode;
            return;
        }
        
        // Fallback: if allocator fails
        if (this != nullptr) {
            // Call some error handler
            FUN_00635a80();
            return;
        }
        
        // Use static node (no 'this' object)
        g_staticNode.key   = key;
        g_staticNode.type  = 10;
        g_staticNode.flags = 1;
        g_staticNode.next  = *prevPtr;
        *prevPtr           = nullptr; // disconnect rest of list
        return;
    }
};