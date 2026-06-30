// FUNC_NAME: quickSortByKey
void quickSortByKey(void** basePtr, int left, int right) {
    // basePtr is a pointer to an array of pointers to structs
    // Each struct has a sort key (uint) at offset +8
    void** array = *basePtr;
    
    while (left < right) {
        int pivotIdx = (left + right) / 2;
        uint pivotKey = *(uint*)((char*)array[pivotIdx] + 8);
        
        int i = left, j = right;
        do {
            while (*(uint*)((char*)array[i] + 8) < pivotKey) i++;
            while (pivotKey < *(uint*)((char*)array[j] + 8)) j--;
            if (i <= j) {
                // Swap pointers
                void* temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                i++;
                j--;
            }
        } while (i <= j);
        
        if (left < j) {
            quickSortByKey(basePtr, left, j);
        }
        left = i;
    }
}