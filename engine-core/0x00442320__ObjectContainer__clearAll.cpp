// FUNC_NAME: ObjectContainer::clearAll

void __fastcall ObjectContainer::clearAll(int this)
{
    int count = *(int *)(this + 0x28); // +0x28: number of items in container
    if (count > 0) {
        int i = 0;
        do {
            destroyItemAt(this, i); // FUN_00441d30: release/destroy the i-th item
            i++;
        } while (i < count);
        *(int *)(this + 0x28) = 0; // reset count
    } else {
        *(int *)(this + 0x28) = 0;
    }
}