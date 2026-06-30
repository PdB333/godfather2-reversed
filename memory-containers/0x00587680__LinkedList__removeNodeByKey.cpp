// FUNC_NAME: LinkedList::removeNodeByKey
void __fastcall LinkedList::removeNodeByKey(int this, int key)
{
    int *currentNode;
    int *prevNode;
    int *nextNode;

    prevNode = (int *)0x0;
    currentNode = *(int **)(this + 0x14); // +0x14: head pointer
    if (currentNode != (int *)0x0) {
        while (nextNode = currentNode, *nextNode != key) { // +0x00: node key
            currentNode = (int *)nextNode[3]; // +0x0C: next pointer
            prevNode = nextNode;
            if (currentNode == (int *)0x0) {
                return;
            }
        }
        *(int *)(this + 0x0C) = *(int *)(this + 0x0C) - nextNode[1]; // +0x0C: count, +0x04: node size
        if (prevNode != (int *)0x0) {
            prevNode[3] = nextNode[3]; // +0x0C: next pointer
            (**(code **)(*(int *)*nextNode + 4))(nextNode, 0); // vtable[1] = destructor
            *(undefined1 *)(this + 0x10) = 1; // +0x10: modified flag
            return;
        }
        *(int **)(this + 0x14) = (int *)nextNode[3]; // +0x14: head pointer
        (**(code **)(*(int *)*nextNode + 4))(nextNode, 0); // vtable[1] = destructor
        *(undefined1 *)(this + 0x10) = 1; // +0x10: modified flag
    }
    return;
}