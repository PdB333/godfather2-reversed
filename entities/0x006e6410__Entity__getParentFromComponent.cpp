// FUNC_NAME: Entity::getParentFromComponent
// Function at 0x006e6410: Returns a pointer to the parent object that contains the component pointed to by this->componentPtr.
// The component is embedded at offset +0x48 within the parent, and this->componentPtr (at offset +0x330) points to that component.
// If componentPtr is null, returns null.

class Entity {
public:
    // +0x330: Pointer to a component object embedded at parent+0x48
    void* componentPtr; // likely a pointer to some embedded sub-object

    // Returns the parent Entity* if componentPtr is valid, otherwise nullptr.
    // The parent is found by subtracting 0x48 from the component pointer,
    // because the component is placed at offset 0x48 within the parent.
    void* getParentFromComponent() {
        if (this->componentPtr != nullptr) {
            // Subtract the offset of the component within the parent to get the parent address.
            return reinterpret_cast<void*>(
                reinterpret_cast<uintptr_t>(this->componentPtr) - 0x48
            );
        }
        return nullptr;
    }
};