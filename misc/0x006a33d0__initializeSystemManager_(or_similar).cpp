// FUNC_NAME: initializeSystemManager (or similar)
// Address: 0x006a33d0
// Role: Lazy initialization of a singleton manager with a linked list cleanup and callback registration.

void __fastcall initializeSystemManager(int *initGuard)
{
    undefined **ppuVar1;
    int allocResult;
    undefined4 callbackParam;
    undefined **ppuListHead;

    // If the guard pointer is null (not initialized yet)
    if (*initGuard == 0) {
        // Traverse the circular doubly linked list at PTR_LOOP_00e50c80 (sentinel)
        ppuListHead = (undefined **)PTR_LOOP_00e50c80;
        if ((undefined **)PTR_LOOP_00e50c80 != &PTR_LOOP_00e50c80) {
            do {
                ppuVar1 = (undefined **)*ppuListHead;
                // Call cleanup/destructor on each node
                FUN_009c8f10(ppuListHead);
                ppuListHead = ppuVar1;
            } while (ppuVar1 != &PTR_LOOP_00e50c80);
        }
        // Reset the list: both head and tail point to sentinel
        PTR_LOOP_00e50c80 = (undefined *)&PTR_LOOP_00e50c80;  // head
        PTR_PTR_LOOP_00e50c84 = (undefined *)&PTR_LOOP_00e50c80; // tail
        // Set version/status to 6
        DAT_00e50c7c = 6;

        // Allocate memory (size 4) - possibly for a new manager object
        allocResult = FUN_009c8e50(4);
        if (allocResult == 0) {
            allocResult = 0;
        }
        else {
            allocResult = FUN_00ab54d0(); // constructor / initializer
        }
        *initGuard = allocResult; // store the result

        // Get a parameter (maybe a version or handle)
        callbackParam = FUN_00ab5470();
        // Register a callback function (LAB_006a3000) with extra parameters
        FUN_00ab7410(&LAB_006a3000, 0, 0, callbackParam);
    }
}