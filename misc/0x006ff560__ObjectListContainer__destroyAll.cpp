// FUNC_NAME: ObjectListContainer::destroyAll
struct ObjectListNode {
    int* object;       // +0x00: pointer to object (used as 'this' in virtual call)
    ObjectListNode* next; // +0x04
};

class ObjectListContainer {
public:
    ObjectListNode* head; // +0x00
    char pad_04[8];       // +0x04 to +0x0B (unknown)
    int* singleChild;     // +0x0C: single child pointer (can be 0)
    void** methodTable;   // +0x10: pointer to a table of function pointers (not standard vtable)
    
    // Virtual function table indices for methodTable:
    // index 1 (offset 4): void releaseChild(ObjectListNode* child, bool flag)
    // index 3 (offset 12): void finalCleanup()
    
    void destroyAll() {
        // Iterate through the linked list and release each child
        ObjectListNode* current = head;
        while (current != nullptr) {
            ObjectListNode* next = current->next;
            // Call the virtual method at methodTable[1] (offset 4) for each child
            auto releaseChild = reinterpret_cast<void(__thiscall*)(ObjectListNode*, bool)>(methodTable[1]);
            releaseChild(current, false); // false = maybe 'delete' flag?
            current = next;
        }
        
        // Release the single child if present
        if (singleChild != nullptr) {
            auto releaseChild = reinterpret_cast<void(__thiscall*)(ObjectListNode*, bool)>(methodTable[1]);
            // Note: singleChild is not an ObjectListNode, but it is the pointer passed as 'this'
            // It is cast to ObjectListNode* for the call; the method likely expects a pointer to the child object itself
            // This works because the child object has the same pointer interface as the node's object pointer
            releaseChild(reinterpret_cast<ObjectListNode*>(singleChild), false);
        }
        
        // Finally, call the cleanup method at methodTable[3] (offset 12)
        auto finalCleanup = reinterpret_cast<void(__thiscall*)()>(methodTable[3]);
        finalCleanup();
    }
};