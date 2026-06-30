// FUNC_NAME: Entity::Entity
undefined4 __thiscall Entity::Entity(Entity *this, byte flags)
{
    EARSObject::EARSObject(this);
    if (flags & 1) {
        this->initInternalBuffer(100);
    }
    return this;
}