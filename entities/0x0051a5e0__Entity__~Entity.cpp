// FUNC_NAME: Entity::~Entity
void Entity::~Entity()
{
    // Call base class destructor (likely Framework::Object::~Object)
    Framework::Object::~Object(); // FUN_0051d6b0

    // Destroy all components stored in the component array
    short componentCount = *(short*)(this + 0x80); // +0x80: mComponentCount
    if (componentCount > 0) {
        // Array of ComponentEntry structures, each 20 bytes (5 int32)
        // First field is a pointer to a component interface
        int* componentArray = (int*)(this + 0xf4); // +0xf4: mComponents
        for (int i = 0; i < componentCount; i++) {
            if (componentArray[0] != 0) {
                // Release the component via its interface
                // FUN_005343f0 is likely IComponent::release()
                ((IComponent*)componentArray[0])->release();
            }
            componentArray += 5; // Move to next component entry (5*4 = 20 bytes)
        }
    }

    // Handle shared pointer to script data / behavior
    // +0x20: mScriptData (shared pointer to a reference-counted object)
    int* scriptData = *(int**)(this + 0x20);
    if (scriptData == 0) {
        *(int*)(this + 0x20) = 0;
        return;
    }
    // Decrement reference count (located at offset +4 in the control block)
    int* refCount = scriptData + 1;
    (*refCount)--;
    if (*refCount == 0) {
        // If ref count reaches zero, call destructor via vtable
        void (**vtable)() = (void (**)())(*(int*)scriptData);
        (*vtable)(); // virtual destructor
    }
    *(int*)(this + 0x20) = 0;
}