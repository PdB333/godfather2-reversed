// FUNC_NAME: GameManager::processUpdateLists
void GameManager::processUpdateLists()
{
    // Global linked list heads
    int* g_pFirstListHead  = (int*)0x01205490;  // first list: next at +0x8
    int* g_pSecondListHead = (int*)0x01205480;  // second list: next at +0x88

    // Process first list: call FUN_004a7020 on each element
    int* current = g_pFirstListHead;
    if (current != 0) {
        do {
            FUN_004a7020(current);              // unknown processing function
            current = *(int**)(current + 2);     // next pointer at offset +8 (index 2 in int*)
        } while (current != 0);
    }

    // Process second list: call virtual method at vtable+0x2c
    int* node = g_pSecondListHead;
    while (node != 0) {
        // vtable pointer is at offset 0, method at +0x2c
        void (**vtable)() = *(void (***)())node;
        vtable[0x2c / 4]();                     // virtual call (__thiscall assumed)

        // Move to next node via pointer stored at +0x88 (index 0x22)
        node = *(int**)(node + 0x22);
    }
}