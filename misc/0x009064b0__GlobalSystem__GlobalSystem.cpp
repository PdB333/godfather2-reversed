// FUNC_NAME: GlobalSystem::GlobalSystem
void __thiscall GlobalSystem::GlobalSystem(GlobalSystem *this) {
    // vtable setup
    this->vtable = &PTR_FUN_00d82604; // +0x00: vtable pointer
    // secondary interface pointer at offset 0x214 (param_1[0x85])
    this->field_0x214 = &PTR_LAB_00d825f4; // +0x214: possibly another vtable or interface

    // Release reference on static singletons if they exist
    // FUN_00402080 likely checks if pointer is valid or has references
    if (FUN_00402080(&DAT_01206794) != '\0') {
        FUN_004086d0(&DAT_01206794); // likely release/decrement ref count
    }

    if (FUN_00402080(&DAT_01206a28) != '\0') {
        FUN_004086d0(&DAT_01206a28); // release second singleton
    }

    // Common initialization sequence
    FUN_004083d0(); // probably initialize internal state
    FUN_004c2ef0(); // probably start subsystems
}