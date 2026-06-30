// FUNC_NAME: Iterator::advance

// Function address: 0x0043b340
// Role: Advances an iterator to the next element. The iterator supports two modes:
//   - Array mode (if first byte non-zero): increments a 4-byte index (offset +4) by 4.
//   - Linked list mode (if first byte zero): traverses a linked list where each node stores
//     a self-relative offset to the next node at offset +0, a 4-byte type at +4, and a 2-byte
//     subtype at +6. Special type values (0x20000000, 0x40000000, 0x80000000) or a type whose
//     lower 16 bits (or full type if subtype != 0x25e3) are zero cause the iterator pointer
//     (offset +0xC) to be nulled, marking the end of iteration.

struct ListNode {
    int nextOffset;   // +0: self-relative offset to next node (offset from this address)
    uint type;        // +4: 32-bit type field
    short subtype;    // +6: 16-bit subtype
};

struct Iterator {
    char mode;        // +0: 0 = linked list, non-zero = array
    int arrayIndex;   // +4: current index in array (incremented by 4 each step)
    ListNode* current; // +0xC: pointer to current node (used only in list mode)
};

void __fastcall Iterator::advance() {
    if (this->mode != 0) {
        // Array mode: advance by 4 bytes (size of one element)
        this->arrayIndex += 4;
        return;
    }

    // Linked list mode: compute next node using self-relative offset
    ListNode* node = this->current; // current node pointer
    int offset = *(int*)node;       // node->nextOffset
    ListNode* nextNode = (ListNode*)((int)node + offset);
    this->current = nextNode;

    uint type = nextNode->type;
    if (type != 0x20000000 && type != 0x40000000 && type != 0x80000000) {
        uint check = type & 0xFFFF; // lower 16 bits
        if (nextNode->subtype != 0x25e3) {
            check = type; // use full type instead of lower bits
        }
        if (check == 0) {
            // Not a terminating node, keep iterator valid
            return;
        }
    }

    // Terminating node encountered: invalidate the iterator by clearing the node pointer
    this->current = nullptr; // clears bytes at this+0xC through this+0xF
}