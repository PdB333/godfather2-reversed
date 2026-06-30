// FUNC_NAME: ObjectContainer::cleanup
void __thiscall ObjectContainer::cleanup(void *this) {
    uint count;
    void **ppvArray;
    uint i;

    count = *(uint *)((int)this + 0x1c);                    // +0x1c: count of child pointers
    if (count != 0) {
        ppvArray = (void **)((int)this + 0x08);             // +0x08: start of child pointer array
        for (i = 0; i < count; i++) {
            // Call virtual function at offset 0x10 on each child object
            (*(void (__thiscall **)(void *))(**(int **)ppvArray[i] + 0x10))(ppvArray[i]);
        }
    }
    // Call virtual function at offset 0x0C on the special child at +0x20
    (*(void (__thiscall **)(void *))(**(int **)((int)this + 0x20) + 0x0C))(*(void **)((int)this + 0x20));
    // Call base destructor/cleanup
    FUN_005651e0(this);
}