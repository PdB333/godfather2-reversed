// FUNC_NAME: EventScheduler::postEventWithData
// Address: 0x0065c0c0
// Role: This is a thin wrapper that packs two 32-bit parameters into an 8-byte buffer and passes them with a command/type code (0x40) to the underlying event posting function at 0x0064b810.
// The first parameter (param_1) corresponds to the implicit 'this' pointer for the EventScheduler instance, but is unused in this function body.

void EventScheduler::postEventWithData(int param2, int param3) {
    int packedData[2]; // +0x00: first value, +0x04: second value
    packedData[0] = param2;
    packedData[1] = param3;
    // FUN_0064b810 is likely the internal event dispatcher (e.g., EventScheduler::dispatchEvent or a global message system)
    // It receives an event type (0x40) and a pointer to the packed data.
    FUN_0064b810(0x40, packedData);
}