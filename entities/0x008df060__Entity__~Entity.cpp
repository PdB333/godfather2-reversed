// FUNC_NAME: Entity::~Entity
// Function at 0x008df060 - Destructor for Entity class (EARS::Framework::Entity)
// Sets multiple vtable pointers for multiple inheritance interfaces, releases sub-objects,
// updates global reference tracking, and calls a cleanup callback.

void __thiscall Entity::~Entity(Entity* this)
{
    // Set vtable pointers for the class and its base classes/interfaces.
    // +0x00: primary vtable
    this->vtable0 = (void*)&PTR_FUN_00d7f730;
    // +0x3C: secondary vtable (likely for an interface)
    this->vtable1 = (void*)&PTR_LAB_00d7f720;
    // +0x48: tertiary vtable
    this->vtable2 = (void*)&PTR_LAB_00d7f71c;
    // +0x50: fourth vtable
    this->vtable3 = (void*)&PTR_LAB_00d7f718;
    // +0x54: fifth vtable
    this->vtable4 = (void*)&PTR_LAB_00d7f6b8;
    // +0x58: sixth vtable
    this->vtable5 = (void*)&PTR_LAB_00d7f650;

    // Update global reference tracking for this object type.
    // DAT_0112fc98 is a global counter or mutex.
    globalRefInc(&g_refCountTracker);
    globalRefDec(&g_refCountTracker);

    // Release two optional sub-objects.
    // +0x2A4: pointer to some allocated sub-object
    if (this->subObject1 != nullptr) {
        deallocate(this->subObject1);
    }
    // +0x298: pointer to another allocated sub-object
    if (this->subObject2 != nullptr) {
        deallocate(this->subObject2);
    }

    // Invoke global cleanup callback (e.g., deregister from manager).
    globalCleanupCallback();
}