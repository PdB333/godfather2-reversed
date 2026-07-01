//FUNC_NAME: UIMessageHandler::handleUIMessage
void __thiscall UIMessageHandler::handleUIMessage(int this, UIMessage* message)
{
    int messageType;
    int playerPtr;
    int uiManagerPtr;
    // Stack variables for building a formatted message
    Vector3D messagePos;
    Vector3D screenPos;
    int someFlag;
    int color;
    int font;
    int texture;

    // Get the message type hash from the message object (virtual function call)
    messageType = message->getTypeHash();

    if (messageType == 0x99b244e) {
        // Handle message type: e.g., "play sound" or "show simple notification"
        uiManagerPtr = getUIManager();
        showMessage(uiManagerPtr + 0x4c); // Offset 0x4c likely points to a UI element or sound slot
        return;
    }

    if (messageType == 0x27a0f69c) {
        // Handle message type: e.g., "display hint with player context"
        if (*(int*)(this + 0x58) != 0) { // Check some state flag at +0x58
            playerPtr = getPlayer();
            // Read player's position or orientation from player object at offsets +0x30 and +0x38
            messagePos.x = *(float*)(playerPtr + 0x30);
            messagePos.y = *(float*)(playerPtr + 0x34);
            messagePos.z = *(float*)(playerPtr + 0x38);

            // Choose texture based on a state at this+0x18c
            if (*(int*)(this + 0x18c) == 0x2b) { // 0x2b = 43, maybe a specific mission or state
                texture = DAT_00e446bc; // Special texture
            } else {
                texture = DAT_00e446f4; // Default texture
            }

            // Get player's screen position or another vector from player at +0x20 and +0x28
            playerPtr = getPlayer();
            screenPos.x = *(float*)(playerPtr + 0x20);
            screenPos.y = *(float*)(playerPtr + 0x24);
            screenPos.z = *(float*)(playerPtr + 0x28);

            someFlag = 0;
            color = _DAT_00d5780c; // Color value
            font = 0;

            // Build a formatted message string using the positions and texture
            formatMessageString(&screenPos, &screenPos, &someFlag, texture);

            // Display the hint on screen with the message position, screen position, font, and other parameters
            displayHint(&messagePos, &screenPos, 0, DAT_00d5ef88, 0, 1);
        }
    } else if (messageType == 0x6bda3054) {
        // Handle message type: e.g., "update UI state"
        if (*(int*)(this + 0x188) == 0) {
            uiManagerPtr = getUIManager();
            setUIState(uiManagerPtr + 0x6c); // Offset 0x6c - state 0
            return;
        }
        if (*(int*)(this + 0x188) != 1) {
            uiManagerPtr = getUIManager();
            setUIState(uiManagerPtr + 0xbc); // Offset 0xbc - other state
            return;
        }
        uiManagerPtr = getUIManager();
        setUIState(uiManagerPtr + 0x94); // Offset 0x94 - state 1
        return;
    }
    // If no matching message type, do nothing
}