// FUNC_NAME: UIInputManager::processInputEvent
// Address: 0x0071ef20
// This function processes an input event for the UI system.
// It checks flags, delegate state, and either plays a sound or calls a virtual handler.

int __thiscall UIInputManager::processInputEvent(UIInputManager* this, int eventId, bool isMouseEvent)
{
    bool bSkipReturn = false;
    char cVar2;
    int iVar3;
    int* pVtable;
    bool bAllowAction;

    // If the delegate pointer is null or points to a special sentinel (0x48), block the event
    if (this->delegate == 0 || this->delegate == (UIDelegate*)0x48) {
        return 1;
    }

    // Compute the derived object pointer (delegate - 0x48)
    if (this->delegate == 0) {
        iVar3 = 0;
    } else {
        iVar3 = (int)this->delegate - 0x48;
    }

    // Check bit 25 of flags at offset 0x1f58 from the derived object
    if ((*(uint*)(iVar3 + 0x1f58) >> 0x19) & 1) {
        return 1;  // Event blocked by a flag
    }

    bAllowAction = false;
    cVar2 = FUN_0045eef0();  // Is cursor visible? (returns 0 if hidden)
    if (cVar2 == '\0') {
        cVar2 = FUN_0045eec0(eventId);  // Is event focused?
        if ((cVar2 != '\0') && 
            (cVar2 = FUN_0045f120(), cVar2 == '\0'))  // Is menu closed?
        {
            bSkipReturn = isMouseEvent == '\0';
            goto LAB_0071efcf;
        }
    } else {
        if (this->delegate == 0) {
            cVar2 = FUN_0045eec0(eventId);
            bSkipReturn = cVar2 == '\0';
        } else {
            cVar2 = FUN_0045eec0(eventId);
            bSkipReturn = cVar2 == '\0';
        }
LAB_0071efcf:
        if (!bSkipReturn) goto LAB_0071efd3;
    }
    bAllowAction = true;

LAB_0071efd3:
    FUN_00460300(1.0f);  // Reset time scale to normal

    if (!bAllowAction) {
        return 1;  // Block action
    }

    if (isMouseEvent == '\0') {
        // Non-mouse event: call a sound/UI function (likely play sound)
        int result = FUN_0045f020(eventId, 0, 0, 0, 0);
        return result;
    } else {
        // Mouse event: call virtual function at vtable offset 83 (0x14c/4)
        if (this->delegate == 0) {
            pVtable = (int*)0x0;
        } else {
            pVtable = (int*)((int)this->delegate - 0x48);
        }
        // vtable+0x14c is a virtual method (e.g., handleMouseAction)
        int result = ((int (__thiscall*)(int, int, int))((int*)*pVtable)[0x53])(eventId, 1, 0);
        return result;
    }
}