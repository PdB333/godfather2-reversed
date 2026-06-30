// FUNC_NAME: Entity::Entity (0x004f3390)
// Constructor with flags parameter. Bit 0 of flags controls additional initialization.
Entity::Entity(unsigned char flags) {
    // Call base class initialization (FUN_004f3850)
    this->initBase();

    if (flags & 1) {
        // If placement-new flag is set, perform extra construction steps (FUN_009c8eb0)
        this->onPlacementConstruct();
    }
}