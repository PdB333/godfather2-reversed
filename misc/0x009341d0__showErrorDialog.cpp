// FUNC_NAME: showErrorDialog
// Function at 0x009341d0: Creates and displays a UI error dialog based on error type.
// Uses a structure of size 0xF0 (240 bytes) allocated via operator new.
// Structure offsets: +0x0C = someFlag (set to 1), +0x14 = callback function pointer (set to label address for button press).
// Strings are localization keys (e.g., "$ui_pro_error_read").

#include <cstdint>

// Forward declarations of called functions (assumed to be in UI system)
void* operatorNew(uint32_t size); // FUN_009c8e50
void dialogConstructor(void* dialog, int param); // FUN_00982280
void setDialogTitle(const char* key); // FUN_00981ec0
void setDialogMessage(const char* key); // FUN_00981eb0
void setDialogFlags(int flags); // FUN_00982400
void showDialog(); // FUN_00982e10

// External label addresses for callbacks (likely function pointers)
extern void* LAB_009333f0; // for save error
extern void* LAB_00933350; // for save corrupt
extern void* LAB_009333a0; // for other errors

int showErrorDialog(int errorType)
{
    void* dialogObj;
    const char* titleKey;

    switch (errorType) {
        case 0: // Read error
        case 1: // Close error
        case 4: // Find error
        case 5: // Delete error
        case 6: // Delete folder error
        {
            dialogObj = operatorNew(0xF0);
            if (dialogObj != nullptr) {
                dialogConstructor(dialogObj, 0);
            }
            *(int*)((uintptr_t)dialogObj + 0x0C) = 1; // Set some flag
            setDialogTitle("$ui_pro_error_read"); // placeholder, will be overridden below
            titleKey = "$ui_pro_error_read";
            break;
        }
        case 2: // Save error
        {
            dialogObj = operatorNew(0xF0);
            if (dialogObj != nullptr) {
                dialogConstructor(dialogObj, 0);
            }
            *(int*)((uintptr_t)dialogObj + 0x0C) = 1;
            setDialogTitle("$ui_pro_error_close"); // Note: title set to close? Possibly a bug or reused string
            titleKey = "$ui_pro_error_close";
            break;
        }
        case 3: // Save error (different handling)
        {
            dialogObj = operatorNew(0xF0);
            if (dialogObj != nullptr) {
                dialogConstructor(dialogObj, 0);
            }
            *(int*)((uintptr_t)dialogObj + 0x0C) = 1;
            setDialogTitle("$ui_pro_error_save");
            setDialogMessage("$ui_pro_error_save");
            setDialogFlags(1);
            *(void**)((uintptr_t)dialogObj + 0x14) = &LAB_009333f0; // Set callback
            showDialog();
            return 0;
        }
        case 7: // Save corrupt
        {
            dialogObj = operatorNew(0xF0);
            if (dialogObj != nullptr) {
                dialogConstructor(dialogObj, 0);
            }
            *(int*)((uintptr_t)dialogObj + 0x0C) = 1;
            setDialogTitle("$ui_pro_save_corrupt");
            setDialogMessage("$ui_pro_save_corrupt");
            setDialogFlags(1);
            *(void**)((uintptr_t)dialogObj + 0x14) = &LAB_00933350; // Set callback
            showDialog();
            return 0;
        }
        default:
            return 1; // Unknown error type
    }

    // For cases 0,1,4,5,6 (and also case 2 which falls through)
    setDialogMessage(titleKey);
    setDialogFlags(1);
    *(void**)((uintptr_t)dialogObj + 0x14) = &LAB_009333a0; // Set default callback
    showDialog();
    return 0;
}