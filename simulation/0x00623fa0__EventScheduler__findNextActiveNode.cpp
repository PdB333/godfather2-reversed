// FUNC_NAME: EventScheduler::findNextActiveNode
void __thiscall EventScheduler::findNextActiveNode(EventScheduler* this) {
    // +0x00: head pointer (sentinel or first node?)
    // +0x04: current node pointer
    if (this->head == 0) {
        // crash or assert
        FUN_00b97aea();
    }

    EventNode* current = this->current;
    // +0x25: active flag (0 = inactive, 1 = active)
    if (current->active == 0) {
        EventNode* next = current->next; // +0x08: next pointer

        if (next->active != 0) {
            // next is active, but we need to check if there is a valid node before it?
            // Walk backwards from the node that points to this next?
            EventNode* prev = current->prev; // +0x04: prev pointer
            char flag = prev->active;
            while (flag == 0 && this->current == prev->next) {
                // continue going backwards while prev is inactive and current is the next of prev?
                this->current = prev;
                prev = prev->prev;
                flag = prev->active;
            }
            this->current = prev;
            return;
        }

        // next is inactive, so walk from head to find first active
        EventNode* node = this->head;
        char flag = node->active;
        EventNode* it = node;
        while (flag == 0) {
            flag = it->next->active;
            node = it;
            it = it->next;
        }
        this->current = node;
        return;
    }

    // current is active – should not happen
    FUN_00b97aea();
}