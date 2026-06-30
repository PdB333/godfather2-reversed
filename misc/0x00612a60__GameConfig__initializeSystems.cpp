// FUNC_NAME: GameConfig::initializeSystems

void __fastcall GameConfig::initializeSystems(GameConfig* this)
{
    // Store global reference to this config instance
    g_pGameConfig = this;

    // Initialize subsystem A and subsystem B (likely sound/UI/rendering)
    ComponentSystem::reset(*(ComponentSystem**)(this + 0x10)); // m_pSystemA
    ComponentSystem::reset(*(ComponentSystem**)(this + 0x14)); // m_pSystemB

    // Bind component at offset 0x94 (some animation or effect) to system B
    if (*(int*)(this + 0x94) != 0) {
        g_AnimConfig1 = g_GlobalAnimSource1;  // copy from static globals
        g_AnimConfig2 = g_GlobalAnimSource2;
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(this + 0x14),
            *(int*)(this + 0x94),
            &g_AnimConfig1);
    }

    // Bind component at offset 0x18 to system A with config g_ComponentConfig[0]
    if (*(int*)(this + 0x18) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x18),
            &g_ComponentConfig_0);
    }

    // offset 0x1c -> system A, bindComponent
    if (*(int*)(this + 0x1c) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x1c),
            &g_ComponentConfig_1);
    }

    // offset 0x20 -> system A, bindChannel
    if (*(int*)(this + 0x20) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x20),
            &g_ComponentConfig_2);
    }

    // offset 0x24 -> system A, bindComponent
    if (*(int*)(this + 0x24) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x24),
            &g_ComponentConfig_3);
    }

    // offset 0x28 -> system A, bindChannel
    if (*(int*)(this + 0x28) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x28),
            &g_ComponentConfig_4);
    }

    // offset 0x2c -> system A, bindComponentEx with mode 3
    if (*(int*)(this + 0x2c) != 0) {
        ComponentSystem::bindComponentEx(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x2c),
            &g_ComponentConfig_4,
            3);
    }

    // offset 0x30 -> system A, bindChannel
    if (*(int*)(this + 0x30) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x30),
            &g_ComponentConfig_5);
    }

    // offset 0x34 -> system A, bindComponentEx with mode 3
    if (*(int*)(this + 0x34) != 0) {
        ComponentSystem::bindComponentEx(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x34),
            &g_ComponentConfig_5,
            3);
    }

    // offset 0x38 -> system A, bindComponentEx with mode 3
    if (*(int*)(this + 0x38) != 0) {
        ComponentSystem::bindComponentEx(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x38),
            &g_ComponentConfig_6,
            3);
    }

    // offset 0x3c -> system A, bindChannel
    if (*(int*)(this + 0x3c) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x3c),
            &g_ComponentConfig_7);
    }

    // offset 0x40 -> system A, bindChannel
    if (*(int*)(this + 0x40) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x40),
            &g_ComponentConfig_8);
    }

    // offset 0x44 -> system A, bindComponentEx with mode 3
    if (*(int*)(this + 0x44) != 0) {
        ComponentSystem::bindComponentEx(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x44),
            &g_ComponentConfig_8,
            3);
    }

    // offset 0x48 -> system A, bindChannel
    if (*(int*)(this + 0x48) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x48),
            &g_ComponentConfig_9);
    }

    // offset 0x4c -> system A, bindChannel
    if (*(int*)(this + 0x4c) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x4c),
            &g_ComponentConfig_10);
    }

    // offset 0x50 -> system A, bindChannel
    if (*(int*)(this + 0x50) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x50),
            &g_ComponentConfig_11);
    }

    // offset 0x54 -> system A, bindChannel
    if (*(int*)(this + 0x54) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x54),
            &g_ComponentConfig_12);
    }

    // offset 0x58 -> system A, bindComponent
    if (*(int*)(this + 0x58) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x58),
            &g_ComponentConfig_13);
    }

    // offset 0x5c -> system A, bindChannel
    if (*(int*)(this + 0x5c) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x5c),
            &g_ComponentConfig_14);
    }

    // offset 0x60 -> system B, bindComponent
    if (*(int*)(this + 0x60) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(this + 0x14),
            *(int*)(this + 0x60),
            &g_ComponentConfig_15);
    }

    // offset 100 (0x64) -> system A, bindComponent
    if (*(int*)(this + 0x64) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(this + 0x10),
            *(int*)(this + 0x64),
            &g_ComponentConfig_15);
    }

    // offset 0x6c -> system B, bindComponent
    if (*(int*)(this + 0x6c) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(this + 0x14),
            *(int*)(this + 0x6c),
            &g_ComponentConfig_1);  // reuse same config as offset 0x1c
    }

    // offset 0x70 -> system B, bindComponent
    if (*(int*)(this + 0x70) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(this + 0x14),
            *(int*)(this + 0x70),
            &g_ComponentConfig_16);
    }

    // offset 0x74 -> system B, bindComponent
    if (*(int*)(this + 0x74) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(this + 0x14),
            *(int*)(this + 0x74),
            &g_ComponentConfig_17);
    }

    // offset 0x8c (via global reference) -> system A, bindComponent
    if (*(int*)(g_pGameConfig + 0x8c) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(g_pGameConfig + 0x10),
            *(int*)(g_pGameConfig + 0x8c),
            &g_ComponentConfig_18);
    }

    // offset 0x90 (via global reference) -> system B, bindComponent
    if (*(int*)(g_pGameConfig + 0x90) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(g_pGameConfig + 0x14),
            *(int*)(g_pGameConfig + 0x90),
            &g_ComponentConfig_19);
    }

    // offset 0x78 -> system B, bindComponent
    if (*(int*)(this + 0x78) != 0) {
        ComponentSystem::bindComponent(
            *(ComponentSystem**)(this + 0x14),
            *(int*)(this + 0x78),
            &g_ComponentConfig_20);
    }

    // offset 0x7c -> system B, bindChannel
    if (*(int*)(this + 0x7c) != 0) {
        ComponentSystem::bindChannel(
            *(ComponentSystem**)(this + 0x14),
            *(int*)(this + 0x7c),
            &g_ComponentConfig_5);
    }

    // offset 0x80 -> system B, bindComponentEx with mode 3
    if (*(int*)(this + 0x80) != 0) {
        ComponentSystem::bindComponentEx(
            *(ComponentSystem**)(this + 0x14),
            *(int*)(this + 0x80),
            &g_ComponentConfig_5,
            3);
    }

    // offset 0x84 -> system B, bindComponentEx with mode 3
    if (*(int*)(this + 0x84) != 0) {
        ComponentSystem::bindComponentEx(
            *(ComponentSystem**)(this + 0x14),
            *(int*)(this + 0x84),
            &g_ComponentConfig_6,
            3);
    }

    // offset 0xa0 -> separate initialization for some sub-component
    if (*(int*)(this + 0xa0) != 0) {
        ComponentSubSystem::finalize();
    }
}