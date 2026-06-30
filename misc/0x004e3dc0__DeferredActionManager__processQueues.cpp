// FUNC_NAME: DeferredActionManager::processQueues
void DeferredActionManager::processQueues() {
    int count = g_deferredSlotCount; // DAT_011946b4
    if (count <= 0) return;

    for (int i = 0; i < count; i++) {
        DeferredSlot* slot = g_deferredSlots[i]; // DAT_011946b8[i]
        DeferredNode* node = slot->activeQueue; // +0x24
        int currentCount = count;

        while (node != nullptr) {
            // Assign global count to currentCount (preserve for condition)
            g_deferredSlotCount = currentCount;
            DeferredNode* next = node->next; // node+0x8
            slot->activeQueue = next;

            // Call virtual function at vtable index 1 (offset 4)
            void (*executeFunc)() = (void(*)())(node->vtable[1]);
            executeFunc();

            // Re-read global count (may have been altered by callback)
            currentCount = g_deferredSlotCount;
            node = slot->activeQueue;
        }

        // Shift pending queues: pending2 becomes active, pending1 becomes pending2, clear pending1
        slot->activeQueue = slot->pending2Queue; // +0x20 -> +0x24
        slot->pending2Queue = slot->pending1Queue; // +0x1c -> +0x20
        slot->pending1Queue = nullptr; // +0x1c = 0
    }
}