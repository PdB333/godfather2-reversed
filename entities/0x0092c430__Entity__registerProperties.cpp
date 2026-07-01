// FUNC_NAME: Entity::registerProperties

void Entity::registerProperties(Entity *this)
{
    // Call base class property registration
    registerBaseProperties();

    // Register properties with type identifiers and optional callback functions
    // Structure offsets are relative to this (Entity) object

    // Offset 0x50 (80) - likely a float or int property
    registerProperty(&PROP_00e40ec8, &this->field_0x50, 0, nullptr, 0, 1);

    // Offset 0x5c (92) - another basic property
    registerProperty(&PROP_00d88ac8, &this->field_0x5c, 0, nullptr, 0, 1);

    // Offset 0x114 (276) - type 6 property
    registerProperty(&PROP_00d88ac0, &this->field_0x114, 6, nullptr, 0, 1);

    // Offset 0x110 (272) - type 6 property
    registerProperty(&PROP_00d88ab8, &this->field_0x110, 6, nullptr, 0, 1);

    // Offset 0x64 (100) - type 2 property (likely integer)
    registerProperty(&PROP_00d88ab0, &this->field_0x64, 2, nullptr, 0, 1);

    // Offset 0xf0 (240) - type 1 property (float)
    registerProperty(&PROP_00d88aa8, &this->field_0xf0, 1, nullptr, 0, 1);

    // Offset 0xf4 (244) - type 1 property with callback at 0x0092bc00
    registerProperty(&PROP_00d88aa0, &this->field_0xf4, 1, &LAB_0092bc00, 0, 0);

    // Offset 0xf8 (248) - type 1 property
    registerProperty(&PROP_00d88a98, &this->field_0xf8, 1, nullptr, 0, 1);

    // Offset 0xfc (252) - type 1 property
    registerProperty(&PROP_00d88a90, &this->field_0xfc, 1, nullptr, 0, 1);

    // Offset 0x100 (256) - type 1 property
    registerProperty(&PROP_00d88a88, &this->field_0x100, 1, nullptr, 0, 1);

    // Offset 0x104 (260) - type 6 property
    registerProperty(&PROP_00d88a80, &this->field_0x104, 6, nullptr, 0, 1);

    // Offset 0x108 (264) - type 6 property
    registerProperty(&PROP_00d88a78, &this->field_0x108, 6, nullptr, 0, 1);

    // Offset 0x10c (268) - type 6 property
    registerProperty(&PROP_00d88a70, &this->field_0x10c, 6, nullptr, 0, 1);

    // Offset 0x68 (104) - type 1 property
    registerProperty(&PROP_00d88a68, &this->field_0x68, 1, nullptr, 0, 1);

    // Offset 0x6c (108) - type 5 property with callback at 0x0092bbf0
    registerProperty(&PROP_00d88a60, &this->field_0x6c, 5, &LAB_0092bbf0, 0, 0);

    // Offset 0x128 (296) - type 1 property
    registerProperty(&PROP_00d88a58, &this->field_0x128, 1, nullptr, 0, 1);

    // Offset 0x12c (300) - type 1 property with callback at 0x0092c420
    registerProperty(&PROP_00d88a50, &this->field_0x12c, 1, &LAB_0092c420, 0, 0);

    // Offset 0x130 (304) - type 1 property
    registerProperty(&PROP_00d87b00, &this->field_0x130, 1, nullptr, 0, 1);

    // Offset 0x17c (380) - type 2 property (integer)
    registerProperty(&PROP_00d88a48, &this->field_0x17c, 2, nullptr, 0, 1);

    // Offset 0x134 (308) - type 1 property
    registerProperty(&PROP_00d88a40, &this->field_0x134, 1, nullptr, 0, 1);

    // Offset 0x140 (320) - type 1 property
    registerProperty(&PROP_00d88a38, &this->field_0x140, 1, nullptr, 0, 1);

    // Offset 0x144 (324) - type 1 property
    registerProperty(&PROP_00d88a30, &this->field_0x144, 1, nullptr, 0, 1);

    // Offset 0x148 (328) - type 1 property
    registerProperty(&PROP_00d88a28, &this->field_0x148, 1, nullptr, 0, 1);

    // Offset 0x14c (332) - type 1 property
    registerProperty(&PROP_00d88a20, &this->field_0x14c, 1, nullptr, 0, 1);

    // Offset 0x150 (336) - type 1 property
    registerProperty(&PROP_00d88a18, &this->field_0x150, 1, nullptr, 0, 1);

    // Offset 0x180 (384) - type 1 property with callback at 0x0092bc10
    registerProperty(&PROP_00d88a10, &this->field_0x180, 1, &LAB_0092bc10, 0, 0);
}