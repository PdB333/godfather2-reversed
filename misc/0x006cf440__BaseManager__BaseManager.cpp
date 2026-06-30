// FUNC_NAME: BaseManager::BaseManager
void __fastcall BaseManager::BaseManager(BaseManager* this)
{
    // Set virtual function table pointer at offset 0
    *reinterpret_cast<void**>(this) = &PTR_FUN_00d5f1f0; // vtable for this class

    // Set pointer at offset +0x08 (param_1[2]) – likely base class vtable or static data
    reinterpret_cast<void**>(this)[2] = &PTR_LAB_00d5f1e8; // e.g., base vtable or shared data

    // Check if a system condition is active (e.g., debug or test mode)
    bool isDebugMode = FUN_0089c630(); // Likely GameSystem::isDebugMode()

    if (isDebugMode)
    {
        FUN_006915c0(7); // Log or trigger assert with code 7 – e.g., Debug::log(7)
    }

    // Perform base class initialization
    FUN_00473a60(); // BaseClass::initialize()
}