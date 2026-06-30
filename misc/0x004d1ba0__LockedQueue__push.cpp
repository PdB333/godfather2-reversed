// FUNC_NAME: LockedQueue::push
bool LockedQueue::push(int item)
{
    bool success = false;
    EnterCriticalSection((LPCRITICAL_SECTION)(this + 4)); // +0x4: critical section
    
    int count = this[3]; // +0xC: current count
    int capacity = this[1]; // +0x4: max capacity
    if (count < capacity) {
        int head = this[2]; // +0x8: head index
        int index = head + count;
        this[3] = count + 1;
        if (capacity <= index) {
            index = index - capacity;
        }
        *(int *)(this[0] + index * 4) = item; // +0x0: buffer pointer
        success = true;
    }
    
    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 4));
    return success;
}