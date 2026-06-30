// FUNC_NAME: Navigation::validatePathIndices
bool Navigation::validatePathIndices(int* outIndices, int targetIndex) {
    outIndices[0] = targetIndex;

    // Get first intermediate index from current cell (this->+0x74) to targetIndex
    short currentIndex = *(short*)(this + 0x74); // +0x74 short currentCellIndex
    int idx1 = -1;
    if (currentIndex >= 0) {
        int rowCount = *(int*)(*(int*)(this + 0x70) + 0x18); // grid row count
        if (targetIndex < rowCount && targetIndex >= 0) {
            int* rows = *(int**)(*(int*)(this + 0x70) + 0x1c); // pointer to array of Row structures
            int rowSize = 0x18; // each Row is 0x18 bytes
            // Each Row has at +0x8: column count, at +0xc: pointer to array of 0x10-byte cell entries
            int colCount = *(int*)((char*)rows + 8 + currentIndex * rowSize);
            if (targetIndex < colCount) {
                int* cellArray = *(int**)((char*)rows + 0xc + currentIndex * rowSize); // pointer to 0x10-byte cells
                idx1 = cellArray[targetIndex * (0x10 / 4)]; // first int in 0x10-byte cell
            }
        }
    }
    outIndices[1] = idx1;

    // Get second intermediate index from current cell to idx1
    int idx2 = -1;
    if (currentIndex >= 0) {
        int rowCount = *(int*)(*(int*)(this + 0x70) + 0x18);
        if (idx1 >= 0 && idx1 < rowCount) {
            int* rows = *(int**)(*(int*)(this + 0x70) + 0x1c);
            int colCount = *(int*)((char*)rows + 8 + currentIndex * 0x18);
            if (idx1 < colCount) {
                int* cellArray = *(int**)((char*)rows + 0xc + currentIndex * 0x18);
                idx2 = cellArray[idx1 * 4]; // 0x10/4 = 4
            }
        }
    }
    outIndices[2] = idx2;

    // Get third intermediate index from current cell to idx2
    int idx3 = -1;
    if (currentIndex >= 0) {
        int rowCount = *(int*)(*(int*)(this + 0x70) + 0x18);
        if (idx2 >= 0 && idx2 < rowCount) {
            int* rows = *(int**)(*(int*)(this + 0x70) + 0x1c);
            int colCount = *(int*)((char*)rows + 8 + currentIndex * 0x18);
            if (idx2 < colCount) {
                int* cellArray = *(int**)((char*)rows + 0xc + currentIndex * 0x18);
                idx3 = cellArray[idx2 * 4];
            }
        }
    }
    outIndices[3] = idx3;

    // Validate that all indices are valid and that each step is passable
    if (targetIndex >= 0 && idx1 >= 0 && idx2 >= 0 && idx3 >= 0) {
        if (isStepValid() && isStepValid() && isStepValid() && isStepValid()) {
            return true;
        }
    }
    return false;
}