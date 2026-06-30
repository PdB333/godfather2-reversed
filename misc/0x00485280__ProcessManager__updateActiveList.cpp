// FUNC_NAME: ProcessManager::updateActiveList
// Function address: 0x00485280
// Role: Processes all entries in the active list (param_1[1]), moves them to the processed list (param_1[0]),
//       then performs a series of swaps between internal state fields, effectively rotating pending/active/processed lists.
//       Used to manage deferred execution queues (e.g., simulation steps, command buffers).

struct ProcessNode {
    void (*function)(int, int); // +0x00: function pointer (__fastcall or __thiscall with params)
    int param1;                 // +0x04: first parameter
    int param2;                 // +0x08: second parameter
    ProcessNode* next;          // +0x0C: next node in list
};

struct ProcessManager {
    ProcessNode* processedHead; // +0x00: head of processed (completed) list
    ProcessNode* activeHead;    // +0x04: head of active (to-be-processed) list
    int field_08;               // +0x08: (swapped with field_10)
    int field_0C;               // +0x0C: (swapped with field_14)
    int field_10;               // +0x10: (swapped with field_08)
    int field_14;               // +0x14: (swapped with field_0C)
    int field_18;               // +0x18: (swapped with field_20)
    int field_1C;               // +0x1C: (swapped with field_14? actually used in copy)
    int field_20;               // +0x20: (cleared after swap)
    int field_24;               // +0x24: (cleared after swap, but also used in traversal? not in this code)
};

void ProcessManager::updateActiveList() {
    ProcessNode* current = activeHead;
    if (current != nullptr) {
        ProcessNode* nextNode = current->next;          // save next before call
        current->function(current->param1, current->param2); // execute node's callback
        ProcessNode* last = current;                    // track last processed node
        while (nextNode != nullptr) {
            ProcessNode* temp = nextNode->next;         // save next
            nextNode->function(nextNode->param1, nextNode->param2);
            last = nextNode;
            nextNode = temp;
        }
        // Append the processed list to the front of the processedHead list
        last->next = processedHead;
        processedHead = activeHead;
        // activeHead is effectively cleared (will be overwritten)
    }

    // Rotate state fields – likely swapping between pending/active slots
    int temp1 = field_0C;
    field_0C = field_14;
    activeHead = (ProcessNode*)temp1; // note: param_1[1] gets old field_0C

    int temp2 = field_18;
    field_08 = field_10;    // param_1[2] gets old field_10
    field_18 = field_20;    // param_1[6] gets old field_20
    field_10 = temp2;       // param_1[4] gets old field_18
    field_14 = field_1C;    // param_1[5] gets old field_1C

    // Clear the swapped-out fields
    field_20 = 0;
    field_1C = 0;

    // Note: No return value; modifies internal state.
}