// FUNC_NAME: PostEffectManager::init
void __fastcall PostEffectManager::init(int this)
{
    undefined4 uVar1;
    bool bVar2;
    undefined **ppuVar3;

    FUN_006127d0(); // likely base class init or memory clear
    *(undefined4 *)(this + 300) = 0; // +0x12C: some flag or pointer
    FUN_00530630(); // likely shader/effect setup
    if (DAT_0120575b == '\0') {
        ppuVar3 = &PTR_DAT_010be990; // low quality shader set
    }
    else {
        ppuVar3 = &PTR_DAT_010be980; // high quality shader set
    }
    uVar1 = FUN_0060a2e0(ppuVar3); // load shader effect
    *(undefined4 *)(this + 0x108) = uVar1; // +0x108: effect pointer (main scene)
    uVar1 = FUN_0060a2e0(&PTR_DAT_010be9e0); // load another effect
    *(undefined4 *)(this + 0x110) = uVar1; // +0x110: effect pointer (blur horizontal?)
    uVar1 = FUN_0060a2e0(&PTR_DAT_010be9f0); // load another effect
    *(undefined4 *)(this + 0x10c) = uVar1; // +0x10C: effect pointer (blur vertical?)
    uVar1 = FUN_0060a2e0(&PTR_DAT_010be9d0); // load another effect
    *(undefined4 *)(this + 0x114) = uVar1; // +0x114: effect pointer (combine?)
    uVar1 = FUN_0060a2e0(&PTR_DAT_010be9c0); // load another effect
    bVar2 = DAT_0120575b == '\0';
    *(undefined4 *)(this + 0x118) = uVar1; // +0x118: effect pointer (screen texture?)
    *(undefined4 *)(this + 0xd8) = 0; // +0xD8: shader parameter handle
    *(undefined4 *)(this + 0xdc) = 0; // +0xDC: shader parameter handle
    *(undefined4 *)(this + 0xe0) = 0; // +0xE0: shader parameter handle
    if (bVar2) {
        uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x108), "queryModulateAlpha");
        *(undefined4 *)(this + 0xe0) = uVar1; // +0xE0: queryModulateAlpha handle
    }
    else {
        uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x108), "modulate_by_corona_info");
        *(undefined4 *)(this + 0xd8) = uVar1; // +0xD8: modulate_by_corona_info handle
        uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x108), "modulate_sampler");
        *(undefined4 *)(this + 0xdc) = uVar1; // +0xDC: modulate_sampler handle
    }
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x108), "screen_color");
    *(undefined4 *)(this + 0xfc) = uVar1; // +0xFC: screen_color handle
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x118), "screen_texture");
    *(undefined4 *)(this + 0x100) = uVar1; // +0x100: screen_texture handle
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x118), "screen_texture_halfPixelOffset");
    *(undefined4 *)(this + 0x104) = uVar1; // +0x104: screen_texture_halfPixelOffset handle
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x10c), "oneOverSize");
    *(undefined4 *)(this + 0xe8) = uVar1; // +0xE8: oneOverSize handle (vertical blur)
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x110), "oneOverSize");
    *(undefined4 *)(this + 0xe4) = uVar1; // +0xE4: oneOverSize handle (horizontal blur)
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x10c), "depth_textureZ");
    *(undefined4 *)(this + 0xf0) = uVar1; // +0xF0: depth_textureZ handle (vertical blur)
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x110), "depth_textureZ");
    *(undefined4 *)(this + 0xf4) = uVar1; // +0xF4: depth_textureZ handle (horizontal blur)
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x118), "oneOverSize");
    *(undefined4 *)(this + 0xec) = uVar1; // +0xEC: oneOverSize handle (screen texture)
    uVar1 = FUN_0060a2e0(&PTR_DAT_010bea00); // load another effect (depth of field?)
    *(undefined4 *)(this + 0x128) = uVar1; // +0x128: effect pointer (DoF)
    uVar1 = FUN_0060a580(uVar1, "oneOverSize");
    *(undefined4 *)(this + 0x11c) = uVar1; // +0x11C: oneOverSize handle (DoF)
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x128), "texture_lowres");
    *(undefined4 *)(this + 0x120) = uVar1; // +0x120: texture_lowres handle (DoF)
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x128), "texture_stencil");
    *(undefined4 *)(this + 0x124) = uVar1; // +0x124: texture_stencil handle (DoF)
    uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x114), "screen_texture");
    *(undefined4 *)(this + 0xf8) = uVar1; // +0xF8: screen_texture handle (combine)
    return;
}