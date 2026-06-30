// FUNC_NAME: PlayerSM::resetState

void __thiscall PlayerSM::resetState(int* context)
{
    // Call virtual function at vtable offset 0x254 (getStateId or similar)
    uint stateId = (*(uint (__thiscall**)(int*))(*context + 0x254))(context);
    this->currentStateId = stateId; // +0x2d0: stored current state ID

    // Check global condition (e.g., is in gameplay state)
    if (FUN_00481620() != 0) {
        // Release the object at +0x46c (e.g., animation handle, vehicle pointer)
        FUN_00701ff0(this->objectPointer); // +0x46c
    }
    this->objectPointer = 0; // +0x46c cleared
    this->someTimer = 0; // +0x384 (900 decimal): reset timer/counter
    FUN_00701f40(); // Clear internal state flags
}