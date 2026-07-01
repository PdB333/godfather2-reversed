// Xbox PDB: EARS::CubeRender::PresentationOpen
// FUNC_NAME: RenderManager::initRenderViews
void RenderManager::initRenderViews() {
    // Clear / reset render targets
    FUN_006154e0(*(void**)DAT_012052f0, 0); // likely a render target or surface
    FUN_006154e0(*(void**)DAT_012052f4, 0);

    // Setup main render view
    int* renderView = (int*)DAT_01205308; // assume global pointer to view struct
    FUN_00422a40(*(void**)DAT_01205300, *(void**)DAT_012052f8, 0, 0); // set viewport or projection
    FUN_00422fb0(*(void**)DAT_00e2a850, 1.0f); // 0x3f800000 -> 1.0
    renderView[0x144 / 4] = *(int*)DAT_00e2fc48; // +0x144: some field
    renderView[0x148 / 4] = *(int*)DAT_0110ae44; // +0x148: another field
    FUN_00423900(); // commit/flush current render command

    // Check if we can push command (TLS flag)
    int* tlsPtr = *(int**)(*(int*)(__readfsdword(0x2C)) + 0x34); // actually: fs:[0x2C] yields TLS array pointer, then [0x34] is a flag
    if (*tlsPtr == 0) {
        // Bump allocator for render commands
        int* poolPos = *(int**)(DAT_01206880 + 0x14); // current position in command pool
        **(int***)poolPos = &PTR_LAB_0110b6a4; // vtable for command type
        *poolPos = *poolPos + 4; // advance past vtable (pool is int*)
        *(int*)(*poolPos) = (int)renderView; // store render view pointer
        int currentPool = *poolPos;
        *(int*)(currentPool + 4) = *(int*)DAT_00e2fc48; // first parameter
        *(int*)(currentPool + 8) = *(int*)DAT_0110ae44; // second parameter
        *poolPos = currentPool + 12; // advance by 3 ints
    }

    // Create SkyCubeRender object
    int skyCube = FUN_00422590("SkyCubeRender");
    DAT_01205310 = skyCube;

    // Setup SkyCubeRender view (same pattern)
    int* skyView = (int*)skyCube;
    FUN_00422a40(*(void**)DAT_01205300, *(void**)DAT_012052f8, 0, 0);
    FUN_00422fb0(*(void**)DAT_00e2a850, 1.0f);
    skyView[0x144 / 4] = *(int*)DAT_00e2fc48;
    skyView[0x148 / 4] = *(int*)DAT_0110ae44;
    FUN_00423900();

    // Push command for sky cube
    if (*tlsPtr == 0) {
        int* poolPos = *(int**)(DAT_01206880 + 0x14);
        **(int***)poolPos = &PTR_LAB_0110b6a4;
        *poolPos = *poolPos + 4;
        *(int*)(*poolPos) = (int)skyView;
        int currentPool = *poolPos;
        *(int*)(currentPool + 4) = *(int*)DAT_00e2fc48;
        *(int*)(currentPool + 8) = *(int*)DAT_0110ae44;
        *poolPos = currentPool + 12;
    }

    // Final initialization step
    FUN_00413ee0();
    DAT_01205320 = 1; // flag that render views are initialized
}