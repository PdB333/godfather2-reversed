// FUNC_NAME: SimObject::update
void __thiscall SimObject::update(SimObject *this) {
    // Release child object if it exists
    if (this->child != NULL) {
        // Call vtable method at offset 1 (releaseChild) with argument 0 (no deletion)
        (this->vtable->releaseChild)(this->child, 0);
        this->child = NULL;
    }
    // Call vtable method at offset 3 (doUpdate) – the main update logic
    (this->vtable->doUpdate)();
}