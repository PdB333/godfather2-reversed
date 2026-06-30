// FUNC_NAME: EARSObject::initWithChild
void EARSObject::initWithChild(void* child) {
    // Store this pointer (param_1) in EDI register for member access
    void* thisPtr = this;

    // Call virtual preInit (vtable offset 8)
    this->vtable->preInit();

    if (child != nullptr) {
        // Acquire reference to child and store at offset 4 (childRef)
        this->childRef = acquireReference(child, thisPtr);
        // Call virtual setChild (vtable offset 4) with child and flags=0
        this->vtable->setChild(child, 0);
        // Call virtual postInit (vtable offset 0xc)
        this->vtable->postInit();
    } else {
        // No child: clear reference at offset 4
        this->childRef = 0;
        // Call virtual postInit
        this->vtable->postInit();
    }
}