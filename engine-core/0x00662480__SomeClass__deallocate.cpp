// FUNC_NAME: SomeClass::deallocate

void __thiscall SomeClass::deallocate(void)
{
    // Check for valid instance pointer (this from ESI)
    if (this != nullptr) {
        // Release internal resources (likely frees child allocations)
        this->releaseResources(); // Calls FUN_00665b80
        // Free the object's memory block (allocated via malloc/family)
        free(this);
    }
}