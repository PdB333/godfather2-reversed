// FUNC_NAME: UIHandler::processAction
// Address: 0x0075e390
// Processes UI action messages with IDs 10-13, delegates others to default handler.
// The class has a bitfield at +0xA8 and an object pointer at +0xB0.

unsigned char __thiscall UIHandler::processAction(int actionId, int arg1, int arg2, int arg3, int arg4)
{
    unsigned char result = 1; // default return value (success?)

    // Base action ID is 10; subtract to get case index
    switch (actionId - 10) {
    case 0: // actionId == 10
        this->toggleSomething(); // calls FUN_0075e330
        return 1;

    case 1: // actionId == 11
        // Check if the action can be performed (some condition) AND flag bit 6 is NOT set
        if (checkCondition() && ((this->flags >> 6) & 1) == 0) {
            startAction();    // FUN_007f62e0
            startAction2();   // FUN_007f62f0
            this->flags |= 0x80; // set bit 7 (active flag)
            return 1;
        }
        break;

    case 2: // actionId == 12
        // If the action is currently active (bit 7 set), disable it
        if ((this->flags >> 7) & 1) {
            stopAction();     // FUN_007fbe50
            stopAction2();    // FUN_007fbe90
            this->flags &= ~0x80; // clear bit 7
            return 1;
        }
        break;

    case 3: // actionId == 13
        // If there is a target object, call its action method
        if (this->targetObject != 0) {
            callObjectAction(this->targetObject); // FUN_0075d380
            return 1;
        }
        break;

    default: // all other action IDs
        result = defaultActionHandler(arg1, arg2, arg3, actionId, arg4); // FUN_004ac700
        break;
    }

    return result;
}