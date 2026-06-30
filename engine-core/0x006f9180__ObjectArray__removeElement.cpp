// FUNC_NAME: ObjectArray::removeElement
bool __thiscall ObjectArray::removeElement(int element) {
    bool removed = false;
    unsigned int index = 0;
    
    if (*(unsigned int*)(this + 0x14) != 0) {  // count field at +0x14
        int* array = *(int**)(this + 0x10);    // array pointer at +0x10
        while (*array != element) {
            index++;
            array++;
            if (*(unsigned int*)(this + 0x14) <= index) {
                return removed; // false
            }
        }
        removed = (index != 0xffffffff);
        if (removed) {
            FUN_006f8ff0(index); // call removal helper with index
        }
    }
    return removed;
}