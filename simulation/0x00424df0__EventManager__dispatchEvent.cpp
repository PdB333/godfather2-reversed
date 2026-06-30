// FUNC_NAME: EventManager::dispatchEvent
void EventManager::dispatchEvent(void* target, void* arg1, void* arg2, void* arg3, void* arg4, char bRunSecondary) {
    // arg2 is unused in this implementation; possibly reserved for future use
    doPrimaryAction(target, arg1, arg3, arg4);
    if (bRunSecondary != '\0') {
        doSecondaryInit();
    }
}