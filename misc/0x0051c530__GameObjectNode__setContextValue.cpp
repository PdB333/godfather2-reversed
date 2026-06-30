// FUNC_NAME: GameObjectNode::setContextValue
void GameObjectNode::setContextValue(int value) {
    // Store the context value at offset +0xac
    this->m_contextValue = value;

    // Iterate through child entries array at offset +0xf4
    // Each child entry is 20 bytes (5 ints), first int is an object pointer
    int childCount = *(short*)((uint8_t*)this + 0x80);
    ChildEntry* children = (ChildEntry*)((uint8_t*)this + 0xf4);

    // vtable offset 0x40 corresponds to the 17th virtual function (0x40/4 = 0x10)
    typedef void (__thiscall* SetValueMethod)(void* obj, int value);

    for (int i = 0; i < childCount; i++) {
        if (children[i].object != nullptr) {
            // Call the virtual method on each child
            SetValueMethod method = *(SetValueMethod*)(*(uint32_t*)children[i].object + 0x40);
            method(children[i].object, value);
        }
    }
}