// FUNC_NAME: SomeManager::processElements
void __thiscall SomeManager::processElements(int *arrayBasePtr)
{
    int count;
    int i;
    int elementOffset;

    // Get the container structure at this+0x20, then read count at +0xc
    count = *(int *)(*(int *)(this + 0x20) + 0xc);
    i = 0;
    if (0 < count) {
        elementOffset = 0;
        do {
            // Call function on each element (size 0x40) starting at *arrayBasePtr
            FUN_009f4cd0(*arrayBasePtr + elementOffset);
            i = i + 1;
            elementOffset = elementOffset + 0x40;
        } while (i < count);
    }
    return;
}