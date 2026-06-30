// FUNC_NAME: GameSettingsManager::initializeSettings
// Address: 0x00691b50
// Role: Initializes game settings by registering hash constants and populating slot entries from a data table.
void GameSettingsManager::initializeSettings(void *configData) {
    // Register hash constants with the config data. These hashes likely represent property names or categories.
    registerHashConstant(0x64ce24d7, configData); // e.g., "someSetting1"
    registerHashConstant(0x657a83a5, configData); // e.g., "someSetting2"
    registerHashConstant(0xa08a43df, configData); // e.g., "someSetting3"

    // Retrieve the manager pointer (unaff_ESI) via a hash pair; assume this is a singleton lookup.
    if (getManager(this, 0xa7879506, 0xf0c639eb)) {
        // Load data blocks (strings?) and set them into the manager at specific slots.
        uint64_t value = loadDataBlock(0, &LAB_00690c10, 0x41, 1); // slot 0x1f: label "LAB_00690c10"
        this->setSlot(0x1f, value);
        setManagerProperty(0xa7879506, this, 0x1f); // Associate hash with this slot

        value = loadDataBlock(0, &LAB_00690c60, 0x23, 1); // slot 0x21: label "LAB_00690c60"
        this->setSlot(0x21, value);
        setManagerProperty(0xf0c639eb, this, 0x21);

        // Load integer constants (0 indicates simple int?) and set at subsequent slots
        value = loadIntConstant(0); // Returns a uint64_t from some source
        this->setSlot(0x28, value);
        setManagerProperty(0x776def75, this, 0x28);

        value = loadIntConstant(0);
        this->setSlot(0x29, value);
        setManagerProperty(0x78467823, this, 0x29);

        value = loadIntConstant(0);
        this->setSlot(0x0d, value); // slot 13
        setManagerProperty(0x1d8e854d, this, 0x0d);

        value = loadIntConstant(0);
        this->setSlot(0x0c, value); // slot 12
        setManagerProperty(0xc1e9c75, this, 0x0c);
    }

    // Register additional hash constants
    registerHashConstant(0x17a26743, configData);
    registerHashConstant(0x6ef11ea8, configData);
    registerHashConstant(0xbe16155b, configData);

    if (this) {
        // Load entries from a predefined data table (DAT_00691950) into slots 0x15-0x1e
        // Each call specifies a different size (likely byte count) from the table.
        // The table appears to contain variable-length data indexed sequentially.

        // Slot 0x15: size 8
        uint64_t value = loadDataBlock(0, &DAT_00691950, 8, 1);
        this->setSlot(0x15, value);
        setManagerProperty(0xc4aacd36, this, 0x15);

        // Slot 0x16: size 5
        value = loadDataBlock(0, &DAT_00691950, 5, 1);
        this->setSlot(0x16, value);
        setManagerProperty(0xc4aacd37, this, 0x16);

        // Slot 0x17: size 9
        value = loadDataBlock(0, &DAT_00691950, 9, 1);
        this->setSlot(0x17, value);
        setManagerProperty(0xc4aacd38, this, 0x17);

        // Slot 0x18: size 1
        value = loadDataBlock(0, &DAT_00691950, 1, 1);
        this->setSlot(0x18, value);
        setManagerProperty(0xc4aacd39, this, 0x18);

        // Slot 0x19: size 2
        value = loadDataBlock(0, &DAT_00691950, 2, 1);
        this->setSlot(0x19, value);
        setManagerProperty(0xc4aacd3a, this, 0x19);

        // Slot 0x1a: size 4
        value = loadDataBlock(0, &DAT_00691950, 4, 1);
        this->setSlot(0x1a, value);
        setManagerProperty(0xc4aacd3b, this, 0x1a);

        // Slot 0x1b: size 3
        value = loadDataBlock(0, &DAT_00691950, 3, 1);
        this->setSlot(0x1b, value);
        setManagerProperty(0xc4aacd3c, this, 0x1b);

        // Slot 0x1c: size 0 (empty?)
        value = loadDataBlock(0, &DAT_00691950, 0, 1);
        this->setSlot(0x1c, value);
        setManagerProperty(0xc4aacd3d, this, 0x1c);

        // Slot 0x1d: size 6
        value = loadDataBlock(0, &DAT_00691950, 6, 1);
        this->setSlot(0x1d, value);
        setManagerProperty(0xc4aacd3e, this, 0x1d);

        // Slot 0x1e: size 7
        value = loadDataBlock(0, &DAT_00691950, 7, 1);
        this->setSlot(0x1e, value);
        setManagerProperty(0xc4aacd3f, this, 0x1e);
    }

    // Final hash constant
    registerHashConstant(0xebc77d43, configData);
}