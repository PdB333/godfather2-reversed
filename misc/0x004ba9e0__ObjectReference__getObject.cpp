// FUNC_NAME: ObjectReference::getObject
int __thiscall ObjectReference::getObject() {
    // Offset +0x04: index into array
    int index = *(int*)((char*)this + 4);
    // Offset +0x08: pointer to array descriptor object
    int descriptorPtr = *(int*)((char*)this + 8);
    // Offset +0x04 of descriptor: base pointer to actual element data
    int base = *(int*)(descriptorPtr + 4);
    // Each element is 0x34 bytes
    return base + index * 0x34;
}