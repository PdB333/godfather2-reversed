// FUNC_NAME: TickableManager::updateAll
void TickableManager::updateAll() {
    // Acquire global lock before iterating registered tickable objects
    lock();

    // Iterate singly linked list starting from global head (DAT_011a0ef0)
    // Node structure: unknown fields, next pointer at offset +0x4
    for (int* node = g_pHead; node != nullptr; node = *(int**)(node + 4)) {
        // Call update method for each registered object (FUN_005f1ef0)
        updateNode(node);
    }

    // Release lock after iteration
    unlock();
}