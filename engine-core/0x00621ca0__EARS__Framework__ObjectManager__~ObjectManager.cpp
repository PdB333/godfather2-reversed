// FUNC_NAME: EARS::Framework::ObjectManager::~ObjectManager
void EARS::Framework::ObjectManager::~ObjectManager(void)
{
    int this;
    byte local_10[12];

    // +0x1c initially points to a pointer-to-pointer structure (e.g., a linked list head)
    // call helper to clean up that structure (likely releases child objects)
    FUN_00623210(local_10, this, **(undefined4 **)(this + 0x1c), this, *(undefined4 **)(this + 0x1c));

    // virtual call on sub-object at +4 (vtable at offset 4) – release with size 0x18
    (**(code **)(**(int **)(this + 4) + 4))(*(undefined4 *)(this + 0x1c), 0x18);
    // clear the pointer structure
    *(undefined4 *)(this + 0x1c) = 0;
    *(undefined4 *)(this + 0x20) = 0;

    // if sub-object at +0x18 exists, release it via vtable at +0x14 (offset 4)
    if (*(int *)(this + 0x18) != 0) {
        (**(code **)(**(int **)(this + 0x14) + 4))(*(int *)(this + 0x18), 0);
        *(undefined4 *)(this + 0x18) = 0;
    }

    // call shutdown on sub-object at +0x14 (vtable offset 0xc)
    (**(code **)(**(int **)(this + 0x14) + 0xc))();

    // global cleanup
    FUN_00621f80();
    return;
}