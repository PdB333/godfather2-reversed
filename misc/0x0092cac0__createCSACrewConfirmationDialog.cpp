// FUNC_NAME: createCSACrewConfirmationDialog
// Address: 0x0092cac0
// Creates and shows a "Are you sure?" confirmation dialog for the CSA (Crew Situation Awareness) system.
// Uses a dynamically allocated dialog structure (0xF0 bytes) with preset field values and a callback.

// Known offsets in the dialog structure (size 0xF0):
// +0x0C: uint32 - dialog state (set to 2 = confirmation type)
// +0x14: function pointer - confirmation callback (to 0x0092BE20)
// +0x1C: uint32 - constant ID or flag (0x997DEE17)
// +0x20: uint32 - constant ID or flag (0xB9754031)

struct CSADialog;
typedef void (*CSADialogCallback)(CSADialog*);

// External helper functions (EA EARS engine)
extern CSADialog* AllocDialog(uint32_t size);                    // 0x009c8e50
extern int32_t InitDialog(CSADialog* dialog, int32_t param);    // 0x00982280 (param is 0 here)
extern void SetDialogString(const char* stringKey);              // 0x00981eb0 (sets localized string for the dialog)
extern void ShowDialog(CSADialog* dialog);                       // 0x00982e10

void createCSACrewConfirmationDialog()
{
    CSADialog* dialog;

    // Allocate dialog structure (0xF0 bytes)
    dialog = AllocDialog(0xF0);

    // If allocation succeeded, initialize it (possibly constructor)
    if (dialog != nullptr)
        InitDialog(dialog, 0);  // second parameter 0 may indicate no parent or default

    // Set the localized string key (actual string retrieved later in ShowDialog)
    SetDialogString("$hud_csa_are_you_sure");

    // Initialize dialog fields
    *(uint32_t*)((char*)dialog + 0x0C) = 2;                     // +0x0C: dialog type/state (2 = confirmation)
    *(uint32_t*)((char*)dialog + 0x20) = 0xB9754031;            // +0x20: some unique identifier or flags
    *(uint32_t*)((char*)dialog + 0x1C) = 0x997DEE17;            // +0x1C: another constant (perhaps for layout/presentation)
    *(CSADialogCallback*)((char*)dialog + 0x14) = (CSADialogCallback)0x0092BE20; // +0x14: callback pointer (confirm action)

    // Display the dialog
    ShowDialog(dialog);
}