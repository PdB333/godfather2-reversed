// FUNC_NAME: ControllerManager::initPads
void ControllerManager::initPads(int param1, int param2, int param3, int param4, int param5, int param6, int param7)
{
    // Call base initialization (FUN_004bfcf0)
    initBase();

    // Allocate and store a controller state object (FUN_0045a8f0)
    void* controllerState = allocateControllerState(param1, param2, param3, param4, param5, param6, param7);
    this->m_pControllerState = controllerState; // +0x90

    // Global constant likely representing an unmapped/unused controller slot
    int unmappedValue = s_unmappedControllerValue; // DAT_00e2b1a4

    // Initialize the 4 controller slots (each slot is 0x14 bytes, 5 fields)
    // Slot 0 at offset 0x40
    this->m_controllerSlots[0].field_00 = unmappedValue; // +0x40
    this->m_controllerSlots[0].field_04 = 0;            // +0x44
    this->m_controllerSlots[0].field_08 = 0;            // +0x48
    this->m_controllerSlots[0].field_0C = 0;            // +0x4c
    this->m_controllerSlots[0].field_10 = 0;            // +0x50

    // Slot 1 at offset 0x54
    this->m_controllerSlots[1].field_00 = unmappedValue; // +0x54
    this->m_controllerSlots[1].field_04 = 0;            // +0x58
    this->m_controllerSlots[1].field_08 = 0;            // +0x5c
    this->m_controllerSlots[1].field_0C = 0;            // +0x60
    this->m_controllerSlots[1].field_10 = 0;            // +0x64

    // Slot 2 at offset 0x68
    this->m_controllerSlots[2].field_00 = unmappedValue; // +0x68
    this->m_controllerSlots[2].field_04 = 0;            // +0x6c
    this->m_controllerSlots[2].field_08 = 0;            // +0x70
    this->m_controllerSlots[2].field_0C = 0;            // +0x74
    this->m_controllerSlots[2].field_10 = 0;            // +0x78

    // Slot 3 at offset 0x7c (only the first field is initialized here)
    this->m_controllerSlots[3].field_00 = unmappedValue; // +0x7c

    // Post‑initialization call (FUN_006101b0)
    postInit();
}