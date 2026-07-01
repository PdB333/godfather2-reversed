// FUNC_NAME: BuildingManager::BuildingManager
void __thiscall BuildingManager::BuildingManager(BuildingManager* this) {
    // Set primary vtable at +0x0
    this->vtable = (void*)&PTR_FUN_00d78bc4;
    // Set secondary vtable at +0x3C
    *(void**)((uintptr_t)this + 0x3C) = (void*)&PTR_LAB_00d78bb4;
    // Set tertiary vtable at +0x48
    *(void**)((uintptr_t)this + 0x48) = (void*)&PTR_LAB_00d78bb0;
    // Initialize sub-object at offset +0x50 (likely CrimeScene or BuildingStore)
    FUN_004086d0((undefined4*)((uintptr_t)this + 0x50));
    FUN_00408310((undefined4*)((uintptr_t)this + 0x50));
    // Global engine initialization (e.g., singleton setup)
    FUN_0046c640();
}