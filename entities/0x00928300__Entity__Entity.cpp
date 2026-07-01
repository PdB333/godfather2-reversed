// FUNC_NAME: Entity::Entity
undefined4 __thiscall Entity::Entity(byte flags)
{
    // Call base class constructor (e.g., Framework::Object)
    FUN_00927b50();
    if ((flags & 1) != 0) {
        // Optional secondary initialization (e.g., allocate memory or set derived flag)
        FUN_009c8eb0(this);
    }
    return this;
}