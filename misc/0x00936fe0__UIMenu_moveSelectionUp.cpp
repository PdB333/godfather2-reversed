// FUNC_NAME: UIMenu_moveSelectionUp

#include <cstdint>

// Global variables
extern void* g_currentMenu;          // DAT_00d8a0dc: pointer to current menu context
extern int32_t g_selectedIndex;      // DAT_011302b0: current selected index

// Forward declarations of called functions (addresses 0x005a04a0 and 0x00408a00)
extern void UICommand_Send(const char* command, int32_t arg1, void** menuContext, int32_t arg3);
extern void UICommand_ApplySelectionOffset(void* selectionState, int32_t arg2);

// Structure matching the local variables in decompiled code
struct SelectionState {
    int32_t index;   // +0x00 (local_c)
    int32_t offset;  // +0x04 (local_8)
    uint8_t flags;   // +0x08 (local_4)
};

void UIMenu_moveSelectionUp(void) {
    // Send the "MoveSelectionUp" command to the current menu context
    UICommand_Send("MoveSelectionUp", 0, &g_currentMenu, 0);
    
    // Build a selection state from the global selected index
    SelectionState state;
    state.index = g_selectedIndex;
    state.offset = 0;
    state.flags = 0;
    
    // Apply the selection change (move up)
    UICommand_ApplySelectionOffset(&state, 0);
}