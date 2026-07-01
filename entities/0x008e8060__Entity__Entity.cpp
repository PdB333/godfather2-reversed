// FUNC_NAME: Entity::Entity
// Address: 0x008e8060
// Role: Constructor for Entity class (size = 0x160 bytes)
// Offsets: +0x00: vtable, +0x3C: unknown ptr, +0x48: unknown ptr, +0x50: sub-object A, +0x58: sub-object B

void* __thiscall Entity::Entity(void* this, byte flags) {
    *(void***)this = (void**)&PTR_FUN_00d8085c;
    *(void**)((uint8_t*)this + 0x3C) = (void*)&PTR_LAB_00d8084c;
    *(void**)((uint8_t*)this + 0x48) = (void*)&PTR_LAB_00d80848;
    FUN_004086d0((uint8_t*)this + 0x50);
    FUN_00408310((uint8_t*)this + 0x50);
    FUN_00408310((uint8_t*)this + 0x58);
    FUN_0046c640();
    if (flags & 1) {
        FUN_0043b960(this, 0x160);
    }
    return this;
}