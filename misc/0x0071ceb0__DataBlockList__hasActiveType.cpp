// FUNC_NAME: DataBlockList::hasActiveType
bool __fastcall DataBlockList::hasActiveType(DataBlockList* this) {
    Node* currentNode = this->head;
    if (currentNode == nullptr) return false;

    while (true) {
        DataBlock* data = (DataBlock*)currentNode->data; // offset +0
        int type = *(int*)((char*)data + 8); // +0x08: type field
        if (type == 0 || type == 0x48) {
            currentNode = currentNode->next; // offset +4: next pointer
            if (currentNode == nullptr) return false;
        } else {
            return true;
        }
    }
}