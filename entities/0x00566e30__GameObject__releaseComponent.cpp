// FUNC_NAME: GameObject::releaseComponent
void __thiscall GameObject::releaseComponent(void) {
    // Check if the component pointer at offset 0x11c is non-null
    if (this->componentPtr != nullptr) {
        // Release/destroy the component object
        releaseObject(this->componentPtr);
        // Clear the pointer to avoid dangling reference
        this->componentPtr = nullptr;
    }
}