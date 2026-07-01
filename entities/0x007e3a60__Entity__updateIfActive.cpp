// FUNC_NAME: Entity::updateIfActive
void __thiscall Entity::updateIfActive(Entity* this)
{
    // Always perform base updates
    Entity::internalUpdate(this); // FUN_007e32f0
    Entity::postUpdate(this); // FUN_007e3560

    if (*(bool*)((uint8_t*)this + 0x80) != false) { // mActive flag at +0x80
        // Additional updates when entity is active
        Entity::activeUpdate(this); // FUN_007e34b0
        Entity::finalizeUpdate(this); // FUN_00800670
    }
}