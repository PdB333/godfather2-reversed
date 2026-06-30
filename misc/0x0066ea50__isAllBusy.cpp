// FUNC_NAME: isAllBusy
// Function at 0x0066ea50: Iterates a linked list (head at this+0x14). Each node contains a pointer at offset 0x08 (node[2]) to an object that has a busy flag at offset +0xB2 (bit 0). Returns 1 (true) if for every node, either the pointer is null or the busy flag is set; returns 0 (false) if a node with a non-null pointer and clear busy flag is found.
// Likely a method of a class managing a list of active agents/behaviors (e.g., crew members, AI states).

bool __thiscall isAllBusy(int thisPtr)
{
    int* node = *(int**)(thisPtr + 0x14); // +0x14: head of linked list
    bool result = true;                    // default: all busy
    if (node != nullptr) {
        while (node[2] == nullptr || (*(byte*)(node[2] + 0xB2) & 1) != 0) {
            node = (int*)*node;           // next node in list
            if (node == nullptr) {
                return result;            // true = all busy
            }
        }
        result = false;                   // found an available node
    }
    return result;                        // false if any available, true if all busy
}