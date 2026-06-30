// FUNC_NAME: CObjectArray::removeAndRelease
int __thiscall CObjectArray::removeAndRelease(void *this, void *element) {
    uint count = *(uint *)((int)this + 8); // +0x08: number of elements
    uint i = 0;
    if (count != 0) {
        int **array = *(int ***)((int)this + 4); // +0x04: pointer to array of pointers
        do {
            if ((int *)*array == (int *)element) {
                if (i < count - 1) {
                    do {
                        *(int *)(*(int *)((int)this + 4) + i * 4) = // shift elements left
                             *(int *)(*(int *)((int)this + 4) + 4 + i * 4);
                        i = i + 1;
                    } while (i < *(int *)((int)this + 8) - 1U);
                }
                *(int *)((int)this + 8) = *(int *)((int)this + 8) - 1; // decrement count
                break;
            }
            i = i + 1;
            array = array + 1;
        } while (i < count);
    }
    if (element != (void *)0x0) {
        (*(void (__thiscall **)(void *, int))(**(int **)element))(element, 1); // call virtual release(1)
    }
    return 1;
}