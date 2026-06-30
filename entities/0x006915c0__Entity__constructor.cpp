// FUNC_NAME: Entity::constructor
// Address: 0x006915c0
// Role: Base entity initialization called by all derived constructors.
// Calls two sub-initializers: initBaseProperties and initComponents.
// The parameter is the 'this' pointer for the entity object.
void Entity::constructor(Entity* this)
{
    Entity::initBaseProperties(this);   // 0x006914a0 - set up base flags, pointers, etc.
    Entity::initComponents(this);       // 0x00691530 - allocate/initialize subsystems (physics, animation, etc.)
    return;
}