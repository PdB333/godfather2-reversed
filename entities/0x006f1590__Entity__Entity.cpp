// FUNC_NAME: Entity::Entity
Entity* __thiscall Entity::Entity(bool isDynamic)
{
    // Call base class constructor (likely SimObject or Framework::Object)
    // FUN_006f1310 performs base initialization
    SimObject::SimObject();

    if (isDynamic)
    {
        // When the object is dynamically allocated (flag bit 0 set),
        // register it with the entity manager or perform additional setup.
        // FUN_009c8eb0(this) handles this registration.
        this->registerWithManager();
    }

    return this;
}