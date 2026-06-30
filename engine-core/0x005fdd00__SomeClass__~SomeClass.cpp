// FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x005fdd00
// Destructor: removes this object from multiple linked lists and calls base destructor.

void __fastcall SomeClass::~SomeClass(int this)
{
    int firstNode;
    int currentNode;
    int *nodePtr;
    int prevNode;
    int nextNode;
    int listHead;
    int listNext;
    int local_c; // temporary list head for callback
    int local_8; // temporary list next for callback
    int local_4; // unused

    local_c = 0;
    local_8 = 0;
    local_4 = 0;

    // Call base class destructor
    baseDestructor();

    // If there's a destroy callback, invoke it with two list pointers and two output pointers
    if (*(code **)(this + 0xA4) != (code *)0x0) {
        (**(code **)(this + 0xA4))(this, this + 0x7C, this + 0x88, &local_c, &local_8);
    }

    // Remove from list at offset 0x7C? Actually the callback used offsets 0x7C and 0x88.
    // The following removal uses local_c as a temporary list head.
    if (local_c != 0) {
        nodePtr = *(int **)(local_c + 4);
        if (nodePtr == &local_c) {
            // Only one node: set its next to the head's next (which is itself)
            *(int *)(local_c + 4) = local_8;
        } else {
            // Find the node that points to the head
            while ((int *)nodePtr[1] != &local_c) {
                nodePtr = (int *)nodePtr[1];
            }
            nodePtr[1] = local_8;
        }
    }

    // Remove from list at offset 0x118
    listHead = *(int *)(this + 0x118);
    if (listHead != 0) {
        currentNode = *(int *)(listHead + 4);
        if (currentNode == this + 0x118) {
            // Only one node: set its next to the head's next (which is itself)
            *(undefined4 *)(listHead + 4) = *(undefined4 *)(this + 0x11C);
        } else {
            // Find the node that points to the head
            listHead = *(int *)(currentNode + 4);
            while (listHead != this + 0x118) {
                currentNode = *(int *)(currentNode + 4);
                listHead = *(int *)(currentNode + 4);
            }
            *(undefined4 *)(currentNode + 4) = *(undefined4 *)(this + 0x11C);
        }
    }

    // Remove from three lists at offsets 0x94, 0x88, 0x7C (in that order)
    int listCount = 3;
    int listOffset = this + 0xA0; // start at offset 0xA0, then subtract 0xC each iteration
    do {
        int nodeAddr = listOffset - 0xC; // offset 0x94, then 0x88, then 0x7C
        firstNode = *(int *)(nodeAddr);
        if (firstNode != 0) {
            currentNode = *(int *)(firstNode + 4);
            if (currentNode == nodeAddr) {
                // Only one node: set its next to the head's next
                *(undefined4 *)(firstNode + 4) = *(undefined4 *)(listOffset - 8);
            } else {
                // Find the node that points to the head
                firstNode = *(int *)(currentNode + 4);
                while (firstNode != nodeAddr) {
                    currentNode = *(int *)(currentNode + 4);
                    firstNode = *(int *)(currentNode + 4);
                }
                *(undefined4 *)(currentNode + 4) = *(undefined4 *)(listOffset - 8);
            }
        }
        listCount--;
        listOffset = nodeAddr;
    } while (listCount >= 0);

    // Remove from list at offset 0x4C
    listHead = *(int *)(this + 0x4C);
    if (listHead != 0) {
        currentNode = *(int *)(listHead + 4);
        if (currentNode == this + 0x4C) {
            *(undefined4 *)(listHead + 4) = *(undefined4 *)(this + 0x50);
        } else {
            listHead = *(int *)(currentNode + 4);
            while (listHead != this + 0x4C) {
                currentNode = *(int *)(currentNode + 4);
                listHead = *(int *)(currentNode + 4);
            }
            *(undefined4 *)(currentNode + 4) = *(undefined4 *)(this + 0x50);
        }
    }

    // Remove from list at offset 0x44
    listHead = *(int *)(this + 0x44);
    if (listHead != 0) {
        currentNode = *(int *)(listHead + 4);
        if (currentNode == this + 0x44) {
            *(undefined4 *)(listHead + 4) = *(undefined4 *)(this + 0x48);
            return;
        }
        listHead = *(int *)(currentNode + 4);
        while (listHead != this + 0x44) {
            currentNode = *(int *)(currentNode + 4);
            listHead = *(int *)(currentNode + 4);
        }
        *(undefined4 *)(currentNode + 4) = *(undefined4 *)(this + 0x48);
    }
}