// FUNC_NAME: EntityManager::setEntityFlagByID

#include <cstdint>

// Forward declaration of assert function (debug build)
extern void __fastcall assert_failed(const char* msg);

#define ASSERT(cond) do { if(!(cond)) assert_failed(""); } while(0)

class EntityManager {
public:
    // Structure: Manager contains a list head pointer at +0x08
    // The list is a doubly linked list of node structures
    struct ListNode {
        ListNode* prev;      // +0x00
        ListNode* next;      // +0x04
        // ... other fields
        void* data;          // +0x0C? Actually from code: +0x10 is a pointer to entity data
    };

    struct NodeData {
        // ... fields
        uint32_t entityId;   // +0x2B4
        uint8_t flag;        // +0x298
    };

    // Assuming the manager has a list head pointer at offset +0x08
    ListNode* listHead; // offset +0x08
    // Then from list head, offset +0x1C is a pointer to the sentinel or first node?
    // Actually: iVar1 = *(int *)(param_1 + 8); -> listHead
    // iVar2 = **(int **)(iVar1 + 0x1c); -> seems like listHead->+0x1c is a pointer to a pointer to current node?
    // But the iteration pattern is weird. Let's assume a standard circular linked list:
    // listHead is a sentinel node; its next pointer at +0x04 points to first real node.
    // But the code uses +0x1c. Possibly it's a different structure.
    // For readability, we'll abstract with an iterator pattern.
    
    // Helper to get next node (calls FUN_005e09e0)
    ListNode* getNextNode(ListNode* node);

