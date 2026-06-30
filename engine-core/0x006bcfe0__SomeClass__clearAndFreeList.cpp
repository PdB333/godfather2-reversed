// FUNC_NAME: SomeClass::clearAndFreeList
void __fastcall SomeClass::clearAndFreeList(int this)
{
    uint index;
    int element;

    index = 0;
    if (*(int *)(this + 0x78) != 0) {
        do {
            element = *(int *)(*(int *)(this + 0x74) + index * 8); // +0x74: list base pointer, each entry 8 bytes
            if ((element != 0) && (element != 0x48)) {
                FUN_004088c0(element + -0xc); // likely free/delete with offset adjustment
            }
            index = index + 1;
        } while (index < *(uint *)(this + 0x78)); // +0x78: count of elements
    }
    FUN_006bccd0(); // likely reset/clear the list
    return;
}