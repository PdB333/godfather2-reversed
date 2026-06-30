// FUNC_NAME: SomeClass::hasRoom
bool __thiscall SomeClass::hasRoom(void) {
    bool result = true; // default return true if pointer is null
    if (this->field_0x10c != nullptr) {
        uint count = this->field_0x10c->vtable->getCount(); // vtable+8→virtual getCount()
        result = (count <= this->field_0x14c); // compare with capacity
    }
    return result;
}