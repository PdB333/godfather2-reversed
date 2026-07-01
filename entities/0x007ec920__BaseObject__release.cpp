// FUNC_NAME: BaseObject::release
void __fastcall BaseObject::release(BaseObject* this)
{
    // Release child object if present
    if (this->m_child != nullptr) {
        // Call virtual release method on child (vtable+4) with argument 0
        (this->m_child->vtable->release)(this->m_child, 0);
        this->m_child = nullptr;
    }
    // Call virtual destructor (vtable+12)
    (this->vtable->destructor)();
}