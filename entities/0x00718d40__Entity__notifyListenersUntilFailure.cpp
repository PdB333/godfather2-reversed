// FUNC_NAME: Entity::notifyListenersUntilFailure
// Address: 0x00718d40
// Iterates a linked list of listener objects at offset 0x390, calling their virtual method (vtable+0xC) with the given argument.
// Continues while the callback returns non-zero; returns the last result (0 if any callback returned 0, else 1).

struct ListenerNode {
    void* object;      // +0x00: pointer to an object with vtable
    ListenerNode* next; // +0x04: next node in the list
};

char __thiscall Entity::notifyListenersUntilFailure(void* thisPtr, uint32_t param_2) {
    ListenerNode* node = *(ListenerNode**)((char*)thisPtr + 0x390);
    char result = '\x01';

    while (node != nullptr) {
        // Get the object's vtable, then call the 4th virtual method (offset 0xC) with param_2.
        void* obj = node->object;
        int (**vtable)(void) = *(int (***)(void))obj;
        result = (**(code**)(vtable + 3))(param_2);
        if (result == '\0') {
            break;
        }
        node = node->next;
    }

    return result;
}