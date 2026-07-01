// FUNC_NAME: Entity::stopComponents
void __fastcall Entity::stopComponents(Entity* this) // 0x00793840
{
    // Check if bit 23 (0x17) of field at +0x2BC is set (flag indicating component active)
    if ((this->field_0x2BC >> 23) & 1)
    {
        // Call virtual function at vtable offset 0xB0 on sub-component at +0xE0, passing 0
        (this->vtable[0xB0 / 4])(&this->componentE0, 0);
    }
    // Unconditionally call same virtual function on sub-component at +0xD4, passing 0
    (this->vtable[0xB0 / 4])(&this->componentD4, 0);
}