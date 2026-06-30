// FUNC_NAME: Entity::Entity
// Address: 0x004f0140
// Role: Constructor for Entity class, initializes from parent config

Entity* Entity::Entity(Entity* this, Config* config, ExtraData* extraData) {
    // Call base class constructor (FUN_00533cc0)
    BaseClass::BaseClass();

    // Set vtable pointer
    this->vtable = &Entity_vtable; // PTR_FUN_00e373b0

    // Initialize field at offset 0x24 to 0
    this->field_0x24 = 0; // param_1[9]

    // Check if config has skip flag at offset 0xd
    if (config->skipInit == 0) { // *(char *)(param_2 + 0xd) == '\0'
        int someValue = this->dataBlock->someField; // *(int *)(param_1[1] + 0xc4)
        int adjustedOffset;
        if (someValue == 0 ||
            ((adjustedOffset = someValue - 0x48, adjustedOffset != 0 &&
              (*(int *)(someValue + 0x11c) == 0)))) {
            adjustedOffset = 0;
        }
        this->field_0x24 = extraData; // unaff_EDI

        // Initialize three sub-objects (FUN_004ebb40)
        initSubObject();
        initSubObject();
        initSubObject();

        if (adjustedOffset == 0) {
            config->initComplete = 1; // *(undefined1 *)(param_2 + 0xc) = 1
            return this;
        }

        // Complex initialization (FUN_004efd70)
        complexInit(this,
                    this->dataBlock->someOtherField, // *(undefined4 *)(param_1[1] + 0x10)
                    adjustedOffset + 0x54,
                    extraData->field0, // *unaff_EDI
                    extraData->field1, // unaff_EDI[1]
                    combine(extraData->field2, extraData->field9), // CONCAT44
                    extraData->field_0x4c, // *(undefined8 *)((int)unaff_EDI + 0x4c)
                    this->field_0x10, // param_1[4]
                    this->field_0x14); // param_1[5]
    }
    return this;
}