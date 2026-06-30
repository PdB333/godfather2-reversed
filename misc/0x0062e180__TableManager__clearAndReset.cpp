// FUNC_NAME: TableManager::clearAndReset
int TableManager::clearAndReset() {
    int* currentPtr = *(int**)(this + 0x8);  // +0x8: current node pointer
    int* endPtr = *(int**)(this + 0xC);      // +0xC: end node pointer

    // If the table appears uninitialized or the first node tag isn't 5, fetch the global table
    if ((endPtr <= currentPtr) || (currentPtr == nullptr) || (*currentPtr != 5)) {
        // The function retrieves a global table descriptor; returns start in EAX, end via ECX (register pair)
        // We treat it as returning two values through a struct or side effect.
        TableDescriptor* desc = (TableDescriptor*)FUN_00627ac0(PTR_s_table_00e2a8b0);
        currentPtr = desc->start;  // start address
        endPtr = desc->end;        // end address (originally from extraout_ECX)
    }

    // Clear all 8-byte entries from current to endPtr + 0x10 (two sentinel entries)
    while ((unsigned int)(this + 0x8) < (unsigned int)(endPtr + 0x4)) { // keep track of offset? actually the while uses *(param_1+8) as uint
        **(int**)(this + 0x8) = 0;              // write 0 (4 bytes) to the node's first field
        *(int*)(this + 0x8) = *(int*)(this + 0x8) + 8; // advance by 8 bytes per entry
    }

    // Reset the current pointer to just past the end region (reserve two extra slots)
    *(int*)(this + 0x8) = (int)(endPtr) + 0x10;

    int status = FUN_00637650();  // checks if there is space for more entries
    if (status == 0) {
        // No space: move back one entry and write a null terminator
        *(int*)(this + 0x8) = *(int*)(this + 0x8) - 8;
        **(int**)(this + 0x8) = 0;
        return 1;
    }
    // There is space: advance one more entry and return 2
    *(int*)(this + 0x8) = *(int*)(this + 0x8) + 8;
    return 2;
}