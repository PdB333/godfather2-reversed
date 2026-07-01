// FUNC_NAME: ObjectList::removeElement
void __thiscall ObjectList::removeElement(uintptr_t value)
{
    uint count;
    int *elements;
    uint index;

    count = *(uint *)(this + 0x14);          // +0x14: element count
    if (count != 0) {
        elements = *(int **)(this + 0x10);   // +0x10: pointer to array of pointers
        index = 0;
        while (*elements != value) {
            index++;
            elements++;
            if (count <= index) {
                return;                      // element not found
            }
        }
        // Found at index
        if (*(char *)(this + 8) != '\0') {   // +0x08: pending release flag
            releaseObject(value);            // FUN_00838050
            if (*(int *)(this + 0x38) == 0 && *(int *)(this + 0x44) == 0) {
                *(char *)(this + 8) = '\0';  // clear pending flag
            }
        }
        // Replace removed element with last element (if not already last)
        if (index != *(int *)(this + 0x14) - 1) {
            *(int *)(*(int *)(this + 0x10) + index * 4) =
                *(int *)(*(int *)(this + 0x10) + -4 + *(int *)(this + 0x14) * 4);
        }
        // Decrement count
        *(int *)(this + 0x14) = *(int *)(this + 0x14) - 1;
        if (*(int *)(this + 0x14) == 0) {
            *(char *)(this + 9) = '\0';      // +0x09: empty flag
        }
    }
}