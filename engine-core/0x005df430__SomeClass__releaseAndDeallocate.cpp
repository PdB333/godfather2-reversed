// FUNC_NAME: SomeClass::releaseAndDeallocate
void __thiscall SomeClass::releaseAndDeallocate(void)
{
    // this->unk_0x10: pointer to first owned object
    if (*(int *)(this + 0x10) != 0) {
        // Call vtable[1] (Release?) on the object, passing 0 as parameter
        (**(code **)(**(int **)(this + 0x0c) + 4))(*(int *)(this + 0x10), 0);
        *(int *)(this + 0x10) = 0; // Clear pointer
    }
    // Call vtable[3] (Destructor?) on the first object's vtable pointer itself
    (**(code **)(**(int **)(this + 0x0c) + 0x0c))();

    // this->unk_0x08: pointer to second owned object
    if (*(int *)(this + 0x08) != 0) {
        // Call vtable[1] on the second object
        (**(code **)(**(int **)(this + 0x04) + 4))(*(int *)(this + 0x08), 0);
        *(int *)(this + 0x08) = 0;
    }
    // Call vtable[3] on the second object's vtable pointer
    (**(code **)(**(int **)(this + 0x04) + 0x0c))();

    return;
}