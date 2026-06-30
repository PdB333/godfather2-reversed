// FUNC_NAME: UIMenuHandler::handleInput

void __thiscall UIMenuHandler::handleInput(UIHandler* this, int actionId)
{
    // Preliminary update (e.g., clear previous state)
    FUN_006bec10();

    // Check first input handler at offset +0x1c (likely a sub-handler for one action type)
    if (FUN_006beb80(reinterpret_cast<char*>(this) + 0x1c, actionId) != 0) {
        // Delegate to first handler callback, passing the component pointer at +0x10
        FUN_008c29f0(*(int*)(reinterpret_cast<char*>(this) + 0x10), actionId);
        return;
    }

    // Check second input handler at offset +0x28 (alternate action)
    if (FUN_006beb80(reinterpret_cast<char*>(this) + 0x28, actionId) != 0) {
        // Delegate to second handler callback
        FUN_008c2ab0(*(int*)(reinterpret_cast<char*>(this) + 0x10), actionId);
    }
}