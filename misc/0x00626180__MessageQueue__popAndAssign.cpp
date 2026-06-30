// FUNC_NAME: MessageQueue::popAndAssign
// Function address: 0x00626180
// This function appears to pop two 32-bit values from a stack-like buffer (decrementing pointer by 8 bytes)
// and conditionally copies them into a target object if a global state structure indicates readiness.
// The global structure (returned by FUN_00625430) is checked: first int must be 6, and a byte at offset 6 of a sub-structure must be zero.
// On success, the two popped values are written at offsets 0x10 and 0x14 of that sub-structure.

class MessageQueue {
public:
    int __thiscall popAndAssign();
private:
    // offset +0x08: pointer to current position in a stack buffer (decremented before read)
    int* m_stackPtr;  // at this+0x08
};

// Helper: returns pointer to a global state structure (likely a manager or connection state)
extern int* __cdecl getGlobalState();

int MessageQueue::popAndAssign() {
    // Pop two ints from the stack (item size 8 bytes)
    m_stackPtr -= 2;  // decrement by 8 bytes (2 ints)
    int* popped = m_stackPtr;  // pointer to the popped item (two ints: popped[0], popped[1])
    int data0 = popped[0];
    int data1 = popped[1];

    // Retrieve global state
    int* globalState = getGlobalState();

    // Condition: globalState[0] == 6 (some magic value), and byte at globalState[1] + 6 is zero
    if (globalState[0] == 6) {
        int* target = (int*)globalState[1];
        char* targetBytes = (char*)target;
        if (targetBytes[6] == '\0') {
            // Write popped data into target structure at offsets 0x10 and 0x14
            target[0x10 / 4] = data0; // *(int*)(target + 0x10)
            target[0x14 / 4] = data1; // *(int*)(target + 0x14)
            return 1; // success
        }
    }
    return 0; // failure (condition not met or invalid state)
}