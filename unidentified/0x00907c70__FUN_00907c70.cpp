// FUNC_NAME: SomeClass::sendMessageToUI
void __thiscall sendMessageToUI(int this, undefined4 messageParam)
{
    // Calls a function to send a message to the UI system.
    // The first argument is a pointer stored at +0x4 in this object (likely a UI manager or message queue).
    // The second argument (0x2d) is likely a message ID or type constant.
    // The third argument is the message parameter (e.g., data or context).
    // The fourth argument (0) might be flags or a callback.
    FUN_005662a0(*(undefined4 *)(this + 4), 0x2d, messageParam, 0);
    return;
}