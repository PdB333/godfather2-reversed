// FUNC_NAME: SimEntity::handleGameEvent
void __thiscall SimEntity::handleGameEvent(int *event)
{
    // event structure: +4 = sender pointer, +0x38 = sender type ID, +8 = resource pointer, +0xc = data1, +0x10 = data2
    if ((*(int *)(event + 1) != 0) && (*(int *)(*(int *)(event + 1) + 0x38) == this->typeIdAt0x1EE8)) {
        // Acquire global mutex (DAT_0112a5e0)
        acquireGlobalMutex(&DAT_0112a5e0);
        // Release resource if present
        if (*(int *)(event + 2) != 0) {
            releaseResource(*(int *)(event + 2), 0);
        }
        // Notify listeners via vtable offset 0x288 (type 4, data from event)
        (*(void (__thiscall **)(int, int, int))(*(int *)this + 0x288 / 4))(4, *(int *)(event + 3), *(int *)(event + 4));
        // Global update tick
        processGlobalTick();
        // Set notification flag (0x800) at this + 0x24A4
        this->notificationFlagsAt0x24A4 |= 0x800;
        // Conditional state transition based on bits
        if ((((uint)this->stateFlagsAt0x249C >> 5 & 1) != 0) && (((uint)this->stateFlagsAt0x24A0 >> 8 & 1) == 0)) {
            this->stateFlagsAt0x24A0 |= 4;
        }
    }
}