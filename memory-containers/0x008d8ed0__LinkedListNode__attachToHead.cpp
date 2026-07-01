// FUNC_NAME: LinkedListNode::attachToHead
int* __thiscall LinkedListNode::attachToHead(int* parent)
{
    int* headSentinel = (parent != 0) ? parent + 0x12 : 0;          // +0x48 / 4 = 0x12 int offsets

    if (this->prev != headSentinel) {
        if (this->prev != 0) {
            this->detach();                                          // FUN_004daf90 – unlinks current
        }

        this->prev = headSentinel;

        if (headSentinel != 0) {
            this->next = *(int*)(headSentinel + 1);                  // *(headSentinel + 4) → old first node
            *(int**)(headSentinel + 1) = this;                       // update sentinel's next pointer
        }
    }

    return this;
}