// FUN_004cebd0: EARSObject::~EARSObject
void __thiscall EARSObject::destroy(void)
{
    // Base class cleanup
    EARSObject::preDestroy(); // FUN_004cecd0 (hypothetical name for base destructor)

    // Release child object at offset +0x18 using virtual destructor with size hint 0xc
    (this->vtable->release)(this->child1, 0xc);
    this->child1 = nullptr;

    // Release child object at offset +0x14 using allocator's free method
    if (this->child2 != nullptr) {
        (this->allocator->vtable->free2)(this->child2, 0);
        this->child2 = nullptr;
    }

    // Finalize allocator (e.g., deinitialize or garbage collect)
    this->allocator->vtable->finalize();

    // Final cleanup
    EARSObject::postDestroy(); // FUN_004cee30
}