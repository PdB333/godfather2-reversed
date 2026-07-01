// FUNC_NAME: Entity::scalarDeletingDestructor
// Address: 0x0091f120
// Role: Scalar deleting destructor for Entity or derived class.

struct Entity {
    void** vftable;                 // +0x00
    void* unknown_0x10;             // +0x10
    // ... other members ...
    void* someVtablePtr_0x4C;       // +0x4C
    Entity* childObject;            // +0x78
    void (Entity::*cleanupFunc)();  // +0x84
};

int g_someGlobalCounter; // 0x0112982c

void SomeGlobalCleanup(); // FUN_005c16e0
void operatorDelete(void* ptr); // FUN_005c4480

Entity* __thiscall Entity::scalarDeletingDestructor(Entity* this, byte flags) {
    this->vftable = (void**)&PTR_FUN_00d86000;
    this->unknown_0x10 = &PTR_LAB_00d85fdc;
    this->someVtablePtr_0x4C = &PTR_LAB_00d85fd8;

    if (this->childObject != 0) {
        (this->*cleanupFunc)();
    }

    this->someVtablePtr_0x4C = &PTR_LAB_00d85d84;
    g_someGlobalCounter = 0;
    SomeGlobalCleanup();

    if ((flags & 1) != 0) {
        operatorDelete(this);
    }

    return this;
}