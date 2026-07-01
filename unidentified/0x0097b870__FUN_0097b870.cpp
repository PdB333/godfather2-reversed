// FUNC_NAME: ManagerClass::findElementIndex
uint __thiscall ManagerClass::findElementIndex(void *this, int searchKey) {
    uint idx = 0xFFFFFFFF;
    // +0x9c: count of elements in the array
    // +0x7c: pointer to start of int array (element IDs or something)
    if (*(uint *)((char *)this + 0x9c) != 0) {
        int *ptr = (int *)((char *)this + 0x7c);
        idx = 0;
        while (*ptr != searchKey) {
            idx++;
            ptr++;
            if (*(uint *)((char *)this + 0x9c) <= idx) {
                return 0xFFFFFFFF; // not found
            }
        }
    }
    return idx;
}