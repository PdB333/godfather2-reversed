// FUNC_NAME: TaskManager::processActiveTasks
// Reconstructed from 0x005dc2f0
// Iterates over a list of tasks in a container, processing each one.
// Container structure (at this+0x08) has:
//   +0x1c: pointer to list head (sentinel node)
//   +0x20: count of active tasks (decremented during processing)
// Task node has a field at offset 16 (likely next pointer).

bool __thiscall TaskManager::processActiveTasks(int this_ptr) {
    int containerPtr = *(int*)(this_ptr + 8);
    bool result = false;

    if (containerPtr != 0) {
        int activeCount = *(int*)(containerPtr + 0x20);

        while (activeCount != 0) {
            // Get first node from the list (head->next)
            int headPtr = *(int*)(containerPtr + 0x1c);
            int currentNode = *(int*)headPtr;  // head->next
            if (currentNode == headPtr) {
                // Empty list with nonzero count – assertion/error
                FUN_00b97aea();
            }

            // Read next pointer from current node (offset 16)
            int nextNode = *(int*)(currentNode + 16);

            byte localBuf[8]; // temporary buffer
            FUN_005dec30(*(int*)(this_ptr + 8), localBuf, containerPtr, currentNode);

            if (nextNode != 0) {
                // Reference counting on the next node
                FUN_005dcdc0();
                FUN_009c8eb0(nextNode);
            }

            // Re-read container and count (may have changed during processing)
            containerPtr = *(int*)(this_ptr + 8);
            activeCount = *(int*)(containerPtr + 0x20);
        }
        result = true;
    }

    FUN_005de360(); // cleanup / sync
    // Call virtual method on sub-object at this+0x10 (vtable index 1)
    (*(void (**)(void))(*((int*)(this_ptr + 0x10)) + 4))();
    return result;
}