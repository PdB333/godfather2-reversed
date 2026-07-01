// FUNC_NAME: Array::removeLastElement
void __fastcall Array::removeLastElement(int this) {
    int count = *(int *)(this + 0xC);       // +0xC: element count
    void **array = *(void ***)(this + 8);   // +0x8: pointer to array of pointers (elements)
    void *element = array[count - 1];
    
    if (element != 0) {
        // Call release method (vtable slot 0) with flag 1
        (*(void (**)(void *, int))element)(element, 1);
    }
    
    // Decrement count (no shifting needed since last element is removed)
    *(int *)(this + 0xC) = count - 1;
}