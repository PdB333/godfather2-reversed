// FUNC_NAME: ContainerList::removeNode
// Address: 0x005d10d0
// Removes a node from a singly linked list with head (offset 0) and tail (offset 4) pointers.
// Node has a 'next' pointer at offset 0x94.

class ContainerList {
public:
    void* m_head; // +0x00
    void* m_tail; // +0x04
};

void __thiscall ContainerList::removeNode(void* node) {
    if (node != 0) {
        if (this->m_tail == node) {
            this->m_tail = *(void**)((char*)node + 0x94);
        }
        if (this->m_head == node) {
            this->m_head = *(void**)((char*)node + 0x94);
        }
        FUN_005d1310();
    }
}