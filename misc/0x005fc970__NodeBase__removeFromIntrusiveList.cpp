// FUNC_NAME: NodeBase::removeFromIntrusiveList
void __thiscall NodeBase::removeFromIntrusiveList(void)
{
    NodeBase *listHead;     // from offset +0x04
    NodeBase *current;      // traversing pointer
    NodeBase *nextNode;

    // Store pointer to the list head object (stored at this+0x04)
    listHead = *(NodeBase **)((char *)this + 4);

    // Set vtable to a purecall stub (object is being destroyed)
    *(void ***)this = &PTR___purecall_00e407a4;

    if (listHead != 0) {
        // The list head object stores a pointer to the first node's link field at offset +0x04
        current = *(NodeBase **)((char *)listHead + 4);

        // If this node is the first node in the list
        if (current == (NodeBase *)((char *)this + 4)) {
            // Update list head to point to the next node
            *(NodeBase **)((char *)listHead + 4) = *(NodeBase **)((char *)this + 8);
            return;
        }

        // Traverse list to find the node just before this one
        nextNode = *(NodeBase **)((char *)current + 4); // next node's link field?
        while (nextNode != (NodeBase *)((char *)this + 4)) {
            current = *(NodeBase **)((char *)current + 4);
            nextNode = *(NodeBase **)((char *)current + 4);
        }

        // Unlink this node by adjusting previous node's next pointer
        *(NodeBase **)((char *)current + 4) = *(NodeBase **)((char *)this + 8);
    }
}