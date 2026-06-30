// FUNC_NAME: EntityComponent::attachChild
// Address: 0x005f0490
// __thiscall with additional source pointer in EDI (non-standard register parameter)
bool EntityComponent::attachChild(EntityComponent* source) {  // source passed via EDI
    EntityComponent* child = *(EntityComponent**)(this + 0x0C); // +0x0C: child component pointer
    if (child != nullptr) {
        // Pre-initialization step (e.g., validate state)
        this->prepChild();
        
        if (*(uint32_t*)(source + 0x04) != 0) {
            // Copy source's reference to child's offset 0x44, then clear source's reference
            *(uint32_t*)(child + 0x44) = *(uint32_t*)(source + 0x04); // +0x44: parent pointer
            *(uint32_t*)(source + 0x04) = 0;
        }
        
        // Triple validation steps
        if (this->validateChild() && 
            this->activateChild() && 
            this->finalizeSetup(child)) {
            return true;
        }
    }
    return false;
}