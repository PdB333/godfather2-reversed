// FUNC_NAME: CInventoryManager::updatePendingItemActivation
// Function address: 0x006b9e60
// This function processes pending item activation requests using a item proxy factory.
// It iterates over a global item manager's list and applies effects if conditions are met.
// The remainingCount parameter limits the number of activations per call.

void __thiscall CInventoryManager::updatePendingItemActivation(uint &actionId, int unused, int *remainingCount)
{
    int *proxy;
    bool isValid;
    int itemCount;
    int *itemManager;
    uint idx;

    // Check if the manager's flags indicate that updates are allowed (bit 0 of +0x80)
    if ((this->flags & 1) != 0) {
        itemManager = getGlobalItemManager();
        // If a global item manager exists and the remainingCount pointer is initially 0, set it to 1
        if (*(int *)(itemManager + 4) != 0 && *remainingCount == 0) {
            *remainingCount = 1;
        }
        idx = 0;
        if (*(int *)(itemManager + 4) != 0) {
            do {
                // If remainingCount drops to 0, stop processing
                if (*remainingCount == 0) {
                    return;
                }
                // Create a proxy object for the current item (size 1 indicates a lightweight proxy)
                proxy = (int *)createItemProxy(1);
                if (proxy != (int *)0x0) {
                    // Call virtual function vtable+0x10 with a hash to resolve the action ID
                    actionId = 0;
                    isValid = (**(code **)(*proxy + 0x10))(0xd7e44d6a, &actionId);
                    // If the action ID is non-zero after the call, proceed to validation
                    if (isValid && isItemValid()) {
                        applyItemEffect(&actionId);
                        *remainingCount = *remainingCount - 1;
                    }
                }
                idx++;
            } while (idx < *(uint *)(itemManager + 4));
        }
    }
    return;
}