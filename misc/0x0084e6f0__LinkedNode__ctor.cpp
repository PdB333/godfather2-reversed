// FUNC_NAME: LinkedNode::ctor
void __thiscall LinkedNode::ctor(LinkedNode *this, void *parent)
{
    // vtable pointer at offset 0
    *(void **)this = &PTR_FUN_00d74eb4;
    void *anchor;
    // parent->+0x48 is the anchor of a linked list (likely a "head" or "sentinel" structure)
    if (parent == (void *)0x0) {
        anchor = (void *)0x0;
    } else {
        anchor = (void *)((char *)parent + 0x48);
    }
    // offset +0x04: next pointer (or "link" to anchor)
    *(void **)((char *)this + 4) = anchor;
    // offset +0x08: prev pointer (or "previous node" pointer)
    *(void **)((char *)this + 8) = (void *)0x0;
    if (anchor != (void *)0x0) {
        // anchor->+0x04 is likely a "tail" or "prev" pointer of the anchor
        // Save existing anchor->+0x04 into current node's prev
        *(void **)((char *)this + 8) = *(void **)((char *)anchor + 4);
        // Link the anchor's pointer to point to this node's next field (offset +4)
        *(void **)((char *)anchor + 4) = (char *)this + 4;
    }
    return;
}