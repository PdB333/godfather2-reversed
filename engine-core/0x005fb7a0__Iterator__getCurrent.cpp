// FUNC_NAME: Iterator::getCurrent

#include <cassert>

// Iterator state: [0x00] head pointer, [0x04] current node pointer
int __fastcall Iterator__getCurrent(int* thisIter)
{
    // Check that the head is valid
    if (thisIter[0] == 0) {
        // head is null, assertion failure
        assert(!"Iterator head is null");
    }
    // Check that current is not the sentinel (stored at head+0x18)
    if (thisIter[1] == *(int*)(thisIter[0] + 0x18)) {
        // current equals sentinel, assertion failure
        assert(!"Iterator at end (sentinel)");
    }
    // Return pointer to data inside the node (node + 8)
    return thisIter[1] + 8;
}