// FUNC_NAME: InputActionHandler::handleInputEvent
void __thiscall InputActionHandler::handleInputEvent(InputActionHandler *this)
{
    int lookupResult;
    int bindingId;
    char isSpecialAction;
    char *bindingString;
    uint index;
    struct {
        undefined1 *p0;
        undefined4 d1;
        undefined4 d2;
        code *funcPtr;
    } localStruct;
    code *actionCallback;
    
    if (((*(byte *)&this->flags & 1) != 0) && (this->state < 2) &&
        (lookupResult = FUN_004973e0(this->actionId), lookupResult != 0)) {
        // lookupResult points to an object with fields at +0x8 and +0xc
        int objField8 = *(int *)(lookupResult + 8);
        int objFieldC = *(int *)(lookupResult + 0xc);
        index = 0;
        while (true) {
            if (((this->currentIndex != -1) && (this->currentIndex <= (int)index)) || (1 < index)) {
                goto default_binding;
            }
            bindingId = FUN_00496610(objField8, objFieldC, index);
            if (bindingId != 0xff) break;
            index = index + 1;
        }
        this->currentIndex = index;
        switch(bindingId) {
        case 0:
            bindingString = "[b=MouseButton1]";
            break;
        case 1:
            bindingString = "[b=MouseButton2]";
            break;
        case 2:
            bindingString = "[b=MouseButton3]";
            break;
        case 3:
        case 4:
            localStruct.p0 = (undefined1 *)0x0;
            localStruct.d1 = 0;
            localStruct.d2 = 0;
            localStruct.funcPtr = (code *)0x0;
            isSpecialAction = FUN_0069c550(bindingId, &localStruct);
            if (isSpecialAction == '\0') {
                if (this->state == 0) {
                    FUN_0068b910(0x33371f37);
                }
            }
            else {
                actionCallback = localStruct.p0;
                if (actionCallback == (undefined1 *)0x0) {
                    actionCallback = &DAT_0120546e;
                }
                FUN_0068e9c0(actionCallback);
                if (((*(byte *)&this->flags & 1) != 0) && (this->state < 2)) {
                    this->state = 1;
                }
            }
            if (localStruct.p0 == (undefined1 *)0x0) {
                return;
            }
            (*localStruct.funcPtr)(localStruct.p0);
            return;
        case 5:
            bindingString = "[b=AnimMouseUp]";
            break;
        case 6:
            bindingString = "[b=AnimMouseDown]";
            break;
        case 7:
            bindingString = "[b=AnimMouseRight]";
            break;
        case 8:
            bindingString = "[b=AnimMouseLeft]";
            break;
        default:
default_binding:
            if (this->state != 0) {
                return;
            }
            bindingString = (char *)FUN_0068b910(0x33371f37);
            if (bindingString == (char *)0x0) {
                return;
            }
        }
        FUN_004d3d90(bindingString);
        this->playedBinding = 1; // +0x10
        if (((*(byte *)&this->flags & 1) != 0) && (this->state < 2)) {
            this->state = 1;
        }
    }
    return;
}