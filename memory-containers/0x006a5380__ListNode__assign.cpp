// FUNC_NAME: ListNode::assign
int* __thiscall ListNode::assign(int* thisPtr, int* other) {
    if (thisPtr != other) {
        int data = *other;
        if (*thisPtr != data) {
            if (*thisPtr != 0) {
                // Release current data (likely decrement refcount or free)
                FUN_004daf90(thisPtr);
            }
            *thisPtr = data;
            if (data != 0) {
                // Update doubly linked list: set this->prev = data->prev
                thisPtr[1] = *(int*)(data + 4);
                // Set data->prev = this
                *(int**)(data + 4) = thisPtr;
            }
        }
    }
    return thisPtr;
}