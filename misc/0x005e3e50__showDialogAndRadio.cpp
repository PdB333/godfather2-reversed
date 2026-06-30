// FUNC_NAME: showDialogAndRadio
void showDialogAndRadio(int dialogId) {
    // Debug output strings
    const char* dialogType1 = "DIALOG";
    const char* dialogType2 = "RADIO";  // Assuming DAT_00e3f500 is "RADIO"

    // Global DialogManager instance pointer (likely from BSS)
    // It's passed as the first argument to dialog creation function
    void* gDialogManager = (void*)0x01223508;  // Pointer to DialogManager singleton

    // Function pointer for destructor (likely stored in vtable or struct)
    // local_4 and local_10 are temporary variables from the decompiler
    // They represent a dialog object and its associated destructor function
    // The pattern shows creation then immediate destruction.
    // This might be a test or initialization sequence.

    // Create and immediately destroy a DIALOG object
    debugPrint(dialogType1);
    void* dialogObj = dialogManagerCreateDialog(gDialogManager, dialogId);
    if (dialogObj != 0) {
        // Destroy the dialog via its destructor
        #ifdef DESTRUCTOR_STYLE
        // Assuming the destructor function is stored alongside the object
        // (e.g., in a struct with a function pointer)
        void (*destructor)(void*) = (void (*)(void*))&dialogObj[0]; // hypothetical
        destructor(dialogObj);
        #else
        // Direct call to a known cleanup function
        cleanupDialog(dialogObj);
        #endif
    }

    // Create and immediately destroy a RADIO object
    debugPrint(dialogType2);
    dialogObj = dialogManagerCreateDialog(gDialogManager, dialogId);
    if (dialogObj != 0) {
        // Destroy the radio dialog via its destructor
        // (same pattern)
        #ifdef DESTRUCTOR_STYLE
        void (*destructor)(void*) = (void (*)(void*))&dialogObj[0];
        destructor(dialogObj);
        #else
        cleanupDialog(dialogObj);
        #endif
    }
}

// Placeholder for debug output function (address 0x004d3bc0)
void debugPrint(const char* message);

// Placeholder for dialog creation function (address 0x005dc3d0)
// Returns a pointer to the created dialog object (handle), or 0 on failure
void* dialogManagerCreateDialog(void* manager, int dialogId);

// Placeholder for cleanup/destructor of dialog (if not using function pointer)
void cleanupDialog(void* dialog);