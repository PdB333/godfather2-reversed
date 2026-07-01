// FUNC_NAME: InputDeviceManager::checkControllerStatus
void __fastcall InputDeviceManager::checkControllerStatus(InputDeviceManager *this)
{
    char cVar1;
    
    // Check if both controller fields at +0x6FC and +0x6FE are non-zero (e.g., device ID and user index)
    if ((this->field_0x6FC != 0) && (this->field_0x6FE != 0)) {
        // Call helper to check controller status (likely XInputGetState or similar)
        cVar1 = FUN_006a8b50(&this->field_0x6FC);
        // Call virtual method at vtable+0x5c (e.g., SetControllerRumble or SetControllerLight)
        // Pass 0x1000000 if connected/active, else 0
        (this->vtable->method_at_0x5c)(-(uint)(cVar1 != '\0') & 0x1000000, 0x1000000);
        return;
    }
    // No controller: clear the effect
    (this->vtable->method_at_0x5c)(0, 0x1000000);
    return;
}