// FUNC_NAME: quickSortPartition
// Function at 0x008891c0: Hoare partition for sorting an array of pointers by a key at offset +0x60 from a sub-object at +0x14.
void quickSortPartition(int** leftPtr, int** rightPtr, int** pivotPtr) {
    // pivotElement: pointer to the pivot object
    int* pivotElement = *pivotPtr;
    // pivotKey: key from pivotElement->subObj->key (subObj at +0x14, key at +0x60)
    uint pivotKey = *(uint*)(*(int*)((int)pivotElement + 0x14) + 0x60);

    while (true) {
        // Move left pointer right while pivotKey > leftElement->subObj->key
        while (true) {
            int* leftElement = *leftPtr;
            uint leftKey = *(uint*)(*(int*)((int)leftElement + 0x14) + 0x60);
            if (pivotKey <= leftKey) break;
            leftPtr++;
        }

        // Move right pointer left while pivotKey < rightElement->subObj->key
        while (true) {
            rightPtr--;
            uint rightKey = *(uint*)(*(int*)((int)*rightPtr + 0x14) + 0x60);
            if (!(pivotKey < rightKey)) break;
        }

        if (rightPtr <= leftPtr) break;

        // Swap elements
        int* temp = *leftPtr;
        *leftPtr = *rightPtr;
        *rightPtr = temp;

        leftPtr++;
    }
}