// FUNC_NAME: ObjectRefArray::resize
void __thiscall ObjectRefArray::resize(int* thisPtr, uint newCapacity) {
    // thisPtr[0] = m_array (Node*)
    // thisPtr[1] = m_count (number of active nodes)
    // thisPtr[2] = m_capacity (allocated size)
    // Each Node is 8 bytes: [0] = Object* obj, [4] = Node* nextInObjectList
    // Objects have a pointer at offset +4 (Node* refListHead) that points to the head of a linked list of nodes referencing them.

    uint currentCapacity = (uint)thisPtr[2];
    if (currentCapacity < newCapacity) {
        // Allocate new node array (8 bytes per node)
        Node* newArray = (Node*)FUN_009c8e80(newCapacity << 3); // param_2 * 8
        uint oldCount = (uint)thisPtr[1];
        if (thisPtr[0] != 0) {
            Node* src = (Node*)thisPtr[0];
            Node* dst = newArray;
            for (uint i = 0; i < oldCount; i++) {
                Node oldNode = src[i];
                if (dst != nullptr) {
                    dst->obj = oldNode.obj;
                    dst->nextInObjectList = 0;
                    if (oldNode.obj != 0) {
                        // Insert dst into object's ref list (at head)
                        dst->nextInObjectList = (Node*)*(int*)((int)oldNode.obj + 4);
                        *(int**)((int)oldNode.obj + 4) = dst;
                    }
                }
                // Remove old node from object's list
                FUN_004daf90(&src[i]);
            }
            // Free old array
            FUN_009c8f10(thisPtr[0]);
        }
        thisPtr[0] = (int)newArray;
        thisPtr[2] = (int)newCapacity;
    }
}