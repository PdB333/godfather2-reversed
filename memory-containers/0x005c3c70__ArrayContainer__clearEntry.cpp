// FUNC_NAME: ArrayContainer::clearEntry
void __thiscall ArrayContainer::clearEntry(int this, int value)
{
    int count;
    int *array;
    int i;

    if (this != 0) {
        count = *(int *)(this + 0xc);          // +0x0C: number of elements
        if (0 < count) {
            array = *(int **)(this + 0x8);      // +0x08: pointer to array of ints
            for (i = 0; i < count; i++) {
                if (array[i] == value) {
                    array[i] = 0;               // nullify the matching entry
                    return;
                }
            }
        }
    }
}