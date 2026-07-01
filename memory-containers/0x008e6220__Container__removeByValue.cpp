// FUNC_NAME: Container::removeByValue
void __thiscall Container::removeByValue(int param_2)
{
    uint count = *(uint *)(this + 0x18);  // +0x18: number of elements
    uint index = 0;
    if (count != 0) {
        int *array = *(int **)(this + 0x14);  // +0x14: pointer to array of ints
        while (*array != param_2) {
            index++;
            array++;
            if (count <= index) {
                return;  // value not found
            }
        }
        if ((int)index >= 0) {
            if (index != count - 1) {
                // Move last element to the removed slot
                *(int *)(*(int *)(this + 0x14) + index * 4) =
                    *(int *)(*(int *)(this + 0x14) + (count - 1) * 4);
            }
            *(int *)(this + 0x18) = count - 1;  // decrement count
        }
    }
    return;
}