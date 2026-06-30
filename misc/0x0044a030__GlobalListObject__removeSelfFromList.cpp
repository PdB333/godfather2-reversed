// FUNC_NAME: GlobalListObject::removeSelfFromList
void __fastcall GlobalListObject::removeSelfFromList(GlobalListObject* thisObj)
{
    // +0x00: vtable pointer (set to PTR_FUN_00e312d0 initially, changed to PTR_LAB_00e2f638 at end)
    // +0x0C: pointer to the head of a singly linked list that this object belongs to
    // +0x10: pointer to the next object in the list (or NULL if last)

    GlobalListObject** listHeadPtr;  // actually &(thisObj->headField)
    GlobalListObject* headNode;
    GlobalListObject* currentNode;
    GlobalListObject* nextNode;

    listHeadPtr = (GlobalListObject**)(((uint*)thisObj) + 3); // &thisObj->headField
    thisObj->vtable = &PTR_FUN_00e312d0;                 // set base vtable

    headNode = thisObj->headField;                       // load head pointer

    if (headNode != NULL)
    {
        currentNode = *(GlobalListObject**)((uint*)headNode + 1); // dereference headNode's next pointer (offset +4)

        if (currentNode == listHeadPtr)                  // if headNode's next points back to our headField addr (single element or head sentinel)
        {
            *(uint*)((uint)headNode + 4) = (uint)thisObj->nextPtr; // update headNode's next to skip this
            thisObj->vtable = &PTR_LAB_00e2f638;                     // set final vtable
            return;
        }

        nextNode = (GlobalListObject*)*((uint*)currentNode + 1); // get currentNode's next

        while (nextNode != listHeadPtr)                  // walk until we find the node whose next points to our headField
        {
            currentNode = nextNode;
            nextNode = (GlobalListObject*)*((uint*)currentNode + 1);
        }

        // currentNode is the node just before us in the list
        *((uint*)currentNode + 1) = (uint)thisObj->nextPtr; // redirect its next to skip us
    }

    thisObj->vtable = &PTR_LAB_00e2f638;                 // set final vtable (maybe base class vtable)
    return;
}