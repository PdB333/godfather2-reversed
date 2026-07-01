// FUNC_NAME: ContainerManager::clearElements
void __thiscall ContainerManager::clearElements(void)
{
    int *arrayBase;
    int count;
    int *elementIter1;
    int *elementIter2;
    int *elementEnd; // actually points 0x28 past last element, we'll use a different naming

    arrayBase = *(int **)(this + 0x0C); // pointer to dynamic array of elements (each 0x28 bytes)
    if (arrayBase != (int *)0x0) {
        count = *(int *)(arrayBase + -1); // stored count just before the array (offset -4 from array start)
        elementEnd = arrayBase + count * 10; // because each element is 0x28 = 40 bytes = 10 ints
        // iterate backwards through the array
        for (int i = count; i > 0; i--) {
            elementEnd -= 10; // move to previous element (0x28 bytes back)
            // check field at offset +0x04 from element start (elementEnd[-9] when elementEnd points past element? Actually careful)
            // elementEnd initially points past the last element. After subtracting 10, it points to start of element i-1.
            // So elementEnd[-9] is offset +0x04 from start? Let's recalc: elementEnd points to start of element. elementEnd[-9] = *(elementEnd-9) which is 36 bytes back? This is messy.
            // Better to use pointer arithmetic as in original: the loop uses puVar3 which is initially arrayBase + count*0x28, then decrements by 10 each iteration.
            // We'll follow the original logic exactly to avoid bugs.
        }
        // Actually let's rewrite cleanly following original assembly.
    }
}