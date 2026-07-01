// FUNC_NAME: sortRecordArrayDescending
// Function at 0x008875a0: Insertion sort of array of 80-byte records (20 uint32s) descending by the third uint32 (offset 0x8). Used for sorting some game object list by key.
void sortRecordArrayDescending(uint* start, uint* end) {
    if (start == end) return;
    const uint RECORD_SIZE = 0x14; // 20 uint32s per record (80 bytes)

    uint* cur = start + RECORD_SIZE;
    while (cur != end) {
        uint temp[RECORD_SIZE];
        // Copy current record to temporary storage
        for (int i = 0; i < RECORD_SIZE; ++i) {
            temp[i] = cur[i];
        }

        // Find insertion point: shift right while temp key < previous record key
        uint* insertPos = cur;
        while (insertPos != start && temp[2] < (insertPos - RECORD_SIZE)[2]) {
            uint* prev = insertPos - RECORD_SIZE;
            for (int i = 0; i < RECORD_SIZE; ++i) {
                insertPos[i] = prev[i];
            }
            insertPos = prev;
        }

        // Place temp record into correct position
        for (int i = 0; i < RECORD_SIZE; ++i) {
            insertPos[i] = temp[i];
        }

        cur += RECORD_SIZE;
    }
}