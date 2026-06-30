// FUNC_NAME: InputManager::processBuffers

// Function at 0x005121b0: Processes input buffers from a global input manager object.
// This function retrieves raw input data (likely from controllers), checks a flag,
// potentially calls an update/reset function, then forwards the buffers to another subsystem.
// 
// Global pointer g_inputManager (DAT_0121b0ac) is a singleton object with fields:
// +0x0C : bool32 flag (likely "hasData" or "needsProcess")
// +0x10 : pointer to buffer A (28 bytes)
// +0x14 : pointer to buffer B (16 bytes)
//
// g_inputStateManager (DAT_0121a394) is another global manager for final input distribution.

void InputManager::processBuffers()
{
    uint8_t bufferA[28];  // 0x1C bytes - e.g., controller axis/button states
    uint8_t bufferB[16];  // 0x10 bytes - e.g., D-pad or digital actions

    // Retrieve current raw input data from hardware or low-level layer
    getRawInput(bufferB, bufferA);

    // If the manager has pending data to process (e.g., event queue flush needed)
    if (g_inputManager->needsProcess != 0)
    {
        processPendingEvents();
    }

    // Send the smaller buffer (16 bytes) to the input state manager
    // Offset +0x14 likely stores a key for this buffer (e.g., device index or priority)
    pushInputToManager(g_inputStateManager, g_inputManager->bufferBKey, bufferB);

    // Send the larger buffer (28 bytes) with its associated key
    pushInputToManager(g_inputStateManager, g_inputManager->bufferAKey, bufferA);
}