// FUNC_NAME: EntityList::containsId
bool EntityList::containsId(int id) {
    // Offset 0x118: pointer to list array (inline int array)
    int* listArray = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x118);
    // Offset 0x198: number of entries in list
    int listCount = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x198);

    if (listCount == 0) {
        return false;
    }

    for (int i = 0; i < listCount; i++) {
        if (listArray[i] == id) {
            return true;
        }
    }
    return false;
}