// FUNC_NAME: TriggerManager::handleTriggerEvent
// Address: 0x004e6e00
// Role: Handles trigger activation for an object; checks flag at +0xb2 and calls action processor if set.
// Offset documentation:
//   param_2+0xb2: uint8 flags (bit 1 = trigger enabled/ready)
//   param_2+0xa0: pointer to action resource (e.g., script or sound)
//   param_2+0x10: event data buffer (e.g., parameters for the action)
// Called function: FUN_00433700 (likely ProcessAction or similar)

void __thiscall TriggerManager::handleTriggerEvent(TriggerObject* triggerObj)
{
    // Check if the trigger's flag bit 1 is set (0x02)
    if ((triggerObj->flags & 0x02) != 0)
    {
        // Invoke the action processor with the trigger's resource, event data, and this manager
        // Arguments: resource pointer, data buffer, 0, -1, 6 (action type?), 0, and this pointer
        ProcessAction(triggerObj->actionResource, triggerObj->eventData, 0, 0xFFFFFFFF, 6, 0, this);
    }
}