// FUNC_NAME: Entity::constructorWithDestructFlag
// Function address: 0x005422f0
// Role: Constructor that optionally calls a cleanup function if flag & 1 is set
int __thiscall Entity::constructorWithDestructFlag(Entity* this, byte flag)
{
    // Base initialization (FUN_00542330)
    Entity::init(this);
    // If flag bit 0 is set, perform destruction (FUN_009c8eb0)
    if (flag & 1) {
        Entity::destroy(this);
    }
    return (int)this;
}