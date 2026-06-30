// FUNC_NAME: Container::Destructor

void __thiscall Container::Destructor(void)
{
    // +0x00: vtable pointer
    // +0x04: child1 (pointer to some object)
    // +0x08: manager (pointer to an object with release/releaseAll methods)
    // +0x0C: child2 (pointer to some object)

    if (this->child2 != 0) {
        // Release child2 via manager's vtable offset 4 (first argument child2, second 0)
        (this->manager->vtable->release(this->child2, 0));
        this->child2 = 0;
    }

    // Call manager's offset 12 cleanup (no arguments)
    (this->manager->vtable->cleanup)();

    if (this->child1 != 0) {
        // Release child1 via own vtable offset 4 (called with child1 as this and 0 as arg)
        (this->vtable->release(this->child1, 0));
        this->child1 = 0;
    }

    // Call own vtable offset 12 destructor (no arguments)
    (this->vtable->destructor)();
}