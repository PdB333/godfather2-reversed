// FUNC_NAME: Entity::writeToStream
void __thiscall Entity::writeToStream(int this, undefined4 *stream)
{
    int *listHead;
    int nodePtr;

    // Get type identifier from stream's vtable
    nodePtr = (**(code **)*stream)();

    if (nodePtr == 0x1b2d5c51) {
        // Type A: write a linked list node
        // this+0x68 points to a node structure (offset 0x48 from its base)
        if (*(int *)(this + 0x68) == 0) {
            nodePtr = 0;
        }
        else {
            nodePtr = *(int *)(this + 0x68) + -0x48;
        }
        listHead = stream + 0x19; // stream offset 0x64: head of list
        if (nodePtr == 0) {
            nodePtr = 0;
        }
        else {
            nodePtr = nodePtr + 0x48;
        }
        // Update list head if changed
        if (*listHead != nodePtr) {
            if (*listHead != 0) {
                FUN_004daf90(listHead); // free old head
            }
            *listHead = nodePtr;
            if (nodePtr != 0) {
                stream[0x1a] = *(undefined4 *)(nodePtr + 4); // copy next pointer
                *(int **)(nodePtr + 4) = listHead; // link back to head
            }
        }
        // Write this+0x78 to stream offset 0x78
        stream[0x1e] = *(undefined4 *)(this + 0x78);
    }
    else if (nodePtr == 0x211bc9c1) {
        // Type B: write three fields directly
        stream[0x1c] = *(undefined4 *)(this + 0x74); // +0x74
        stream[0x1e] = *(undefined4 *)(this + 0x78); // +0x78
        stream[0x20] = *(undefined4 *)(this + 0x70); // +0x70
        return;
    }
    return;
}