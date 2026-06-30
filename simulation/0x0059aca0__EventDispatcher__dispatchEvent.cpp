// FUNC_NAME: EventDispatcher::dispatchEvent
void __fastcall EventDispatcher::dispatchEvent(int this)
{
    // Check if handler object exists
    if (*(int *)(this + 0x1c0) != 0) {
        // Validate message type (expected 0xC)
        if (*(short *)(*(int *)(this + 8) + 2) != 0xc) {
            // Debug break or assertion failure via global vtable
            (**(code **)(*DAT_01205590 + 4))();
        }
        // Check if message has a target object
        if (*(int *)(*(int *)(this + 8) + 4) != 0) {
            // Call handler's virtual function at index 3 (0xC/4) with no extra args
            (**(code **)(**(int **)(this + 0x1c0) + 0xc))();
            return;
        }
        // Otherwise call handler's virtual function at index 4 (0x10/4) with message parameter
        (**(code **)(**(int **)(this + 0x1c0) + 0x10))(*(undefined4 *)(*(int *)(this + 8) + 8));
    }
}