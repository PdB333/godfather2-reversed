// FUNC_NAME: GodfatherGameManager::update
// Address: 0x00799eb0
// Calls virtual at vtable+0x308, checks flag at +0x4A8, then update call

void __thiscall GodfatherGameManager::update(GodfatherGameManager* this) {
    // Virtual call at offset 0x308 (likely base class tick/update)
    (**(code**)(*(int*)this + 0x308))();

    // Check if the active flag at offset 0x4A8 (field index 0x12a * 4) is zero
    if (*(int*)((char*)this + 0x4A8) == 0) {
        // Log debug with level 3 (e.g., enable verbose logging)
        sub_5512C0(3);
    }

    // Call additional update/subsystem processing
    sub_896E60();
}