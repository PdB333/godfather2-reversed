// FUNC_NAME: Utility::releaseArrayWithItemPointers
void __fastcall releaseArrayWithItemPointers(int* param_1) // param_1 points to {int* buffer; int count;}
{
    int i = param_1[1] - 1; // count - 1
    if (i >= 0) {
        int base = *param_1; // pointer to element array
        do {
            // Each element is 20 bytes; pointer to resource is at offset 8 within element
            int* resource = *(int**)(base + i * 0x14 + 8);
            if (resource != 0) {
                deallocate(resource); // FUN_009c8f10
            }
            i--;
        } while (i >= 0);
    }
    // Free the element array itself
    int* array = *param_1;
    if (array != 0) {
        deallocate(array); // FUN_009c8f10
    }
}