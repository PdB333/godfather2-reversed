// FUNC_NAME: Container::addNodeFromObject

void __thiscall Container::addNodeFromObject(int thisPtr, void* objectPtr)
{
    // objectPtr is a pointer to an object that has an embedded Node at offset 0x48 (Node::Node)
    struct Node {
        int field_0;     // +0x00 usually next or key
        int field_4;     // +0x04 next pointer or flags
    };
    
    Node* node;
    if (objectPtr == nullptr) {
        node = nullptr;
    } else {
        node = (Node*)((char*)objectPtr + 0x48); // embedded node at +0x48
    }
    
    int savedNext = 0;
    if (node != nullptr) {
        savedNext = node->field_4;   // save current next
        node->field_4 = (int)&node;  // point back to itself? Possibly for temporary linking
    }
    
    // Search an array of key-value pairs stored at this+0xf0 (entries) and this+0xf4 (count)
    // The array stores pairs of (Node*, value) where each pair is 8 bytes.
    uint count = *(uint*)(thisPtr + 0xf4);
    if (count != 0) {
        int* entries = *(int**)(thisPtr + 0xf0);
        uint idx = 0;
        do {
            if (entries[0] == (int)node) { // check if node already exists
                if (idx != 0xffffffff) goto found;
                break;
            }
            idx++;
            entries += 2; // next pair
        } while (idx < count);
    }
    
    // If not found, call a function to add this node entry
    // FUN_006b44e0(&node) likely inserts node into the map
    Container_addEntry(thisPtr, &node);
    
found:
    if (node != nullptr) {
        // FUN_004daf90(&node) - restore or cleanup node's next pointer?
        Container_restoreNode(&node);
    }
    return;
}