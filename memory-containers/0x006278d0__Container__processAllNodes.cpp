// FUNC_NAME: Container::processAllNodes
void Container::processAllNodes(void) {
    // Get the internal data block and its list iterator
    // this + 0x10 points to an internal structure (e.g., m_pInternalData)
    // That internal structure + 0x3c points to the iterator (m_pIterator)
    Iterator* iter = *(Iterator**)(*(int*)(this + 0x10) + 0x3c);
    
    // Initialize external resources
    FUN_006382a0(); // e.g., some global setup
    FUN_006266e0(iter); // e.g., reset iterator
    
    // Clear iterator flag at +0x54
    iter->field_0x54 = 0;
    
    // Process all nodes: loop continues as long as the callback returns non-zero
    do {
        // Reset current pointer to head
        iter->current = iter->head;                     // +0x14 = current, +0x28 = head
        // Read the node value from head (dereference twice)
        int nodeValue = *(*iter->head);                 // first element value
        iter->firstData  = nodeValue;                   // +0x8
        iter->secondData = nodeValue;                   // +0xc
        iter->someFlag   = 0;                           // +0x2e (set to 0)
        
        // Process the current node and advance head
        int result = FUN_00635ab0(iter, FUN_006278c0, 0);
    } while (result != 0);
    
    // Final cleanup
    FUN_006276b0(); // e.g., release resources
}