// FUNC_NAME: Entity::setID
void __thiscall Entity::setID(int this, int newID)
{
    // Set the ID at offset 0x60, only if different to avoid unnecessary updates
    if (*(int *)(this + 0x60) != newID) {
        *(int *)(this + 0x60) = newID;
    }
}