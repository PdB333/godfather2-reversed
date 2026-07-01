// FUNC_NAME: Entity::createDonControlGadget
void Entity::createDonControlGadget(void) {
    char isActive;
    
    isActive = GameplayControl::isActive(); // FUN_00481660
    if (isActive != '\0') {
        void* memory = GpmMemory::allocate(0x38); // FUN_009c8e50
        if (memory != (void*)0x0) {
            DonControlGadget* gadget = new (memory) DonControlGadget(this); // FUN_0079fc50
            this->setActiveGadget(gadget); // FUN_00481690
            return;
        }
        this->setActiveGadget((DonControlGadget*)0x0);
    }
    return;
}