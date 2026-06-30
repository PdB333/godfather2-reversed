// FUN_NAME: ListClass::contains
// Function address: 0x006aed40
// Role: Checks if a node with a matching key exists in the intrusive circular singly-linked list.
// The list uses an embedded sentinel node (at this+0x154) with its next pointer stored at this+0x1A4.
// Nodes have a next pointer at offset 0x50.

bool __thiscall ListClass::contains(uint key) {
    // Offset of sentinel node within this object
    Node* sentinel = reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(this) + 0x154);
    
    // Sentinal's next pointer (offset 0x1A4) points to the first node's next field.
    // To get the actual node base, subtract 0x50.
    Node* head = *reinterpret_cast<Node**>(reinterpret_cast<uintptr_t>(this) + 0x1A4);
    Node* current;
    if (head == nullptr) {
        current = nullptr;
    } else {
        current = reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(head) - 0x50);
    }
    
    // If current is back to sentinel, list is empty (or we wrapped around)
    if (current == sentinel) {
        return false;
    }
    
    do {
        // The function FUN_006b7660 is likely Node::matches(key) using the current node as this
        if (nodeMatchesKey(static_cast<void*>(current), key)) {
            return true;
        }
        
        // Advance to next node
        Node* next = *reinterpret_cast<Node**>(reinterpret_cast<uintptr_t>(current) + 0x50);
        if (next == nullptr) {
            current = nullptr;
        } else {
            current = reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(next) - 0x50);
        }
    } while (current != sentinel);
    
    return false;
}