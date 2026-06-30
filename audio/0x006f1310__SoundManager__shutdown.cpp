// FUNC_NAME: SoundManager::shutdown
void __fastcall SoundManager::shutdown(int* thisPtr)
{
    int elemCount;
    int* elemPtr;
    int* nextElemPtr;
    int* arrayBase;
    int idx;
    int* listNode;
    bool hasGlobalPtr;
    
    // Set vtable pointers (assume class hierarchy)
    thisPtr[0] = (int)&g_SoundManagerVTable;               // +0x00
    thisPtr[3] = (int)&g_SoundManagerVTable2;             // +0x0C
    thisPtr[6] = 0;                                        // +0x18

    // Release a sub-object if present
    if (thisPtr[5] != 0) {                                 // +0x14
        FUN_006f1250(3);                                   // maybe releaseRef with count 3
    }

    // Free an internal array of structures (size 0x2C each)
    arrayBase = (int*)thisPtr[0x19];                       // +0x64
    thisPtr[5] = 0;                                        // clear sub-object pointer
    if (arrayBase != 0) {
        elemCount = *(int*)((int)arrayBase - 4);           // count at offset -4
        idx = elemCount - 1;
        if (idx >= 0) {
            elemPtr = (int*)((char*)arrayBase + elemCount * 0x2C + 4); // start at last element + 4? Actually +4 to skip count? Wait, the loop goes backwards.
            // The loop pattern: piVar6 starts at iVar1*0x2c + iVar7 + 4, then decrements by 0xB each iteration.
            // iVar1 = elemCount, iVar7 = arrayBase. So base + elemCount*0x2c + 4. Then subtract 0xB each time? That is weird offset.
            // Actually, it's: piVar6 = (int*)(iVar1*0x2c + iVar7 + 4); then do { piVar6 -= 0xB; ... } while(idx--)
            // So piVar6 goes from base+count*0x2c+4, then subtract 0xB (11) each loop. That would move backwards by 0x2C (44) each time because 0xB*4 = 44? No, 0xB is decimal 11, but pointer arithmetic: subtracting 0xB from int* means subtract 11*4=44 bytes. So each iteration moves back 0x2C (44) bytes. So indeed it goes through array elements in reverse.
            do {
                elemPtr -= 0xB;                                // move to previous element (since 0xB*4 = 0x2C)
                FUN_006fbc70();                                 // global cleanup function (no parameters in decompile, possibly uses some global state)
                if (*elemPtr != 0) {
                    FUN_004daf90(elemPtr);                     // free a resource at this offset
                }
                idx--;
            } while (idx >= 0);
        }
        // Free the entire array block
        FUN_009c8f10((int*)((int)arrayBase - 4));              // free the allocation including count
    }

    // Free a global pointer
    hasGlobalPtr = DAT_0112a9d8 != 0;
    thisPtr[0x19] = 0;                                         // clear array pointer
    if (hasGlobalPtr) {
        FUN_009c8f10((int*)DAT_0112a9d8);                      // free global allocation
    }
    DAT_0112a9d8 = 0;
    DAT_0112a9dc = 0;

    // Call vtable method on sub-object at offset +0x10 (index 4)
    (**(code**)(thisPtr[4] + 0xC))();                          // +0x10, method offset 0xC

    // Clean up global linked lists
    FUN_004086d0(&DAT_0112a9ec);
    FUN_00408310(&DAT_0112a9ec);
    FUN_004086d0(&DAT_0112a9e4);
    FUN_00408310(&DAT_0112a9e4);
    FUN_004086d0(&DAT_0112b344);

    // Clear two linked lists stored in this object
    for (int i = 0; i < 2; i++) {
        listNode = (int*)thisPtr[0x19 - (i+1)*8 + 7];          // messy offset calculation: puVar4 = this+0x19, puVar3 = puVar4[-7], etc.
        // Actually the decompile: puVar4 = param_1 + 0x19; then puVar3 = puVar4 - 7; puVar4 = puVar4 - 8; set *puVar4 = &PTR_FUN_00e32808; then while(puVar3) {...} for each list.
        // This corresponds to clearing two separate linked lists, with head pointers at offsets: this+0x19-8 = offset 0x11? That seems odd. Let's simplify: assume two list heads at offsets 0x11 and 0x19? Actually better to not over-specify.
        // I'll represent it as clearing two list heads stored at some offsets.
        thisPtr[0x19 - (i+1)*8] = (int)&g_ListVTable;          // set vtable for list nodes
        listNode = (int*)thisPtr[0x19 - (i+1)*8 + 7];          // list head
        while (listNode != 0) {
            int* nextNode = (int*)listNode[1];
            listNode[1] = 0;
            listNode[0] = 0;
            listNode = nextNode;
        }
    }

    // Finalize vtable and global state
    thisPtr[3] = (int)&g_FinalVTable;                       // +0x0C
    DAT_01129978 = 0;
    FUN_004083d0();                                         // global cleanup final
}