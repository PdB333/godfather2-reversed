// FUNC_NAME: BuildingManager::BuildingManager
void __fastcall BuildingManager::BuildingManager(BuildingManager* this) // 0x0077ea20
{
    // Set primary vtable pointer (BuildingManager class vtable)
    this->vtable = &PTR_FUN_00d6920c; // +0x00

    // Set secondary vtable pointers for multiple interface support (e.g., IDrawable, IUpdatable)
    this->field_3C = &PTR_LAB_00d691fc; // +0x3C
    this->field_48 = &PTR_LAB_00d691f8; // +0x48

    // Initialize global EntityDataManager singleton (likely a static or engine-wide manager)
    EntityDataManager::Initialize(&DAT_0120e93c); // FUN_004086d0

    // Call base class constructor (e.g., SimManager or EntityManager)
    BaseClass::BaseClass(this); // FUN_0077b6b0

    // If a pointer at offset 0x5C already exists, release it (prevents memory leak on re-init)
    if (this->field_5C != nullptr) // +0x5C
    {
        Object::Release(this->field_5C); // FUN_009c8eb0
        this->field_5C = nullptr;
    }

    // Finalize construction (e.g., register with the engine's main loop)
    GlobalEnginePostConstruction(); // FUN_0046c640
}