// FUNC_NAME: Entity::Entity
undefined4 __thiscall Entity::Entity(undefined4 this, byte creationFlags)
{
    // Common base initialization (likely parent class or static setup)
    FUN_005c16e0();
    // If the first bit is set, perform additional construction steps
    if ((creationFlags & 1) != 0) {
        FUN_005c4480(this);
    }
    return this;
}