// FUNC_NAME: BaseVehicle::checkDriverAction
void __fastcall BaseVehicle::checkDriverAction(void) {
    // Check if driver pointer (offset 0x2c88) is not null
    if (this->m_pDriver != 0) {
        // Process driver-specific action
        handleDriverAction(); // calls FUN_00784750
    }
}