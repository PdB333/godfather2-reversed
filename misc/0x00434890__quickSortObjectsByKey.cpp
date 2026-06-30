// FUNC_NAME: quickSortObjectsByKey
// Function address: 0x00434890
// Description: Quicksort an array of pointers to objects, sorting by the unsigned integer at offset 0x08 of each object.
// Parameters:
//   arrayHandle - pointer to a variable holding the base address of the pointer array (int**)
//   left - left index (inclusive)
//   right - right index (inclusive)
void quickSortObjectsByKey(int** arrayHandle, int left, int right)
{
    int* arrayBase;
    uint pivotKey;
    int i, j;
    uint leftKey, rightKey;
    void* temp;

    do {
        // pivot is the key of the middle element
        pivotKey = *(uint*)(*(int*)(*arrayHandle + ((left + right) / 2) * 4) + 0x08);

        i = left;
        j = right;
        arrayBase = *arrayHandle;

        do {
            // scan from left for element with key < pivot
            while (pivotKey < *(uint*)(*(int*)(arrayBase + i * 4) + 0x08)) {
                i++;
            }
            // scan from right for element with key > pivot
            while (*(uint*)(*(int*)(arrayBase + j * 4) + 0x08) < pivotKey) {
                j--;
            }
            if (j < i) break;

            // swap the two pointers
            temp = *(void**)(arrayBase + i * 4);
            *(void**)(arrayBase + i * 4) = *(void**)(arrayBase + j * 4);
            *(void**)(arrayBase + j * 4) = temp;

            i++;
            j--;
        } while (i <= j);

        // recursively sort left sub-array
        if (left < j) {
            quickSortObjectsByKey(arrayHandle, left, j);
        }
        left = i;
    } while (i < right);  // tail recursion for right sub-array
}