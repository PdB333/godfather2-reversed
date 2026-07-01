// FUNC_NAME: Entity::stopChildObjects
void __fastcall Entity::stopChildObjects(Entity* this)
{
    // Check flag at offset +0x2bc (param_1[0xaf]) bit 23
    if ((this->flags & 0x800000) != 0) {
        // Call virtual function at vtable offset 0xb0 on child at +0x380 (param_1 + 0xe0)
        (this->vtable->release)(&this->childA, 0);
    }
    // Always release child at +0x360 (param_1 + 0xd8)
    (this->vtable->release)(&this->childB, 0);
}