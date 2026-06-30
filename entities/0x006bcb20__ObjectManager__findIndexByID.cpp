// FUNC_NAME: ObjectManager::findIndexByID
int __thiscall ObjectManager::findIndexByID(int key)
{
    int index = -1;
    if (key != 0) {
        int *current = *(int **)(this + 0x68);    // +0x68: pointer to array of {id, data} pairs
        int *end = current + *(int *)(this + 0x6c) * 2; // +0x6c: number of entries, each entry is 2 ints
        int i = 0;
        while (current != end) {
            if (*current == key) {
                index = i;
                break;
            }
            current += 2; // skip over data portion
            i++;
        }
    }
    return index;
}