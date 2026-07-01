// FUNC_NAME: Entity::checkAndCallHandler
void __thiscall Entity::checkAndCallHandler() {
    // Check if the pointer at offset +0x204 is non-null
    if (*(int*)(reinterpret_cast<int>(this) + 0x204) != 0) {
        handleFlagAction(); // Calls FUN_004df600
    }
}