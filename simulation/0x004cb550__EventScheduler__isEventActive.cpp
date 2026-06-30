// FUNC_NAME: EventScheduler::isEventActive
int EventScheduler::isEventActive() {
    // +0x18: flag byte, cleared here
    *(char *)(this + 0x18) = 0;

    // +0x08: event ID (non-zero means assigned)
    if (*(int *)(this + 0x08) != 0) {
        // Global event manager pointer
        activateEventCheck();
        char result = checkEventByID(gEventManager, *(int *)(this + 0x08));
        if (result != '\0') {
            return 1;
        }
    }
    return 0;
}