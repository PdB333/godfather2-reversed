// FUNC_NAME: GodfatherGameManager::constructor
GodfatherGameManager* __thiscall GodfatherGameManager::constructor(GodfatherGameManager* this, void* systemSettings) {
    // Call base class constructor (EARSObject or similar)
    EARSObject::constructor(); // FUN_0049c610

    // Initialize virtual function tables (dual-inheritance: primary at +0, secondary at +8)
    this->vtablePrimary   = (void*)&vtable_GodfatherGameManager_primary;   // *param_1 = &PTR_FUN_00d606c8
    g_pGameManager        = this;                                          // DAT_01129970
    this->vtableSecondary = (void*)&vtable_GodfatherGameManager_secondary; // param_1[2] = &PTR_LAB_00d606c4

    // Store system settings pointer at offset +0x10
    this->settings = systemSettings; // param_1[4] = param_2

    // Invoke a method on systemSettings via its vtable slot at offset +8 (index 2)
    (*(void (__thiscall**)(void*))((int**)systemSettings)[2])(systemSettings); // (**(code**)(*param_2+8))()

    // Allocate sub-component memory (20 bytes)
    void* subMem = operatorNew(0x14); // FUN_009c8e50
    if (subMem != nullptr) {
        int initData[3] = {0, 0, 0};  // uStack_c, uStack_8, uStack_4
        // Construct sub-component; returns a handle or pointer stored at offset +0x0C
        this->subComponent = SubComponent::create(10, systemSettings, initData); // FUN_006f4280
    } else {
        this->subComponent = nullptr;
    }

    // Register this instance with the engine
    engineRegisterInstance(&gClassData, 1); // FUN_0049c6e0

    return this;
}