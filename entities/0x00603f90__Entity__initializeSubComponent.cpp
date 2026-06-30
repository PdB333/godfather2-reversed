// FUNC_NAME: Entity::initializeSubComponent
void __thiscall Entity::initializeSubComponent(Entity *this, int param_2, int param_3, int param_4)
{
    // Call a general initialization function with the three parameters
    // (likely setup for a sub-component or configuration data)
    initializeComponent(param_2, param_3, param_4);  // FUN_00603d30

    // Initialize a sub-object located at offset 0x74 from this
    // (could be a pointer to a controller, state machine, or another entity)
    ((SomeSubComponent*)(this + 0x74))->postInit();   // FUN_004d4300
}