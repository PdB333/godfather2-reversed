// FUNC_NAME: Entity::getPhysicsComponent
int __fastcall Entity::getPhysicsComponent(void)
{
    // Returns pointer to physics component at offset 0x10 from this
    return (int)(this) + 0x10;
}