// FUNC_NAME: EntityManager::hasEntity
// Address: 0x004a4f20
// Role: Checks whether an entity with the given ID exists in any of the two internal lists.
//        First list (offset +0x34/+0x38) stores pointers to objects with an ID at offset +0x04 (4 bytes).
//        Second list (offset +0x68/+0x6c) stores 16-byte entries; first 4 bytes is a pointer to an object
//        that has a virtual method at vtable+0x78 that returns non-zero if it "owns" the given ID.

int __thiscall EntityManager::hasEntity(int id)
{
    // First list: array of 8-byte entries (pointer + padding?) at +0x34, count at +0x38
    int list1Count = *(int *)(this + 0x38);
    if (list1Count != 0) {
        char *list1Data = *(char **)(this + 0x34); // base of 8-byte entries
        for (int i = 0; i < list1Count; i++) {
            // each entry is 8 bytes, the first 4 bytes are a pointer to an object
            void *obj = *(void **)(list1Data + i * 8);
            // object's ID is at offset +0x04
            if (*(int *)((char *)obj + 4) == id) {
                return 1;
            }
        }
    }

    // Second list: array of 16-byte entries at +0x68, count at +0x6c
    int list2Count = *(int *)(this + 0x6c);
    if (list2Count != 0) {
        char *list2Data = *(char **)(this + 0x68); // base of 16-byte entries
        for (int i = 0; i < list2Count; i++) {
            // first 4 bytes of each entry is a pointer to an object
            void *obj = *(void **)(list2Data + i * 16);
            // Virtual call: get vtable pointer, then function at offset 0x78 (index 0x1E)
            int *vtable = *(int **)obj;
            // Function signature: bool (__thiscall)(void* this, int id)
            bool (*virtualFunc)(void *, int) = (bool (*)(void *, int))vtable[0x78 / 4];
            if (virtualFunc(obj, id)) {
                return 1;
            }
        }
    }

    return 0;
}