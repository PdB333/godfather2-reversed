// FUNC_NAME: NetworkPacketSlot::Initialize
void __fastcall NetworkPacketSlot::Initialize(void *this, int *list1Head, int *list2Head, int param4)
{
    // this is in ESI
    int *slot = (int *)this;
    slot[1] = 0;                          // +0x04: unknown, init to 0
    slot[0] = (int)&PTR_FUN_00e407c4;     // +0x00: vtable pointer

    // --- Insert into first linked list (list1Head) ---
    int *list1First = (int *)*list1Head;  // head of list1
    slot[2] = (int)list1First;            // +0x08: store old first node pointer
    slot[3] = 0;                          // +0x0C: next pointer in list1?, init 0
    if (list1First != 0)
    {
        slot[3] = list1First[1];          // +0x04 of old first = its next
        list1First[1] = (int)&slot[2];    // old first's next points to slot's +0x08
    }

    // --- Insert into second linked list (list2Head) ---
    slot[4] = list1Head[2];               // +0x10: some value from list1Head[2]
    int *list2First = (int *)*list2Head;  // head of list2
    slot[5] = (int)list2First;            // +0x14: store old first
    slot[6] = 0;                          // +0x18: next pointer in list2?, init 0
    if (list2First != 0)
    {
        slot[6] = list2First[1];          // +0x04 of old first = its next
        list2First[1] = (int)&slot[5];    // old first's next points to slot's +0x14
    }

    // --- Other fields ---
    slot[7] = list1Head[2];               // +0x1C: duplicate of slot[4]?
    slot[8] = param4;                     // +0x20: parameter 4
    slot[10] = 0;                         // +0x28
    slot[0xC] = 0;                        // +0x30
    slot[0xD] = 0;                        // +0x34
    slot[0xE] = 0;                        // +0x38
    slot[0xF] = DAT_00e2e50c;             // +0x3C: global constant
    slot[0x10] = 0;                       // +0x40
    slot[0x11] = 0;                       // +0x44

    // --- Memory allocation using a global object ---
    int *globalObj = (int *)DAT_01223520;           // global pointer to some manager
    slot[0xB] = *(int *)((int)globalObj + 0x20);   // +0x2C: copy from global+0x20

    local_c = 0; local_8 = 0; local_4 = 0;         // local variables for allocation call
    int size = *(int *)((int)globalObj + 0x20) * 12;  // size = count * 12
    int (*allocFunc)(int, void *) = *(int (**)(int, void *))(*(int *)((int)globalObj + 0x10)); // vtable call
    int allocResult = allocFunc(size, &local_c);   // allocate memory
    slot[9] = allocResult;                        // +0x24: store allocation pointer

    if (allocResult == 0)
    {
        slot[0xE] |= 0x84;                        // +0x38: set flags if allocation failed
    }

    slot[0x13] = 0x9000;   // +0x4C: some constant
    slot[0x12] = 0x8000;   // +0x48: another constant
}