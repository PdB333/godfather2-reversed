// FUNC_NAME: Node::unlink
void __thiscall Node::unlink(void) {
    // Offsets: +0x04 = prev, +0x08 = next
    // Global list head and tail (DAT_01205490 = listHead, DAT_01205494 = listTail)
    if (this->prev != nullptr) {
        this->prev->next = this->next;
    }
    if (this->next != nullptr) {
        this->next->prev = this->prev;
    }
    if (listHead == this) {
        listHead = this->next;
    }
    bool wasTail = (listTail == this);
    this->next = nullptr;
    if (wasTail) {
        listTail = this->prev;
    }
    this->prev = nullptr;
}