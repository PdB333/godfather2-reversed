// FUNC_NAME: NodeList::waitUntilFlagSet
void NodeList::waitUntilFlagSet() {
    // this->head at +0x8
    Node* current = *(Node**)(this + 0x8);
    // Each node has next pointer at +0x8 and flag at +0x19
    while (*(char*)(current + 0x19) == 0) {
        current = *(Node**)(current + 0x8);
    }
    // Found node with flag != 0, return
}