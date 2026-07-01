// FUNC_NAME: ObjectList::addItem
void __thiscall ObjectList::addItem(int this, int newElement) {
    // +0x7c: current count of elements (max 25)
    // +0x18: array of elements (each 4 bytes)
    uint count = *(uint*)(this + 0x7c);
    if (count < 25) {
        *(int*)(this + 0x18 + count * 4) = newElement;
        *(int*)(this + 0x7c) = count + 1;
    }
}