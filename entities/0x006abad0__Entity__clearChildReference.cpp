// FUNC_NAME: Entity::clearChildReference
void __thiscall Entity::clearChildReference(Entity* this, Entity* child)
{
    if (child != 0) {
        // child->slotType: 0 = first slot (offset 0x10), 1 = second slot (offset 0x14)
        if (*(short*)(child + 0x78) == 0) {
            if (child == *(Entity**)(this + 0x10)) {
                *(int*)(this + 0x10) = 0;
            }
        }
        else if ((*(short*)(child + 0x78) == 1) && (child == *(Entity**)(this + 0x14))) {
            *(int*)(this + 0x14) = 0;
        }
    }
}