    // Internal function
    bool setFlagForEntity(uint32_t entityId, bool setFlag) {
        if (entityId == 0) {
            return false;
        }

        // Get the head of the list
        ListNode* list = *(ListNode**)(reinterpret_cast<uint8_t*>(this) + 0x08);
        // The list+0x1c might point to a doubly-linked list node?
        // Actually, the code does: iVar2 = **(int **)(iVar1 + 0x1c);
        // That suggests list+0x1c is a pointer to a pointer (maybe an iterator variable)
        // Let's assume it's a pointer to the current node pointer in the list structure.
        ListNode** currentPtr = reinterpret_cast<ListNode**>(reinterpret_cast<uint8_t*>(list) + 0x1C);
        ListNode* current = *currentPtr;
        ListNode* sentinel = current; // Actually iVar3 = sentinel value from list

        // Sentinel check from code: iVar3 = *(int *)(*(int *)(param_1 + 8) + 0x1c);
        // This reads the same pointer value stored at list+0x1c (the double-dereference yields the pointer itself)
        // So sentinel is the same as *currentPtr? That seems odd.
        // To match original logic, we'll use a loop that compares current with the pointer stored at list+0x1c.
        // But it's convoluted. Simpler: iterate through list nodes.
        
        // Let's rewrite using the same variable names as decompiled for clarity,
        // but with meaningful names.
        ListNode* node = *(ListNode**)(reinterpret_cast<uint8_t*>(list) + 0x1C);
        ListNode* sentinelNode = *(ListNode**)(reinterpret_cast<uint8_t*>(list) + 0x1C); // Actually reads double pointer and then value?
        
        // Actually, reading the decompiled again:
        // iVar1 = *(int *)(param_1 + 8); -> list
        // iVar2 = **(int **)(iVar1 + 0x1c); -> first node (node)
        // iVar3 = *(int *)(*(int *)(param_1 + 8) + 0x1c); -> this is just the pointer value at list+0x1c (which is a ListNode*), not double dereference
        // So iVar3 = the value stored at list+0x1c (which is a ListNode*)
        // iVar2 = the value pointed to by that pointer (another ListNode*)???
        // Wait: iVar2 = **(int **)(iVar1 + 0x1c) means: (iVar1+0x1c) is a pointer to a pointer, so read pointer, then dereference that.
        // iVar3 = *(int *)(*(int *)(...)+0x1c) means: first read pointer at (param_1+8)=list, then read *(list+0x1c) which gives a ListNode*, assign to iVar3.
        // So iVar2 is the node pointed to by the pointer at list+0x1c? Actually list+0x1c is a ListNode* (call it headPtr).
        // Then *headPtr gives the first node? Or headPtr is a pointer to a node that contains a pointer to the next? This is messy.
        
        // Given the assert checks: if (iVar1 != 0) and iVar1 != *(int *)(param_1 + 8) -> that means iVar1 is non-null and equals the list pointer? Actually it checks if (iVar1 == 0) || (iVar1 != *(int *)(param_1 + 8)) -> that fails if iVar1 is not the list pointer? That suggests iVar1 is supposed to be list, so if it changes, assert.
        // So iVar1 is initially set to list, then later they check if iVar1 == 0 or iVar1 != list -> assert.
        // This implies iVar1 stays as list and they don't modify it, but they compare iVar2 to iVar3.
        // iVar2 is a node, iVar3 is the sentinel value (which is the pointer stored at list+0x1c).
        // The loop condition: if (iVar2 == iVar3) break; So when current node equals the sentinel, end.
        // The sentinel is likely a circular list head.
        
        // So reinterpret:
        ListNode* list = *(ListNode**)(reinterpret_cast<uint8_t*>(this) + 0x08);
        ListNode* sentinel = *(ListNode**)(reinterpret_cast<uint8_t*>(list) + 0x1C); // This is a pointer to a node (maybe the list head sentinel)
        ListNode* current = **(ListNode***)(reinterpret_cast<uint8_t*>(list) + 0x1C); // The actual first node (or current iterator)
        
        // But then later they do: if (iVar2 == *(int *)(iVar1 + 0x1c)) { assert; } That means if current equals the sentinel pointer (i.e., empty list?) they assert.
        // So the sentinel is not a node but a pointer to a special marker.
        // Actually the code checks: if (iVar1 == 0) { assert; } if (iVar2 == *(int *)(iVar1 + 0x1c)) { assert; } So they check if iterating over the list and node is the head/tail.
        // This is likely a custom linked list with a sentinel node. The sentinel node's address is stored at list+0x1c.
        // The first real node is ** at list+0x1c (double dereference). So sentinel = *(list+0x1c); first = *sentinel? Actually no.
        // Let's just use a simplified iteration:
        
        // We'll assume there's a function to get the next node and we'll iterate until we loop back.
        // We'll not replicate the exact assert checks for readability, but we'll include them.
        
        // Placeholder: actual iteration uses a while loop with a break on sentinel match.
        // For cleanliness, I'll implement as a for loop over nodes.
        
        // Note: The original code modifies the list during iteration? It doesn't appear to.
        // Also, the function calls FUN_005e09e0 after each check - presumably advances to next node.
        
        ListNode* node = current;
        while (true) {
            // Assert valid pointers
            if (node == nullptr || node != list) {
                ASSERT(false && "corrupted list");
            }
            // Check if we've reached sentinel
            if (node == sentinel) {
                break;
            }
            // Assert node is not sentinel (since we already break)
            if (node == sentinel) {
                ASSERT(false && "node is sentinel");
            }
            
            // Get entity data from node
            NodeData* entity = reinterpret_cast<NodeData*>(node->data); // node+0x10 is data pointer
            if (entity->entityId == entityId) {
                // Set flag
                entity->flag = (setFlag ? 1 : 0);
            }
            
            // Advance to next node (function call)
            node = getNextNode(node);
        }
        
        return true;
    }
};

// Stub for getNextNode (implementation elsewhere)
EntityManager::ListNode* EntityManager::getNextNode(ListNode* node) {
    // This would be implemented in the engine, likely returns node->next
    // But the original code calls FUN_005e09e0 which might do more.
    // For now, assume it returns the next node in the list.
    return node->next;
}