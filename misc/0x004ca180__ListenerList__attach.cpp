// FUNC_NAME: ListenerList::attach
void __thiscall ListenerList::attach(ListenerInfo *info)
{
    IUnknown *listenerObj; // piVar3
    int listenerId; // iVar2
    uint cloneResult; // uVar1
    ListNode *sentinel; // from FUN_004cac00

    listenerObj = info->listener; // +0x00
    listenerId = info->id;        // +0x04

    // Release the original listener object (vtable+8 = Release)
    listenerObj->Release();

    if (listenerId == 0) {
        cloneResult = 0;
    } else {
        // Clone the listener object (likely AddRef or duplicate)
        cloneResult = FUN_004265d0(listenerId, listenerObj);
    }

    // Add the (possibly cloned) listener to the internal list
    FUN_004ca9a0(this, listenerObj, cloneResult);

    // Allocate a new sentinel node and initialize it as a circular doubly linked list
    sentinel = (ListNode *)FUN_004cac00();
    this->listHead = sentinel; // +0x1c

    sentinel->isSentinel = 1;     // +0x15
    sentinel->prev = sentinel;    // +0x00
    sentinel->next = sentinel;    // +0x04
    sentinel->data = sentinel;    // +0x08 (points to self for sentinel)

    this->listSize = 0;           // +0x20
}