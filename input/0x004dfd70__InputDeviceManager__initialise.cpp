// FUNC_NAME: InputDeviceManager::initialise
void InputDeviceManager::initialise(void)
{
    // Global: last active controller index (set to -1 meaning none active)
    g_lastActiveControllerIndex = -1; // 0x010c2328

    // Initialise controller slot array (16 slots, 0x10 bytes each)
    // Slot structure at +0x011947f8, each slot has fields at +0x4 and +0x6
    short index = 0;
    short* pSlotField = (short*)((int)&g_controllerSlots + 6); // start at first slot's +0x6
    do {
        *pSlotField = index;                 // +0x6: slot index
        *(pSlotField - 1) = 0;               // +0x4: clear flag
        pSlotField += 8;                     // advance 0x10 bytes (8 shorts)
        index++;
    } while ((int)pSlotField < (int)&g_controllerSlotsEnd); // end address 0x1194a7e

    // Allocate InputDeviceManager instance (0x48 bytes)
    void* mem = operator new(0x48); // FUN_009c8e50
    if (mem != nullptr) {
        g_pInputDeviceManager = (InputDeviceManager*)InputDeviceManager::constructor(mem); // FUN_004ded00
    } else {
        g_pInputDeviceManager = nullptr;
    }

    // Initialise input subsystems
    InputDeviceManager::initXInput();       // FUN_004e3ef0
    InputDeviceManager::initKeyboardMouse();// FUN_004e9190
    InputDeviceManager::initForceFeedback();// FUN_004dfdd0
}