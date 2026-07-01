// Xbox PDB: EARS_Apt_LobbyParams_ShowOrHideSideArrows
// FUNC_NAME: UIMenu::updateArrowButtons
// Function at 0x0095e7d0 - Controls visibility of left/right navigation arrows in a menu or carousel.
// Calls shouldShowRightArrow() and shouldShowLeftArrow() to determine state, then uses sendUICommand() to show/hide.

void __thiscall UIMenu::updateArrowButtons(int this) // this is param_1
{
    char showRight;
    char showLeft;

    // Check if we should show the right arrow
    showRight = shouldShowRightArrow(this); // FUN_0095e6c0
    if (showRight == '\0') {
        // Hide right arrow
        sendUICommand("HideRightArrow", 0, &DAT_00d8cdec, 0); // FUN_005a04a0 - DAT_00d8cdec likely a global or member UI context
    } else {
        // Show right arrow
        sendUICommand("ShowRightArrow", 0, &DAT_00d8cdec, 0);
    }

    // Check if we should show the left arrow
    showLeft = shouldShowLeftArrow(this); // FUN_0095e5e0
    if (showLeft != '\0') {
        // Show left arrow (and return early, so if left is shown, we don't then hide it)
        sendUICommand("ShowLeftArrow", 0, &DAT_00d8cdec, 0);
        return;
    }

    // Hide left arrow
    sendUICommand("HideLeftArrow", 0, &DAT_00d8cdec, 0);
}