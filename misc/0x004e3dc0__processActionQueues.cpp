// FUNC_NAME: processActionQueues
// Function at 0x004e3dc0: Processes all action queues for registered managers.
// Each manager has three list slots (current, next, future) for pending actions.
// Actions are linked list nodes with a vtable; the second virtual function is called.
// After processing current, the slots are shifted: current = next, next = future, future = null.

struct ActionNode {
    void** vtable; // +0x00
    // +0x04: unknown (maybe data)
    ActionNode* next; // +0x08 (piVar3[2])
};

struct ActionManager {
    void* unknown_0x00[7]; // +0x00 to +0x1b (unused here)
    ActionNode* futureList; // +0x1c
    ActionNode* nextList;   // +0x20
    ActionNode* currentList; // +0x24
};

static int g_actionManagerCount; // DAT_011946b4
static ActionManager* g_actionManagers[]; // DAT_011946b8 (array of pointers)

void processActionQueues(void) {
    int count = g_actionManagerCount;
    if (count <= 0) return;

    for (int i = 0; i < count; i++) {
        ActionManager* mgr = g_actionManagers[i];
        ActionNode* node = mgr->currentList;

        // Process all actions in the current list
        while (node != nullptr) {
            ActionNode* nextNode = node->next; // save next before calling
            mgr->currentList = nextNode;

            // Call the second virtual function (likely execute/process)
            void (*actionFunc)(ActionNode*) = (void (*)(ActionNode*))node->vtable[1];
            actionFunc(node);

            node = mgr->currentList;
        }

        // Shift the lists: current = next, next = future, future = null
        mgr->currentList = mgr->nextList;
        mgr->nextList = mgr->futureList;
        mgr->futureList = nullptr;
    }
}