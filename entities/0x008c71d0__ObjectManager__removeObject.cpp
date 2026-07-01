// FUNC_NAME: ObjectManager::removeObject
void __thiscall ObjectManager::removeObject(int this, int pObject)
{
    uint count;
    uint index;
    uint lastIndex;
    int *list;

    count = *(uint *)(this + 0x28);          // m_objectCount
    index = 0;
    lastIndex = 0xffffffff;                  // sentinel for not found

    if (count != 0) {
        list = *(int **)(this + 0x24);       // m_objectList
        do {
            lastIndex = index;
            if (*list == pObject) break;
            index = index + 1;
            list = list + 1;
            lastIndex = 0xffffffff;          // reset if not found
        } while (index < count);
    }

    // If found and not the last element, swap with last
    if (lastIndex != count - 1) {
        *(undefined4 *)(*(int *)(this + 0x24) + lastIndex * 4) =
             *(undefined4 *)(*(int *)(this + 0x24) + -4 + count * 4);
    }

    // Decrement object count
    *(int *)(this + 0x28) = *(int *)(this + 0x28) - 1;

    // If the object is active, also remove from active list
    if (*(int *)(pObject + 0x1d0) != 0) {   // pObject->m_isActive
        count = *(uint *)(this + 0x34);     // m_activeCount
        index = 0;
        if (count != 0) {
            list = *(int **)(this + 0x30);  // m_activeList
            while (*list != pObject) {
                index = index + 1;
                list = list + 1;
                if (count <= index) {
                    return;
                }
            }
            if (-1 < (int)index) {
                if (index != count - 1) {
                    *(undefined4 *)(*(int *)(this + 0x30) + index * 4) =
                         *(undefined4 *)(*(int *)(this + 0x30) + -4 + count * 4);
                }
                *(int *)(this + 0x34) = *(int *)(this + 0x34) - 1;
            }
        }
    }
    return;
}