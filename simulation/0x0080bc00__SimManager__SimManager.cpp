// FUNC_NAME: SimManager::SimManager
void __thiscall SimManager::SimManager(SimManager *this)
{
    // Set the vtable pointer at offset +0x00
    this->vtable = &SIM_MANAGER_VTABLE; // PTR_FUN_00d7251c

    // Initialize function pointer tables at offsets +0x3C and +0x48
    this->pFuncTable1 = &FUNC_TABLE_1; // PTR_LAB_00d7250c at +0x3C
    this->pFuncTable2 = &FUNC_TABLE_2; // PTR_LAB_00d72508 at +0x48

    // Construct embedded subsystem at +0x50 (e.g., a state machine or simulation core)
    SimCore *core = reinterpret_cast<SimCore *>(&this->field_0x50);
    SimCore::SimCore(core);        // FUN_004086d0
    SimCore::init(core);           // FUN_00408310

    // Perform global initialization (e.g., register classes, load defaults)
    GlobalInit();                  // FUN_0046c640
}