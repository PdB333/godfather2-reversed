// FUNC_NAME: NodeList::removeNode
void __thiscall NodeList::removeNode(int node)
{
    if (node != 0) {
        // Update tail pointer (at offset +0x04)
        if (this->tail == node) {
            this->tail = *(int *)(node + 0x94); // Node's next pointer
        }
        // Update head pointer (at offset +0x00)
        if (this->head == node) {
            this->head = *(int *)(node + 0x94); // Node's next pointer
        }
        FUN_005d1310(); // Likely frees node or adjusts list bookkeeping
    }
}