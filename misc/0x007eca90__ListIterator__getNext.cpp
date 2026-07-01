// FUNC_NAME: ListIterator::getNext

// Structure for linked list iterator (likely from EARS engine)
// Offsets: +0x00 = head pointer, +0x04 = current node pointer
struct ListIterator {
    int* head;      // Pointer to list head node
    int* current;   // Pointer to current node in iteration
};

// Output structure to receive current iterator state
struct IteratorOutput {
    int* outHead;    // Copy of head
    int* outCurrent; // Copy of current node (before advance)
};

// Forward declaration (assertion function, likely debug break)
void __cdecl debugAssert(void);

// __thiscall: this == param_1 (ListIterator*)
// param_2: pointer to output structure (IteratorOutput*)
IteratorOutput* __thiscall ListIterator::getNext(ListIterator* this, IteratorOutput* out) {
    // Save current state to output
    out->outHead = this->head;
    out->outCurrent = this->current;

    // Safety checks
    if (this->head == nullptr) {
        debugAssert();          // Head must not be null
    }
    if (this->current == *(int**)((char*)this->head + 0x18)) {
        debugAssert();          // Reached sentinel or end of list (offset +0x18 in head node)
    }

    // Advance current pointer to next node
    // The current node's first field (+0x00) is assumed to be the "next" pointer
    this->current = *(int**)this->current;

    return out;
}