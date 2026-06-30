// FUNC_NAME: processNextQueuedItem
void __thiscall processNextQueuedItem(void* thisPtr) {
    // Read pointer to an internal queue (offset 0x184 from this)
    int* queuePtr = *(int**)((char*)thisPtr + 0x184);
    // Attempt to dequeue the next available index
    int index = dequeueNextIndex(&queuePtr);
    // If a valid index is returned (>= 0), process it
    if (index >= 0) {
        processIndex(index);
    }
}