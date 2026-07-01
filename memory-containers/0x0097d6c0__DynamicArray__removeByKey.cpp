// FUNC_NAME: DynamicArray::removeByKey
void __thiscall DynamicArray::removeByKey(int this, int key) {
    uint index = 0;
    uint count = *(uint *)(this + 0xac);
    if (count != 0) {
        int *currentKey = (int *)(*(int *)(this + 0xa8) + 0xc);
        while (*currentKey != key) {
            index++;
            currentKey += 4;
            if (count <= index) {
                return;
            }
        }
        // found element at index
        int *elementBase = (int *)(*(int *)(this + 0xa8) + index * 0x10);
        FUN_0097c1e0(elementBase); // destructElement cleanup
        if (index != count - 1) {
            int *lastBase = (int *)(*(int *)(this + 0xa8) + (count - 1) * 0x10);
            // copy 16 bytes from last element into the gap
            *(undefined8 *)elementBase = *(undefined8 *)lastBase;
            *(undefined8 *)(elementBase + 2) = *(undefined8 *)(lastBase + 2);
        }
        *(int *)(this + 0xac) = count - 1;
    }
}