// FUNC_NAME: ControllerManager::runActiveControllerLoop
// Address: 0x0078f260
// This function appears to be the main loop for processing a single active controller slot.
// It runs until shutdown, processing one slot per iteration. The controller data is stored
// in an array at this+0xB4, each slot being 0x10 bytes (8 slots total: offsets 0xB4, 0xC4, ... 0x124).

void __thiscall ControllerManager::runActiveControllerLoop(void* param_2) {
    char isShutdown;
    int slotIndex;

    // Initialize the controller context (param_2 points to a context object)
    initControllerContext(param_2);
    // Set context name to "Controller" (constant string at 0x00e965b5)
    setControllerContextName(param_2, "Controller");

    // Loop until shutdown is signaled
    while (true) {
        isShutdown = isInputShutdown(); // returns non-zero if shutdown requested
        if (isShutdown != 0) {
            return;
        }

        // Global per-frame update (no slot context)
        updateControllerFrame();

        // Get the currently active slot index (0-7)
        slotIndex = getActiveControllerSlot();

        // Pointer to the specific slot data
        ControllerSlot* slotData = nullptr;
        switch (slotIndex) {
        case 0:
            slotData = (ControllerSlot*)(this + 0xB4);
            break;
        case 1:
            slotData = (ControllerSlot*)(this + 0xC4);
            break;
        case 2:
            slotData = (ControllerSlot*)(this + 0xD4);
            break;
        case 3:
            slotData = (ControllerSlot*)(this + 0xE4);
            break;
        case 4:
            slotData = (ControllerSlot*)(this + 0xF4);
            break;
        case 5:
            slotData = (ControllerSlot*)(this + 0x104);
            break;
        case 6:
            slotData = (ControllerSlot*)(this + 0x114);
            break;
        case 7:
            slotData = (ControllerSlot*)(this + 0x124);
            break;
        default:
            goto endOfLoop;
        }

        // Update the specific slot
        updateControllerSlot(slotData);
        // Handle slot events/messages
        handleControllerSlot(slotData);

endOfLoop:
        // End-of-frame processing
        finalizeControllerFrame();

        // Check shutdown again before next iteration
        isShutdown = isInputShutdown();
    }
}