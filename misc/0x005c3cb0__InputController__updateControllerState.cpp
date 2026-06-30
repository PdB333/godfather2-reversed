// FUNC_NAME: InputController::updateControllerState
void __thiscall InputController::updateControllerState(InputController* this, uint param2)
{
    // Retrieve the controller manager singleton via static function.
    // The argument in_EAX is likely a thread ID or constant (placeheld as 0).
    int* pMgr = (int*)FUN_005c3df0(0);
    if (pMgr != nullptr) {
        // Call the third virtual method (offset 8) on the manager.
        // Passes (this + 5) as the first argument (byte offset 5 or offset 0x14 if int*).
        // The second argument is param2.
        (**(void (__thiscall**)(int, uint))(*pMgr + 8))((int)this + 5, param2);
    }
}