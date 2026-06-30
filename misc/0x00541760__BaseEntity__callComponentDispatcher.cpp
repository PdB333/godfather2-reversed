// FUNC_NAME: BaseEntity::callComponentDispatcher
void __thiscall BaseEntity::callComponentDispatcher(BaseEntity* this) {
    // Global hook or validation call before dispatching
    FUN_009f2000();  // Likely some engine-level pre-tick validation or logging

    // Indirect call through component pointer at offset 0xd0,
    // indexing a vtable slot at offset 0x4c (virtual function index 0x13)
    // The component is expected to be a polymorphic object (e.g., a behavior or controller)
    (*(void(__thiscall**)(BaseEntity*))(*(uint32_t*)((uint8_t*)this + 0xd0) + 0x4c))(
        *(BaseEntity**)((uint8_t*)this + 0xd0)
    );
}