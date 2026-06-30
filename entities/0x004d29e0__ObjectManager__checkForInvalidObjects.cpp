// FUNC_NAME: ObjectManager::checkForInvalidObjects
char ObjectManager::checkForInvalidObjects() {
    int* arrayPtr = *(int**)(this + 0x14); // +0x14: array of handles (pointer + size at offset 1)
    uint count = (uint)arrayPtr[1];        // number of elements in the array
    char result = '\0';
    for (uint i = 0; i < count; i++) {
        if (result != '\0') {
            return result;
        }
        int handle = *(int*)(*arrayPtr + i * 4); // each element is a handle (4 bytes)
        int* objPtr = (int*)FUN_004986e0(&handle); // convert handle to object pointer
        if (objPtr == (int*)0 || *(int*)(*objPtr + 0x28) != 1) { // +0x28: state flag (1 = valid/active)
            result = '\x01';
        }
    }
    return result;
}