// FUNC_NAME: LinkedListNode::insertIntoBucket
void __thiscall LinkedListNode::insertIntoBucket(void *this, HashTable *table)
{
    int bucketIndex;
    Node **bucketHeadPtr;
    Node *oldHead;

    bucketIndex = getBucketIndex(this);
    bucketHeadPtr = (Node **)((char *)table + 0x10 + bucketIndex * 4);
    *(Node **)((char *)this + 0x10) = *bucketHeadPtr;  // this->next = old head
    *(Node ***)((char *)this + 0xc) = bucketHeadPtr;  // this->prevPtr = &bucketHead
    oldHead = *bucketHeadPtr;
    if (oldHead != 0) {
        *(Node ***)((char *)oldHead + 0xc) = (Node **)((char *)this + 0x10); // old head->prevPtr = &this->next
    }
    *bucketHeadPtr = (Node *)this; // bucket head = this
}