// FUNC_NAME: Container::releaseChildrenAndDestroy
void __thiscall Container::releaseChildrenAndDestroy(void)
{
    Node* current = *(Node**)((int)this + 0x14); // this->listHead
    while (current != 0) {
        Node* next = *(Node**)((int)current + 0x0c); // current->next
        // Call vtable[1] on current (release with param 0)
        (**(void (__thiscall**)(Node*, int))(**(int**)current + 4))(current, 0);
        current = next;
    }

    Node* singleObj = *(Node**)((int)this + 0x04); // this->singleObject
    if (singleObj != 0) {
        // Call vtable[1] on singleObj (release with param 0)
        (**(void (__thiscall**)(Node*, int))(**(int**)singleObj + 4))(singleObj, 0);
    }

    // Call vtable[3] on this (self-destruct)
    (**(void (__thiscall**)(Container*))(**(int**)this + 0x0c))(this);
}