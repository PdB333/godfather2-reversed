// FUN_00468680: PacketProcessor::processNextEntry
// Role: Reads next data entry from a typed buffer. Supports type 3 (conditional with extra check) and type 4 (direct). Allocates and processes a result buffer.
// Address: 0x00468680

int PacketProcessor::processNextEntry() {
    int* current = *(int**)(this + 0xC);  // +0xC: current read pointer
    int* end     = *(int**)(this + 0x8);  // +0x8: end of buffer pointer (exclusive)
    int result = 0;

    // Check if there is data available
    if (current < end && current != nullptr) {
        int type = *current;  // first word is type tag

        if (type == 4) {
            // Type 4: direct offset from next word
            result = current[1] + 0x10;
        }
        else if (type == 3) {
            // Type 3: conditional; check additional condition
            int checkResult = FUN_00633990(this);  // likely checks some flag/state
            if (checkResult != 0) {
                result = current[1] + 0x10;
            }
            // else result remains 0

            // Extra guard: if another structure indicates overflow, trigger debug break
            int* otherStruct = *(int**)(this + 0x10);  // +0x10: pointer to secondary structure
            if (*(uint*)(otherStruct + 0x20) <= *(uint*)(otherStruct + 0x24)) {
                FUN_00627360();  // debug assertion / breakpoint
            }
        }
        // 'type' is guaranteed to be 3 or 4 by outer condition
    }

    // Allocate and process the result buffer (even if result==0)
    void* buffer = FUN_004dafd0(result);  // allocate buffer of given size
    FUN_004564f0(buffer);                  // process the buffer
    return 0;
}