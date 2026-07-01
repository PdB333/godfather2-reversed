// FUNC_NAME: MenuInputHandler::processMenuInput
void __thiscall MenuInputHandler::processMenuInput(MenuPanel* menuPanel) {
    // Initialize the menu UI and associate it with a specific menu identifier (hash constant)
    initializeMenuUI(menuPanel);
    setMenuIdentifier(menuPanel, 0x29a3abfc); // Likely a hash for the menu type

    // Wait until the input system signals that input events are ready to be processed
    bool inputReady = isMenuInputReady();
    while (!inputReady) {
        // Poll for the next input event type
        int eventType = getInputEventType();

        if (eventType == 0) {
            // Event type 0: store the event's data at offset +8 into member at +0x210
            InputEvent* event = getNextInputEvent();
            m_menuSelectionData = event->data08; // offset +8
        }
        else if (eventType == 1) {
            // Event type 1: interpret the event's data at +8 as a navigation direction
            InputEvent* event = getNextInputEvent();
            int direction = event->data08; // offset +8
            if (direction == 0) {
                m_menuNavigationDelta = -1; // left/up
            }
            else if (direction == 1) {
                m_menuNavigationDelta = 0;  // no change/select
            }
            else if (direction == 2) {
                m_menuNavigationDelta = 1;  // right/down
            }
        }

        // Release the processed event
        releaseInputEvent();

        // Re-check input readiness
        inputReady = isMenuInputReady();
    }
}