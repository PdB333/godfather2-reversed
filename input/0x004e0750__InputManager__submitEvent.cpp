// FUNC_NAME: InputManager::submitEvent
void InputManager::submitEvent(int sourceId) {
    InputManager* singleton = GetInputManager();
    EventParams params;
    params.deviceType = 2;          // 2 = controller? or keyboard?
    params.maxSlots = 0x10;         // 16 controller slots
    params.flags = 0;               // no flags
    ((void (*)(int, EventParams*))singleton->vtable[0])(sourceId, &params);
}