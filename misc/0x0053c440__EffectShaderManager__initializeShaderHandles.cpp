// FUNC_NAME: EffectShaderManager::initializeShaderHandles

void __thiscall EffectShaderManager::initializeShaderHandles(void)
{
    int iVar1;
    int iVar2;
    int *piVar3;
    uint uVar4;

    // Store the system material/shader references
    iVar1 = createDefaultShader();                      // FUN_0060a380
    *(int *)(this + 0x10) = iVar1;
    iVar1 = loadShaderFromCache(&g_pShaderCache);       // FUN_0060a2e0(&PTR_DAT_010bde70)
    *(int *)(this + 0x14) = iVar1;

    g_pGlobalShaders = (int *)this;
    g_GlobalInitDone();                                  // FUN_006127d0

    // Store shader pointers into global variables for fast access
    DAT_01198e48 = *(int *)(this + 0x10);
    DAT_01198e70 = *(int *)(this + 0x14);
    DAT_01198e74 = createDefaultShader();                // FUN_0060a380
    DAT_01198e54 = loadShaderFromCache(&g_pShaderX);    // &PTR_DAT_010bdeb0
    DAT_01198e4c = loadShaderFromCache(&g_pShaderY);    // &PTR_DAT_010bdea0
    DAT_01194d04 = loadShaderFromCache(&g_pShaderZ);    // &PTR_DAT_010bdf30
    DAT_01198e68 = loadShaderFromCache(&g_pShaderW);    // &PTR_DAT_010bdef0
    DAT_01198e50 = loadShaderFromCache(&g_pShaderV);    // &PTR_DAT_010bdf10
    DAT_01198e58 = loadShaderFromCache(&g_pShaderU);    // &PTR_DAT_010bded0
    DAT_01198e6c = loadShaderFromCache(&g_pShaderT);    // &PTR_DAT_010bdf00
    DAT_01198e60 = loadShaderFromCache(&g_pShaderS);    // &PTR_DAT_010bdf20
    DAT_01198e64 = loadShaderFromCache(&g_pShaderR);    // &PTR_DAT_010bde80
    DAT_01198e78 = loadShaderFromCache(&g_pShaderQ);    // &PTR_DAT_010bdee0
    DAT_01198e5c = loadShaderFromCache(&g_pShaderP);    // &PTR_DAT_010bdec0

    // Initialize particle shader parameter handles (3 shaders, 3 parameters each)
    // Structure at offset 0xa4: [particlePosAlpha, ?, ?]
    piVar3 = (int *)(this + 0xa8);
    uVar4 = 0;
    do {
        int *pShader = *(int **)((int)&g_particleShaderList + uVar4);  // PTR_DAT_010bebd4
        iVar2 = getShaderParameterHandle(*pShader, "world_particle_pos3_alpha");
        piVar3[-1] = iVar2;
        iVar2 = getShaderParameterHandle(*pShader, "...");              // PTR_LAB_00763274_3_00e38600 (unidentified)
        *piVar3 = iVar2;
        iVar1 = getShaderParameterHandle(*pShader, "...");              // DAT_00e388d4
        piVar3[1] = iVar1;
        uVar4 += 4;
        piVar3 += 3;
    } while (uVar4 < 0xc);

    // Initialize displacement/water shader parameter handles (52 shaders, 8 parameters each)
    // Structure at offset 0xcc: [texSampler, texMask, displaceSampler, colorMult, deltaUV, additive, multiply, scaling]
    piVar3 = (int *)(this + 0xd0);
    uVar4 = 0;
    do {
        int *pShader = *(int **)((int)&g_waterShaderList + uVar4);      // PTR_DAT_010beba0
        iVar2 = getShaderParameterHandle(*pShader, "displacement_sampler");
        piVar3[1] = iVar2;
        iVar2 = getShaderParameterHandle(*pShader, "texture_mask");
        *piVar3 = iVar2;
        iVar2 = getShaderParameterHandle(*pShader, "texture_sampler");
        piVar3[-1] = iVar2;
        iVar2 = getShaderParameterHandle(*pShader, "colorMult_colorOffset_isCenter_lerpValue");
        piVar3[2] = iVar2;
        iVar2 = getShaderParameterHandle(*pShader, "deltaUV_centerUV");
        piVar3[3] = iVar2;
        iVar2 = getShaderParameterHandle(*pShader, "additivepass");
        piVar3[4] = iVar2;
        iVar2 = getShaderParameterHandle(*pShader, "multiplypass");
        piVar3[5] = iVar2;
        iVar1 = getShaderParameterHandle(*pShader, "scaling");
        piVar3[6] = iVar1;
        uVar4 += 4;
        piVar3 += 8;
    } while (uVar4 < 0x34);

    // Store vertex shader parameter handle
    iVar1 = getShaderParameterHandle(DAT_01198e74, "vPosScaleTranslationVS");
    *(int *)(this + 0x270) = iVar1;

    return;
}