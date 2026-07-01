// FUNC_NAME: Entity::triggerCallback
/**
 * Address: 0x00838140
 * Role: Calls internal handler with two fields at offsets +0x17c and +0x18c.
 * Likely a dispatch or callback invoker.
 */
void Entity::triggerCallback() {
    // Dereference offsets 0x17c and 0x18c as arguments to handler
    handleAction(this, *(int*)(this + 0x17c), *(int*)(this + 0x18c));
}