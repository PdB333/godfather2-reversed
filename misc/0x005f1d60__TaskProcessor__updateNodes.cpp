// FUNC_NAME: TaskProcessor::updateNodes
// Address: 0x005f1d60
// Processes a linked list of task nodes, handling state transitions.

struct TaskNode {
    int field_0;                 // +0x00 (unused here)
    TaskNode* next;              // +0x04
    int active;                  // +0x08
    /* padding to +0x5c */
    int dataAt0x5c;              // +0x5c
    char byteAt0x64;             // +0x64
    int state;                   // +0x68
    unsigned short flags;        // +0x6c
};

TaskNode* g_headNode = (TaskNode*)0x011a0ef0; // linked list head

void __thiscall TaskProcessor::updateNodes(int context)
{
    TaskNode* node = g_headNode;
    if (node == 0) return;

    do {
        if (node->active != 0) {
            int state = node->state;
            if (state == 2 || state == 4) {
                FUN_005f2280(context);  // handle context setup
                FUN_005f3080(node);     // process state 2/4
            }
            else if (state == 5) {
                FUN_005f1ef0(node);     // terminate or finalize node
            }
            else if (state == 1) {
                if ((node->flags & 2) == 0) {
                    node->flags |= 2;   // mark first time flag
                } else {
                    FUN_005dbc10(node->byteAt0x64, node->dataAt0x5c); // trigger action
                    FUN_005f1ef0(node); // then finalize
                }
            }
        }
        node = node->next;
    } while (node != 0);
}