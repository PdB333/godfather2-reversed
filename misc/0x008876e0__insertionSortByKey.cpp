// FUNC_NAME: insertionSortByKey
void insertionSortByKey(int** start, int** end)
{
    if (start == end) return;
    int** pos = start;
    do {
        int* current = *pos; // element to insert
        int* prev = *(pos - 1); // previous element
        // Key: *(uint*)(*(int*)(object + 0x14) + 0x60)
        if (*(unsigned int*)(*(int*)(current + 0x14) + 0x60) < *(unsigned int*)(*(int*)(prev + 0x14) + 0x60)) {
            int** insertPos = pos;
            do {
                int** prevPos = insertPos - 1;
                *insertPos = prev; // shift previous element right
                prev = *(prevPos - 1); // get next previous (two positions back)
                insertPos = prevPos;
            } while (*(unsigned int*)(*(int*)(current + 0x14) + 0x60) < *(unsigned int*)(*(int*)(prev + 0x14) + 0x60));
            *insertPos = current;
        }
        ++pos;
    } while (pos != end);
}