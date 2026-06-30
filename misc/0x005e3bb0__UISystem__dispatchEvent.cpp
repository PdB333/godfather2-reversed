// FUNC_NAME: UISystem::dispatchEvent
void UISystem_dispatchEvent(int targetHandle, int eventData) {
    // Global pointer to the UI system singleton is stored at DAT_01223518+4.
    // Check if the system is initialized and the target is valid.
    if (*(int*)(DAT_01223518 + 4) != 0 && targetHandle != 0) {
        // Build a UI event structure: type=2 (likely a specific message, e.g., set value),
        // eventData as payload, and a zero padding/flags field.
        struct UIEvent {
            int type;   // +0x00
            int value;  // +0x04
            int unused; // +0x08
        } event = {2, eventData, 0};

        // Retrieve the UI system object instance.
        void* uiSystem = *(void**)(DAT_01223518 + 4);
        // Get the vtable pointer (first 4 bytes of the instance).
        void** vtable = *(void***)uiSystem;
        // Call the first virtual method (likely UISystem::handleEvent) with target and event.
        typedef void (*EventFunc)(void* self, int target, UIEvent* event);
        ((EventFunc)vtable[0])(uiSystem, targetHandle, &event);
    }
}