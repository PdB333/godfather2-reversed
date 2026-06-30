// FUNC_NAME: Entity::setEnabled
void __thiscall Entity::setEnabled(Entity* this, char enabled)
{
    // vtable offset 0x234: presumably a virtual method that sets an active/visible state with an integer level and an immediate flag
    // The first argument is the state: 0 = disabled, 4 = fully enabled
    // The second argument is a constant 1, likely indicating "apply immediately"
    if (enabled != '\0') {
        (**(void (__thiscall**)(Entity*, int, int))(*(int*)this + 0x234))(this, 4, 1);
        return;
    }
    (**(void (__thiscall**)(Entity*, int, int))(*(int*)this + 0x234))(this, 0, 1);
    return;
}