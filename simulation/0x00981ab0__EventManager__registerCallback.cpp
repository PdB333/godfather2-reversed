// FUNC_NAME: EventManager::registerCallback

void EventManager::registerCallback() {
    // Registers a callback with type 3, using object-specific data at offset 0x54,
    // and the callback table located at LAB_00981670.
    // The constant 3 likely identifies the event or message type.
    // FUN_0093f6c0 is presumably a static event registration function.
    FUN_0093f6c0(3, *(undefined4 *)(this + 0x54), &LAB_00981670);
}