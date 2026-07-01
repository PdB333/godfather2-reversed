// FUNC_NAME: shutdownGameSystems

extern void* DAT_0112db98; // pointer to some manager object with vtable
extern void* DAT_0112db84; // pointer to another manager object
extern int DAT_0112dbc0;   // flag or pointer indicating some system is active
extern int* DAT_0112dbbc;  // pointer to a reference-counted object (first int is vtable, second is ref count)

// Forward declarations of cleanup functions
void FUN_008240d0(void);
void FUN_004df830(int param);
void FUN_004df600(void);
void FUN_009d5260(void);

void shutdownGameSystems(void)
{
    // Release first manager if it exists (call vtable[0] with arg 1, likely Release)
    if (DAT_0112db98 != (void*)0x0) {
        (*(void (**)(int))(*DAT_0112db98))(1);
    }

    // Release second manager if it exists
    if (DAT_0112db84 != (void*)0x0) {
        (*(void (**)(int))(*DAT_0112db84))(1);
    }

    // Call general cleanup function
    FUN_008240d0();

    // If a certain system is active (DAT_0112dbc0 non-zero), shut it down
    if (DAT_0112dbc0 != 0) {
        FUN_004df830(0);
        FUN_004df600();
    }

    // Handle reference-counted object at DAT_0112dbbc
    int* piVar1 = DAT_0112dbbc;
    if (DAT_0112dbbc != (int*)0x0) {
        // Decrement reference count at offset +4
        DAT_0112dbbc[1] = DAT_0112dbbc[1] - 1;
        if (piVar1[1] == 0) {
            // If ref count reached zero, call destructor via vtable[1]
            (*(void (**)(void))(*piVar1 + 4))();
        }
        // Clear the global pointer
        DAT_0112dbbc = (int*)0x0;
    }

    // Final cleanup
    FUN_009d5260();
    return;
}