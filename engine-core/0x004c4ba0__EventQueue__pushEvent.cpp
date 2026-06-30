// FUNC_NAME: EventQueue::pushEvent
void __thiscall EventQueue::pushEvent(int param_1, int param_2, int param_3, int param_4) {
    // this: in_EAX
    int currentCount = *(int *)(this + 0x38); // +0x38: current number of queued events
    int capacity = *(int *)(this + 0x34);     // +0x34: maximum capacity

    if (currentCount < capacity) {
        *(int *)(this + 0x38) = currentCount + 1; // increment count
        *(char *)(this + 0x18) = 0;                // +0x18: clear flag byte

        int entryOffset = currentCount * 0x20; // each entry is 32 bytes
        int *entryBase = *(int **)(this + 0x10); // +0x10: pointer to array of 0x20-sized entries

        int result = FUN_004c4a10(param_1); // allocate or copy based on param_1
        entryBase[entryOffset / 4] = result; // store at entry offset 0

        FUN_004c4cb0(currentCount, param_1, param_4, param_2, param_3); // additional initialization

        if (*(char *)(this + 0x3c) != 0) { // +0x3c: flag to do extra processing
            int *array = *(int **)(this + 0x10);
            int val1 = array[entryOffset / 4]; // first dword of entry
            int res1 = FUN_004c4610(val1, this + 0x24); // +0x24: some base offset
            int val2 = array[(entryOffset / 4) + 1]; // second dword of entry (offset 4)
            int res2 = FUN_004c4610(val2, res1 + 0xc);
            FUN_004c4730(this, res2 + 0xc);
        }
    }
}