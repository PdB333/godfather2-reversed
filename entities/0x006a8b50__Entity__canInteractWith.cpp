// FUNC_NAME: Entity::canInteractWith
bool __thiscall Entity::canInteractWith(Entity* this, EntityRef* otherRef) {
    byte local_byte;
    EntityComponent* otherComponent;
    
    local_byte = 0;
    if (((this->exists != 0) && (otherRef->entityPtr != 0)) &&
        (otherComponent = otherRef->componentPtr, otherComponent != 0)) {
        
        // Check if both entity's existence flags are set and base pointers are valid
        if ((this->entityData != 0) && (this->componentPtr != 0)) {
            // If the other component has the "teamCheck" flag (bit 2 in +0x21)
            if ((otherComponent->flags & 2) != 0) {
                // If this entity's teamMask is zero, return false
                if (this->teamMask == 0) {
                    return false;
                }
                // If other component's teamMask is zero, return false
                if (otherComponent->teamMask == 0) {
                    return false;
                }
                // If team masks overlap (i.e., same team), return false
                if ((otherComponent->teamMask & this->teamMask) != 0) {
                    return false;
                }
            }
            local_byte = 1;
        }
    }
    return local_byte;
}