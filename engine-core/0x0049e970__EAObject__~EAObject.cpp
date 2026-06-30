// FUNC_NAME: EAObject::~EAObject
void __thiscall EAObject::~EAObject(void)
{
    int resourcePtr = this->resource; // offset +0x08
    this->vtable = &BASE_VTABLE_00e352b8;

    if (resourcePtr != 0) {
        if (g_ResourceFreeFunc != (code *)0x0) {
            (*g_ResourceFreeFunc)(resourcePtr);
        }
        ResourceManager *resMgr = GetResourceManager(); // FUN_009c8f80
        (**(code **)(*resMgr + 4))(resourcePtr, 0xb0); // Release resource with type 0xb0
    }

    SiblingNode *siblingNode = &this->siblingNode; // offset +0x0C (this+3)
    this->resource = 0;
    int *nextNode = siblingNode->next; // offset +0x00 relative to siblingNode
    if (nextNode != 0) {
        int *prevNode = *(int **)(nextNode + 4); // previous pointer
        if (prevNode == siblingNode) {
            *(undefined4 *)(nextNode + 4) = this->prevSibling; // offset +0x10
        } else {
            int *current = (int *)prevNode[1];
            while (current != siblingNode) {
                prevNode = (int *)prevNode[1];
                current = (int *)prevNode[1];
            }
            prevNode[1] = this->prevSibling;
        }
    }

    this->vtable = &FINAL_VTABLE_00e32808;

    ChildNode *child = this->childHead; // offset +0x04 (this+1)
    while (child != 0) {
        ChildNode *nextChild = child->next;
        child->next = 0;
        child->prev = 0;
        child = nextChild;
    }
}