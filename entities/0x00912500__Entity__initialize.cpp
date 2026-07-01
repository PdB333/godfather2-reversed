// FUNC_NAME: Entity::initialize

void Entity::initialize()
{
    // Call a global helper function (likely engine-level initialization or update)
    // FUN_00957df0 - possibly GameEngine::preInitialize() or similar
    GameEngine::preInitialize();

    // Call the virtual function at vtable offset 0x78 (7th? 30th? depends on layout)
    // This likely triggers an event or starts the object with a default state
    // (*(void (__thiscall **)(int, int))(*this + 0x78))(this, 0);
    this->onCreate(0); // Assume 'onCreate' with a parameter 'state' (0 = default)
}