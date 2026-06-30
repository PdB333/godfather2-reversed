// FUNC_NAME: Entity::setDataPtr
void __thiscall Entity::setDataPtr(void* ptr) {
    *(void**)(this + 0xb4) = ptr; // +0xB4: pointer to some associated data
}