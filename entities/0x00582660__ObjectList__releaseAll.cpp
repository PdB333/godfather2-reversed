// FUNC_NAME: ObjectList::releaseAll
void ObjectList::releaseAll() {
    // +0x04: count of items in the list
    int count = *(int *)((char *)this + 4);
    // +0x08: pointer to array of item pointers
    void **items = *(void ***)((char *)this + 8);
    // +0x0C: pointer to vtable (first entry is the vtable base pointer)
    void **vtable = *(void ***)((char *)this + 12);

    for (int i = 0; i < count; i++) {
        void *node = items[i];
        if (node != nullptr) {
            // First field of the node is a pointer to the inner object
            void *innerObj = *(void **)node;
            // Virtual function at vtable index 1 (offset 4) – likely Release/Destroy
            void (*releaseFunc)(void *, int) = (void (*)(void *, int))vtable[1];
            releaseFunc(innerObj, 0);  // release the inner object
            releaseFunc(node, 0);      // release the node itself
        }
    }
}