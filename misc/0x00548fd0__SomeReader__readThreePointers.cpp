// FUNC_NAME: SomeReader::readThreePointers
void SomeReader::readThreePointers() {
    // Initialize hash reader or context (0xd891b9ac is likely a type hash)
    initHash(0xd891b9ac); // FUN_0043aff0

    uint currentIndex = index_; // local_58
    while (true) {
        bool done;
        if (isDense_) {       // local_64 == 0? Actually local_64 is the flag, 0 means linked list, nonzero means dense
            done = (currentIndex == count_); // local_54
        } else {
            done = (*listNode_ == 0); // local_8 is a pointer to node, dereference to check end
        }
        if (done) break;

        void** ppEntry;
        if (isDense_) {
            ppEntry = &denseEntry_; // local_50
        } else {
            ppEntry = listNode_;    // local_8
        }

        // Read type field: if a short at +6 equals 0x25e3, treat as short pointer; else as pointer
        void* pValue;
        if (*(short*)((char*)ppEntry + 6) == 0x25e3) {
            pValue = (void*)(uint)*(unsigned short*)(ppEntry[1]);   // offset 4
        } else {
            pValue = ppEntry[1];
        }

        // Set one of three fields based on pValue (0, 1, 2)
        if (pValue == 0) {
            *(void**)(this + 0x08) = ppEntry[2]; // offset 8
        } else if (pValue == (void*)1) {
            *(void**)(this + 0x0C) = ppEntry[2]; // offset 12
        } else if (pValue == (void*)2) {
            *(void**)(this + 0x10) = ppEntry[2]; // offset 16
        }

        // Advance to next entry
        if (isDense_) {
            currentIndex++;
            if (currentIndex != count_) {
                unsigned short bitIdx = (unsigned short)currentIndex;
                // Check bitmask at (currentIndex>>3) in the bitfield buffer
                if ((bitfieldBase_[currentIndex >> 3] & (1 << (currentIndex & 7))) == 0) {
                    denseEntry_ = denseDataPos_; // local_5c
                    entryData_ = *denseDataPos_;
                    denseDataPos_++;
                } else {
                    denseEntry_ = 0;
                    entryData_ = 0;
                }
            }
        } else {
            // Linked list traversal with size stored at offset 0 of each node
            if ((int)currentIndex < 0) {
                listNode_ = (void**)((int)listNode_ + (int)*listNode_); // advance by node size
                advanceList(); // FUN_0043b140
                currentIndex = index_; // reload from member
            } else if ((int)currentIndex < (int)(count_ - 1)) {
                listNode_ = (void**)((int)listNode_ + (int)*listNode_);
                index_ = currentIndex + 1;
                currentIndex = index_;
            } else {
                listNode_ = (void**)0x1163cf8; // sentinel / null
            }
        }
    }
}