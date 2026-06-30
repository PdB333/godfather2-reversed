// FUNC_NAME: EventAction::handleEvent
void __thiscall EventAction::handleEvent(uint param_2)
{
    // Temporary structure representing an event message (4+4+1 bytes)
    struct EventMessage {
        int *dataPtr;  // +0x00: pointer to global event data
        int flags;     // +0x04: flags (initialised to 0)
        char active;   // +0x08: active flag (initialised to 1)
    } msg;

    msg.dataPtr = DAT_0120e93c;  // global static event data
    msg.flags = 0;
    msg.active = 1;

    // Use value at this+0x3C as an event parameter, or 0 if this is null
    int eventParam = (this == 0) ? 0 : *(int *)((uint)this + 0x3C);

    // Dispatch the event message
    FUN_00408bf0(&msg, eventParam, param_2);

    // If both pointers at +0x34 and +0x38 are non‑null, chain to another action
    if (*(int *)((uint)this + 0x38) != 0 && *(int *)((uint)this + 0x34) != 0)
    {
        // Execute the linked action (pointed by +0x38)
        FUN_00482aa0(*(int *)((uint)this + 0x38), param_2);
    }
}