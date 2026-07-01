// FUNC_NAME: VideoOptionsMenu::applyResolutionSelection
void __fastcall VideoOptionsMenu::applyResolutionSelection(int this)
{
    uint currentSelection;
    char selectionString[4]; // actually a buffer for formatted string
    char isDisabled[256];

    // Close any open selection
    sendMenuCommand("CloseSelection", 0, &gMenuContext, 0);

    currentSelection = *(uint *)(this + 0x54); // +0x54: current selection index

    if (*(int *)(this + 0x58) == 0) // +0x58: state flag (0 = initializing)
    {
        // Set rendering parameters (gamma, brightness, etc.)
        setGamma(1.0f);
        setBrightness(1.0f);
        setContrast(0);
        setSaturation(0);
        *(byte *)(this + 0x10c) = 1; // +0x10c: some flag (e.g., "settingsApplied")
        updateDisplay();
    }
    else if (*(int *)(this + 0x58) == 1) // +0x58: state flag (1 = applying resolution)
    {
        // Set resolution to 1024x768 @ 60Hz
        *(int *)(this + 0x114) = 0x400; // +0x114: width
        *(int *)(this + 0x110) = 0x300; // +0x110: height
        *(int *)(this + 0x118) = 0x3c;  // +0x118: refresh rate (60)
        *(int *)(this + 0x78) = 0;      // +0x78: some flag (e.g., windowed)
        *(int *)(this + 0x70) = 0;      // +0x70: another flag
        setFullscreen(0);               // set windowed mode
        *(int *)(this + 0x7c) = 1;      // +0x7c: flag (e.g., "resolutionChanged")
        setVideoMode(3);                // apply video mode
        sendMenuCommand("DisableAdvancedOptions", 0, &gMenuContext, 0);
        *(byte *)(this + 0x10d) = 1;    // +0x10d: flag (e.g., "advancedDisabled")
        refreshMenu();

        // Format resolution string
        sprintf((char *)(this + 0xc4), "%d x %d @ %dHz",
                *(int *)(this + 0x114), *(int *)(this + 0x110), *(int *)(this + 0x118));

        // Loop to find a non-disabled selection
        formatSelectionString(selectionString, &gResolutionFormat, currentSelection);
        isDisabled[0] = '\0';
        sendMenuCommand("IsSelectionDisabled", isDisabled, &gMenuContext, 1, selectionString);
        while (isDisabled[0] == '1')
        {
            currentSelection = ((*(uint *)(this + 0x60) - 1) + currentSelection) % *(uint *)(this + 0x60);
            formatSelectionString(selectionString, &gResolutionFormat, currentSelection);
            isDisabled[0] = '\0';
            sendMenuCommand("IsSelectionDisabled", isDisabled, &gMenuContext, 1, selectionString);
        }
    }

    // Close selection and finalize
    sendMenuCommand("CloseSelection", 0, &gMenuContext, 0);
    setCurrentSelection(currentSelection);
    finalizeMenu();
}