// FUNC_NAME: LinkedListNode::insertAfter

struct LinkedListNode {
    LinkedListNode* next;  // +0x00
    LinkedListNode* prev;  // +0x04
    int data;              // +0x08
};

extern void unlinkNode(LinkedListNode* node);

LinkedListNode* __thiscall LinkedListNode::insertAfter(LinkedListNode* param_2) {
    if (this != param_2) {
        LinkedListNode* newNext = param_2->next;
        if (this->next != newNext) {
            if (this->next != nullptr) {
                unlinkNode(this);
            }
            this->next = newNext;
            if (newNext != nullptr) {
                this->prev = newNext->prev;
                newNext->prev = this;
            }
        }
    }
    this->data = param_2->data;
    return this;
}