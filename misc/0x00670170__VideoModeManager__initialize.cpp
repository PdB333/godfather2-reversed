// FUNC_NAME: VideoModeManager::initialize
// Function at 0x00670170: Initializes video mode manager (constructor/init)
// Sets up display device, mode, and renderer; configures resolution thresholds.

void VideoModeManager::initialize() {
    // Clear first several fields (0..5)
    this->field_0x00 = 0;
    this->field_0x04 = 0;
    this->field_0x08 = 0;
    this->field_0x0C = 0;
    this->field_0x10 = 0xFFFFFFFF; // +0x10
    this->field_0x14 = 0;

    // Set global resolution configuration based on screen width
    gDisplayMode = (gScreenWidth > 720) ? DAT_00e445a0 : DAT_00e2b1a0; // _DAT_00f0ccb0 = select based on width

    // Base initialization (likely parent class)
    baseInitialize();

    // Set secondary fields (at offsets 0x198..0x1A8)
    this->field_0x198 = 0xFFFFFFFF;
    this->field_0x1A0 = 0xFFFFFFFF;
    this->field_0x1A4 = 0xFFFFFFFF;
    this->field_0x19C = 0;
    this->field_0x1A8 = 0x6E; // 'n'

    // Create display device and store in first field
    int unusedLocal;
    this->pDisplayDevice = createDisplayDevice(); // FUN_00672680

    // Create display mode object, gets pointer stored in second field
    this->pDisplayMode = createDisplayMode(&unusedLocal); // FUN_006719c0

    // Initialize renderer
    initializeRenderer(); // FUN_00671040

    // Configure display mode parameters at offset 0x1E28 in the mode object
    uint16_t* modeParams = reinterpret_cast<uint16_t*>(this->pDisplayMode + 0x1E28);
    modeParams[0] = 3;    // width or resolution index
    modeParams[1] = 1;    // height or something
    modeParams[2] = 0x409;// refresh rate or mode flag
    modeParams[3] = 1;    // additional flag

    // Set last fields
    this->field_0x14 = 0;
    this->field_0x0C = 1;
}