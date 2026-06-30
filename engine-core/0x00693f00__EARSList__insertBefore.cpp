// FUNC_NAME: EARSList::insertBefore
void __thiscall EARSList::insertBefore(SentinelNode* listHead, Node** iterator) {
    // listHead is the sentinel node, located at this+4? Actually param_1 is likely the list object, with sentinel at offset +4.
    // iterator is a pointer to a Node* variable that holds the current node pointer.
    Node* nodeToInsert = *iterator; // Node to be inserted
    *iterator = nodeToInsert->next; // Advance iterator to the node after the one being inserted (the original current node's next)
    
    Node* nextNode = nodeToInsert->next;
    if (nextNode && nextNode->isSentinelFlag == 0) { // <--- offset 0x29 is a flag (maybe isSentinel)
        nextNode->prev = reinterpret_cast<Node*>(iterator); // Set the prev of the next node to point to the iterator variable? This seems odd, but per decompilation.
    }
    nodeToInsert->prev = reinterpret_cast<Node*>(iterator[1]); // Set node's prev to the stored previous node from iterator
    // The above sets nodeToInsert->prev to whatever was at iterator[1] (the "prev" field of the iterator structure)
    
    // Check if we are inserting at the end (tail)
    Node* tailNode = listHead->prev; // listHead->prev is the tail (offset +4 from sentinel)
    if (iterator == &tailNode->next) { // Compare iterator address with tail->next? Actually decompiled: param_2 == *(int**)(*(int*)(param_1+4)+4) i.e., &tail->next?
        // This condition appears to check if iterator points to the tail node's next pointer.
        tailNode->next = nodeToInsert;
        nodeToInsert->next = reinterpret_cast<Node*>(iterator);
        iterator[1] = nodeToInsert;
        return;
    }
    
    // Otherwise, get the previous node from the iterator (stored in iterator[1])
    Node* prevNode = reinterpret_cast<Node*>(iterator[1]);
    if (iterator == &prevNode->next) { // Check if iterator points to prevNode->next
        prevNode->next = nodeToInsert;
        nodeToInsert->next = reinterpret_cast<Node*>(iterator);
        iterator[1] = nodeToInsert;
        return;
    }
    
    // Fallback: prevNode->next wasn't the target; possibly end of list?
    *prevNode = reinterpret_cast<Node*>(nodeToInsert); // This sets prevNode's first field (next?) to nodeToInsert? Unclear.
    nodeToInsert->next = reinterpret_cast<Node*>(iterator);
    iterator[1] = nodeToInsert;
    return;
}