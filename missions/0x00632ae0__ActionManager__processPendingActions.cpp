// FUNC_NAME: ActionManager::processPendingActions

struct PendingAction {
    uint32_t flags;       // +0x08: bit0 = ? (clear), bit1 = pending (set)
    uint32_t destination; // +0x0C: target to write
    uint32_t* source;     // +0x10: pointer to data to copy
};

class ActionManager {
public:
    void __thiscall processPendingActions() {
        PendingAction* pAction = *(PendingAction**)((char*)this + 0x14); // +0x14: start of list (high address)
        PendingAction* pEnd = *(PendingAction**)((char*)this + 0x28);   // +0x28: end of list (low address)

        while (pAction != pEnd) {
            // Check if action is not completed (bit0 clear) and is pending (bit1 set)
            if ((pAction->flags & 1) == 0 && (pAction->flags & 2) != 0) {
                // Copy the value pointed to by source to destination
                pAction->destination = *(pAction->source);
            }
            // Move to previous action (list stored in decreasing address order)
            pAction = (PendingAction*)((char*)pAction - 0x18);
        }

        // Mark that pending actions have been processed
        *(uint8_t*)((char*)this + 0x32) = 1;
    }
};