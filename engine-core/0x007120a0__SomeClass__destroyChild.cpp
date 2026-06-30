// FUNC_NAME: SomeClass::destroyChild
void __thiscall SomeClass::destroyChild() {
    // +0x5c: pointer to child object (owned)
    if (this->m_child != nullptr) {
        releaseChildObject(this->m_child);  // FUN_0071bc70 – likely destructor/release
        this->m_child = nullptr;
    }
}