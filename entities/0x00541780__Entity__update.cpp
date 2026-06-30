// FUNC_NAME: Entity::update
void __thiscall Entity::update(Entity* this) {
    // Likely a debug assertion or function prolog (e.g., validate this pointer)
    FUN_009f2000();
    // +0xd0: pointer to a virtual function table (likely a secondary interface or component vtable)
    // Offset 0x50 into that table corresponds to virtual function slot 20 (update)
    (*(void (__thiscall**)(Entity*))(*(int*)((char*)this + 0xd0) + 0x50))();
}