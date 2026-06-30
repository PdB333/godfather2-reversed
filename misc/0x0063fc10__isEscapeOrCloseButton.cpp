// FUNC_NAME: isEscapeOrCloseButton
int __cdecl isEscapeOrCloseButton(int actionId)
{
    // Check if the action ID corresponds to a cancel/close event.
    // These constants likely correspond to specific UI button codes
    // for back/escape actions (e.g., escape key, right-click, back button).
    switch (actionId)
    {
    case 0x104: // E.g., UI_ACTION_ESCAPE
    case 0x105: // UI_ACTION_CANCEL
    case 0x106: // UI_ACTION_CLOSE
    case 0x114: // UI_ACTION_BACK_ALT
    case 0x11f: // UI_ACTION_EXIT
        return 1;
    default:
        return 0;
    }
}