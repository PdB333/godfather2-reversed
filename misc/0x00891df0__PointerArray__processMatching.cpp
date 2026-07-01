//FUNC_NAME: PointerArray::processMatching
void __thiscall PointerArray::processMatching(int param_2)
{
    uint count = *(uint *)(this + 0xc); // +0x0C: number of elements
    if (count != 0) {
        int **array = *(int ***)(this + 0x8); // +0x08: pointer to array of pointers
        for (uint i = 0; i < count; i++) {
            if (array[i] == (int *)param_2) {
                // Found matching pointer, call handler
                FUN_00891c10(); // likely a static or member function
                return;
            }
        }
    }
}