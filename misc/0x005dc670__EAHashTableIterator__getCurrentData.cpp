// FUNC_NAME: EAHashTableIterator::getCurrentData
// Address: 0x005dc670
// Class: likely EAHashTableIterator or similar iterator for hash table/array
// This method retrieves the data pointer at the current iterator position, with debug validation.
// The iterator owns a pointer to a data block (at this+0x08) which has a current index at +0x1c.
// The helper function (FUN_005def60) retrieves the current node (local_10) and index (local_c) from an internal state.
// If the index matches, it returns the data pointer from local_c+0x10, otherwise returns 0.

void* __thiscall EAHashTableIterator::getCurrentData(void* thisPtr) {
    // thisPtr is the iterator object (implicit this)
    int local_10;  // node pointer or key? (output from helper)
    int local_c;   // index value (output from helper)
    
    int* dataBlock = *(int**)((char*)thisPtr + 0x08); // +0x08: pointer to internal data block (hash table array or node list)
    if (dataBlock != nullptr) {
        // Call helper to get current node and index from the data block
        // The helper takes a reference to a struct on the stack (local_10 and local_c as a pair)
        // It's likely a function like getCurrentNode(dataBlock, &local_10, &local_c)
        // but Ghidra shows only one parameter (address of locals). We'll treat it as a function that reads internal state.
        getCurrentNodeAndIndex(&local_10); // helper fills local_10 and local_c (stack parameters)
        
        int currentIndex = dataBlock[0x1c / sizeof(int)]; // +0x1c: current index field
        if ((local_10 == 0) || (local_10 != (int)dataBlock)) {
            assertFail(); // FUN_00b97aea - iterator is invalid (data block mismatch)
        }
        if (local_c != currentIndex) {
            if (local_10 == 0) {
                assertFail(); // FUN_00b97aea - node is null
            }
            if (local_c == *(int*)(local_10 + 0x1c)) {
                assertFail(); // FUN_00b97aea - index mismatch again? (debug check)
            }
            // Return pointer at local_c+0x10 (data field)
            return (void*)*(int*)(local_c + 0x10);
        }
    }
    return nullptr; // no data block or index match
}

// Note: The exact signature of the helper function is unknown, but based on calling convention it likely modifies the stack locals.
// The assertFail function (FUN_00b97aea) is a debug assertion that presumably terminates or logs error.