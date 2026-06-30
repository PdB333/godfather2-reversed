// FUNC_NAME: heapReplaceValue
void __fastcall heapReplaceValue(unsigned int* heapBase, int heapSize, int index, unsigned int newValue)
{
    int currentIdx = index;
    int leftChildIdx = index * 2;

    // Sift down: move smaller children up until we reach a leaf
    while (true) {
        int rightChildIdx = leftChildIdx + 2; // right child = 2*currentIdx + 2 (0-based)
        if (rightChildIdx >= heapSize) {
            break;
        }

        // pick the smaller child
        int smallerChildIdx = rightChildIdx; // default to right
        if (heapBase[rightChildIdx] < heapBase[rightChildIdx - 1]) {
            smallerChildIdx = leftChildIdx + 1; // left child = 2*currentIdx + 1
        }

        // move the smaller child up to the current hole
        heapBase[currentIdx] = heapBase[smallerChildIdx];
        currentIdx = smallerChildIdx;
        leftChildIdx = currentIdx * 2;
    }

    // If we have only a left child (the last element)
    if (rightChildIdx == heapSize) {
        heapBase[currentIdx] = heapBase[heapSize - 1];
        currentIdx = heapSize - 1;
    }

    // Sift up with the new value
    while (index < currentIdx) {
        int parentIdx = (currentIdx - 1) / 2;
        unsigned int parentValue = heapBase[parentIdx];
        if (newValue <= parentValue) {
            break;
        }
        heapBase[currentIdx] = parentValue;
        currentIdx = parentIdx;
    }
    heapBase[currentIdx] = newValue;
}