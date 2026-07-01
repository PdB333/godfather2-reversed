// FUNC_NAME: ControllerSlot::resetState
void __fastcall ControllerSlot::resetState(ControllerSlot* this)
{
    // Call to base class or member initialization routine (e.g., clears data or sets defaults)
    FUN_00873bb0(0);
    // Set the "active" or "connected" flag at offset +0x5 to false
    this->active = 0;
    return;
}