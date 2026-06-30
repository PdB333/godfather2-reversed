// FUNC_NAME: ObjectList::update
void ObjectList::update(uint arg) {
    // Header is at this+0x34, count at header+0xC (ushort)
    uint count = *(ushort *)(*(int *)((int)this + 0x34) + 0xC) + 1;

    // +0x38 points to array of object pointers (starting from index 1)
    uint index = 1;
    if (1 < count) {
        do {
            void* obj = *(void **)(*(int *)((int)this + 0x38) + index * 4);
            void** vtable = *(void ***)obj;
            // vtable+0x18: function taking one argument (e.g., update with delta)
            ((void (*)(void *, uint))vtable[0x18 / 4])(obj, arg);
            index++;
        } while (index < count);
    }

    index = 1;
    if (1 < count) {
        do {
            void* obj = *(void **)(*(int *)((int)this + 0x38) + index * 4);
            void** vtable = *(void ***)obj;
            // vtable+0x10: function taking no arguments (e.g., post-update)
            ((void (*)(void *))vtable[0x10 / 4])(obj);
            index++;
        } while (index < count);
    }
}