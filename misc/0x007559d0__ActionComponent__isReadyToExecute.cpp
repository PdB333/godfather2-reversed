// FUNC_NAME: ActionComponent::isReadyToExecute
bool __thiscall ActionComponent::isReadyToExecute(ActionComponent* thisPtr) {
    uint8 flags = *(uint8*)(thisPtr + 0x58);  // +0x58 flags (bit 3 = paused, bit 4 = completed)
    if ((flags & 0x08) == 0) {
        float elapsed = getTimerElapsedTime((TimerData*)(thisPtr + 0x6c));  // +0x6c timer struct, function returns float
        if (elapsed <= *(float*)(thisPtr + 0x60)) {  // +0x60 cooldown duration
            return false;
        }
    } else if ((flags & 0x10) == 0) {
        return false;
    }
    return true;
}