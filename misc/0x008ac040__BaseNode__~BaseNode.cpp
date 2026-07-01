// FUNC_NAME: BaseNode::~BaseNode
void __thiscall BaseNode::~BaseNode(BaseNode* this)
{
    // +0x38: pointer to custom cleanup argument
    // +0x44: pointer to cleanup function (code pointer)
    if (this->m_pCleanupArg != 0) {
        // Call the cleanup function with the argument
        (*(void (__thiscall**)(void*))(this + 0x44))(this->m_pCleanupArg);
    }

    // +0x28: vtable pointer, set to base class vtable (global PTR_LAB_00e317cc)
    this->m_pVtable = &PTR_LAB_00e317cc;

    // +0x18: previous node pointer
    // +0x1c: next node pointer
    // +0x20: pointer to data object (which also has list pointers at +0x4 and +0x8)
    BaseNode* prev = this->m_pPrev;
    BaseNode* next = this->m_pNext;
    BaseNode* data = this->m_pData;

    // Remove this node from the doubly linked list and insert the data object in its place
    if (prev != 0) {
        if (next == 0) {
            // If no next, set prev's next to data
            *(BaseNode**)(prev + 4) = data;
        } else {
            // Set next's prev to data
            *(BaseNode**)(next + 8) = data;
        }
    }
    if (data != 0) {
        // Set data's next to next
        *(BaseNode**)(data + 4) = next;
    }

    // Call memory deallocation function (likely operator delete or pool free)
    FUN_0064d150();
}