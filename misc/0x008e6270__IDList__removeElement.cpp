// FUNC_NAME: IDList::removeElement
void __thiscall IDList::removeElement(int param_2)
{
    uint count = *(uint *)(this + 0x30); // +0x30: number of elements
    uint index = 0;

    if (count != 0) {
        int *array = *(int **)(this + 0x2c); // +0x2c: pointer to array of ints
        while (*array != param_2) {
            index++;
            array++;
            if (count <= index) {
                return; // element not found
            }
        }
        // Element found at index
        if ((int)index >= 0) {
            if (index != count - 1) {
                // Replace with last element to avoid shifting
                *(int *)(*(int *)(this + 0x2c) + index * 4) = *(int *)(*(int *)(this + 0x2c) + (count - 1) * 4);
            }
            // Decrement count
            *(int *)(this + 0x30) = count - 1;
        }
    }
}