// FUNC_NAME: EventManager::createEvent

int EventManager::createEvent(int param_1, int param_2, int param_3)
{
    char cVar1;
    int iVar2;
    int iVar3;

    // Increment event counter at offset 0x244
    *(int *)(this + 0x244) = *(int *)(this + 0x244) + 1;

    // Validate the event data (param_3)
    cVar1 = EventManager::isValidEventData(param_3);
    if (cVar1 != '\0')
    {
        // Check if the system is initialized
        cVar1 = EventManager::isSystemInitialized();
        if (cVar1 != '\0')
        {
            // Allocate an event handle based on param_2
            iVar2 = EventManager::allocateEventHandle(this, param_2);
            if (iVar2 != 0)
            {
                // Allocate a new EventNode (size 0x1C)
                iVar3 = EventManager::allocateEventNode(0x1c);
                if (iVar3 == 0)
                {
                    iVar3 = 0;
                }
                else
                {
                    // Set EventNode fields:
                    // +0x10 : handle (from allocateEventHandle)
                    *(int *)(iVar3 + 0x10) = iVar2;
                    // +0x08 : flag (byte, set to 0)
                    *(unsigned char *)(iVar3 + 8) = 0;
                    // +0x0C : unknown (int, 0)
                    *(int *)(iVar3 + 0xc) = 0;
                    // +0x14 : event data (param_3)
                    *(int *)(iVar3 + 0x14) = param_3;
                    // +0x18 : unknown (int, 0)
                    *(int *)(iVar3 + 0x18) = 0;
                }
                // Notify that an event was created
                EventManager::onEventCreated();
                // Register the event with the given object (param_1) and a field from this+4
                EventManager::registerEvent(param_1, *(int *)(this + 4));
                return iVar3;
            }
        }
    }
    return 0;
}