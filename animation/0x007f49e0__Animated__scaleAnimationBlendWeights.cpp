// FUNC_NAME: Animated::scaleAnimationBlendWeights
void __thiscall Animated::scaleAnimationBlendWeights(int this, float scale, char scaleFirstLayer, char scaleSecondLayer)
{
  undefined4 uVar1;
  
  if (scaleFirstLayer != '\0') {
    // Store the scale factor for the first animation layer (blend weight multiplier)
    *(float *)(this + 0x6d0) = scale;
    
    // Scale all 4-component blend weights for the first layer (0xCC - 0x2BC)
    // Each block is 0x10 bytes (4 floats) with a preserved 4th component
    uVar1 = *(undefined4 *)(this + 0xcc);
    *(float *)(this + 0xc0) = scale * *(float *)(this + 0xc0);
    *(float *)(this + 0xc4) = scale * *(float *)(this + 0xc4);
    *(float *)(this + 200) = scale * *(float *)(this + 200);
    *(float *)(this + 0xcc) = scale * *(float *)(this + 0xcc);
    *(undefined4 *)(this + 0xcc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0xdc);
    *(float *)(this + 0xd0) = scale * *(float *)(this + 0xd0);
    *(float *)(this + 0xd4) = scale * *(float *)(this + 0xd4);
    *(float *)(this + 0xd8) = scale * *(float *)(this + 0xd8);
    *(float *)(this + 0xdc) = scale * *(float *)(this + 0xdc);
    *(undefined4 *)(this + 0xdc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0xec);
    *(float *)(this + 0xe0) = scale * *(float *)(this + 0xe0);
    *(float *)(this + 0xe4) = scale * *(float *)(this + 0xe4);
    *(float *)(this + 0xe8) = scale * *(float *)(this + 0xe8);
    *(float *)(this + 0xec) = scale * *(float *)(this + 0xec);
    *(undefined4 *)(this + 0xec) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0xfc);
    *(float *)(this + 0xf0) = scale * *(float *)(this + 0xf0);
    *(float *)(this + 0xf4) = scale * *(float *)(this + 0xf4);
    *(float *)(this + 0xf8) = scale * *(float *)(this + 0xf8);
    *(float *)(this + 0xfc) = scale * *(float *)(this + 0xfc);
    *(undefined4 *)(this + 0xfc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x10c);
    *(float *)(this + 0x100) = scale * *(float *)(this + 0x100);
    *(float *)(this + 0x104) = scale * *(float *)(this + 0x104);
    *(float *)(this + 0x108) = scale * *(float *)(this + 0x108);
    *(float *)(this + 0x10c) = scale * *(float *)(this + 0x10c);
    *(undefined4 *)(this + 0x10c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x1bc);
    *(float *)(this + 0x1b0) = scale * *(float *)(this + 0x1b0);
    *(float *)(this + 0x1b4) = scale * *(float *)(this + 0x1b4);
    *(float *)(this + 0x1b8) = scale * *(float *)(this + 0x1b8);
    *(float *)(this + 0x1bc) = scale * *(float *)(this + 0x1bc);
    *(undefined4 *)(this + 0x1bc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x1ec);
    *(float *)(this + 0x1e0) = scale * *(float *)(this + 0x1e0);
    *(float *)(this + 0x1e4) = scale * *(float *)(this + 0x1e4);
    *(float *)(this + 0x1e8) = scale * *(float *)(this + 0x1e8);
    *(float *)(this + 0x1ec) = scale * *(float *)(this + 0x1ec);
    *(undefined4 *)(this + 0x1ec) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x21c);
    *(float *)(this + 0x210) = scale * *(float *)(this + 0x210);
    *(float *)(this + 0x214) = scale * *(float *)(this + 0x214);
    *(float *)(this + 0x218) = scale * *(float *)(this + 0x218);
    *(float *)(this + 0x21c) = scale * *(float *)(this + 0x21c);
    *(undefined4 *)(this + 0x21c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x24c);
    *(float *)(this + 0x240) = scale * *(float *)(this + 0x240);
    *(float *)(this + 0x244) = scale * *(float *)(this + 0x244);
    *(float *)(this + 0x248) = scale * *(float *)(this + 0x248);
    *(float *)(this + 0x24c) = scale * *(float *)(this + 0x24c);
    *(undefined4 *)(this + 0x24c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x27c);
    *(float *)(this + 0x270) = scale * *(float *)(this + 0x270);
    *(float *)(this + 0x274) = scale * *(float *)(this + 0x274);
    *(float *)(this + 0x278) = scale * *(float *)(this + 0x278);
    *(float *)(this + 0x27c) = scale * *(float *)(this + 0x27c);
    *(undefined4 *)(this + 0x27c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x2ac);
    *(float *)(this + 0x2a0) = scale * *(float *)(this + 0x2a0);
    *(float *)(this + 0x2a4) = scale * *(float *)(this + 0x2a4);
    *(float *)(this + 0x2a8) = scale * *(float *)(this + 0x2a8);
    *(float *)(this + 0x2ac) = scale * *(float *)(this + 0x2ac);
    *(undefined4 *)(this + 0x2ac) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x1cc);
    *(float *)(this + 0x1c0) = scale * *(float *)(this + 0x1c0);
    *(float *)(this + 0x1c4) = scale * *(float *)(this + 0x1c4);
    *(float *)(this + 0x1c8) = scale * *(float *)(this + 0x1c8);
    *(float *)(this + 0x1cc) = scale * *(float *)(this + 0x1cc);
    *(undefined4 *)(this + 0x1cc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x1fc);
    *(float *)(this + 0x1f0) = scale * *(float *)(this + 0x1f0);
    *(float *)(this + 500) = scale * *(float *)(this + 500);
    *(float *)(this + 0x1f8) = scale * *(float *)(this + 0x1f8);
    *(float *)(this + 0x1fc) = scale * *(float *)(this + 0x1fc);
    *(undefined4 *)(this + 0x1fc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x22c);
    *(float *)(this + 0x220) = scale * *(float *)(this + 0x220);
    *(float *)(this + 0x224) = scale * *(float *)(this + 0x224);
    *(float *)(this + 0x228) = scale * *(float *)(this + 0x228);
    *(float *)(this + 0x22c) = scale * *(float *)(this + 0x22c);
    *(undefined4 *)(this + 0x22c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x25c);
    *(float *)(this + 0x250) = scale * *(float *)(this + 0x250);
    *(float *)(this + 0x254) = scale * *(float *)(this + 0x254);
    *(float *)(this + 600) = scale * *(float *)(this + 600);
    *(float *)(this + 0x25c) = scale * *(float *)(this + 0x25c);
    *(undefined4 *)(this + 0x25c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x28c);
    *(float *)(this + 0x280) = scale * *(float *)(this + 0x280);
    *(float *)(this + 0x284) = scale * *(float *)(this + 0x284);
    *(float *)(this + 0x288) = scale * *(float *)(this + 0x288);
    *(float *)(this + 0x28c) = scale * *(float *)(this + 0x28c);
    *(undefined4 *)(this + 0x28c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 700);
    *(float *)(this + 0x2b0) = scale * *(float *)(this + 0x2b0);
    *(float *)(this + 0x2b4) = scale * *(float *)(this + 0x2b4);
    *(float *)(this + 0x2b8) = scale * *(float *)(this + 0x2b8);
    *(float *)(this + 700) = scale * *(float *)(this + 700);
    *(undefined4 *)(this + 700) = uVar1;
  }
  
  if (scaleSecondLayer != '\0') {
    // Store the scale factor for the second animation layer
    *(float *)(this + 0x6d4) = scale;
    
    // Scale all 4-component blend weights for the second layer (0x340 - 0x69C)
    uVar1 = *(undefined4 *)(this + 0x34c);
    *(float *)(this + 0x340) = scale * *(float *)(this + 0x340);
    *(float *)(this + 0x344) = scale * *(float *)(this + 0x344);
    *(float *)(this + 0x348) = scale * *(float *)(this + 0x348);
    *(float *)(this + 0x34c) = scale * *(float *)(this + 0x34c);
    *(undefined4 *)(this + 0x34c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x37c);
    *(float *)(this + 0x370) = scale * *(float *)(this + 0x370);
    *(float *)(this + 0x374) = scale * *(float *)(this + 0x374);
    *(float *)(this + 0x378) = scale * *(float *)(this + 0x378);
    *(float *)(this + 0x37c) = scale * *(float *)(this + 0x37c);
    *(undefined4 *)(this + 0x37c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x2ec);
    *(float *)(this + 0x2e0) = scale * *(float *)(this + 0x2e0);
    *(float *)(this + 0x2e4) = scale * *(float *)(this + 0x2e4);
    *(float *)(this + 0x2e8) = scale * *(float *)(this + 0x2e8);
    *(float *)(this + 0x2ec) = scale * *(float *)(this + 0x2ec);
    *(undefined4 *)(this + 0x2ec) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x31c);
    *(float *)(this + 0x310) = scale * *(float *)(this + 0x310);
    *(float *)(this + 0x314) = scale * *(float *)(this + 0x314);
    *(float *)(this + 0x318) = scale * *(float *)(this + 0x318);
    *(float *)(this + 0x31c) = scale * *(float *)(this + 0x31c);
    *(undefined4 *)(this + 0x31c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x39c);
    *(float *)(this + 0x390) = scale * *(float *)(this + 0x390);
    *(float *)(this + 0x394) = scale * *(float *)(this + 0x394);
    *(float *)(this + 0x398) = scale * *(float *)(this + 0x398);
    *(float *)(this + 0x39c) = scale * *(float *)(this + 0x39c);
    *(undefined4 *)(this + 0x39c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x3cc);
    *(float *)(this + 0x3c0) = scale * *(float *)(this + 0x3c0);
    *(float *)(this + 0x3c4) = scale * *(float *)(this + 0x3c4);
    *(float *)(this + 0x3c8) = scale * *(float *)(this + 0x3c8);
    *(float *)(this + 0x3cc) = scale * *(float *)(this + 0x3cc);
    *(undefined4 *)(this + 0x3cc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x3ac);
    *(float *)(this + 0x3a0) = scale * *(float *)(this + 0x3a0);
    *(float *)(this + 0x3a4) = scale * *(float *)(this + 0x3a4);
    *(float *)(this + 0x3a8) = scale * *(float *)(this + 0x3a8);
    *(float *)(this + 0x3ac) = scale * *(float *)(this + 0x3ac);
    *(undefined4 *)(this + 0x3ac) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x3dc);
    *(float *)(this + 0x3d0) = scale * *(float *)(this + 0x3d0);
    *(float *)(this + 0x3d4) = scale * *(float *)(this + 0x3d4);
    *(float *)(this + 0x3d8) = scale * *(float *)(this + 0x3d8);
    *(float *)(this + 0x3dc) = scale * *(float *)(this + 0x3dc);
    *(undefined4 *)(this + 0x3dc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x40c);
    *(float *)(this + 0x400) = scale * *(float *)(this + 0x400);
    *(float *)(this + 0x404) = scale * *(float *)(this + 0x404);
    *(float *)(this + 0x408) = scale * *(float *)(this + 0x408);
    *(float *)(this + 0x40c) = scale * *(float *)(this + 0x40c);
    *(undefined4 *)(this + 0x40c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x43c);
    *(float *)(this + 0x430) = scale * *(float *)(this + 0x430);
    *(float *)(this + 0x434) = scale * *(float *)(this + 0x434);
    *(float *)(this + 0x438) = scale * *(float *)(this + 0x438);
    *(float *)(this + 0x43c) = scale * *(float *)(this + 0x43c);
    *(undefined4 *)(this + 0x43c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x46c);
    *(float *)(this + 0x460) = scale * *(float *)(this + 0x460);
    *(float *)(this + 0x464) = scale * *(float *)(this + 0x464);
    *(float *)(this + 0x468) = scale * *(float *)(this + 0x468);
    *(float *)(this + 0x46c) = scale * *(float *)(this + 0x46c);
    *(undefined4 *)(this + 0x46c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x49c);
    *(float *)(this + 0x490) = scale * *(float *)(this + 0x490);
    *(float *)(this + 0x494) = scale * *(float *)(this + 0x494);
    *(float *)(this + 0x498) = scale * *(float *)(this + 0x498);
    *(float *)(this + 0x49c) = scale * *(float *)(this + 0x49c);
    *(undefined4 *)(this + 0x49c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x4cc);
    *(float *)(this + 0x4c0) = scale * *(float *)(this + 0x4c0);
    *(float *)(this + 0x4c4) = scale * *(float *)(this + 0x4c4);
    *(float *)(this + 0x4c8) = scale * *(float *)(this + 0x4c8);
    *(float *)(this + 0x4cc) = scale * *(float *)(this + 0x4cc);
    *(undefined4 *)(this + 0x4cc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x4fc);
    *(float *)(this + 0x4f0) = scale * *(float *)(this + 0x4f0);
    *(float *)(this + 0x4f4) = scale * *(float *)(this + 0x4f4);
    *(float *)(this + 0x4f8) = scale * *(float *)(this + 0x4f8);
    *(float *)(this + 0x4fc) = scale * *(float *)(this + 0x4fc);
    *(undefined4 *)(this + 0x4fc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x52c);
    *(float *)(this + 0x520) = scale * *(float *)(this + 0x520);
    *(float *)(this + 0x524) = scale * *(float *)(this + 0x524);
    *(float *)(this + 0x528) = scale * *(float *)(this + 0x528);
    *(float *)(this + 0x52c) = scale * *(float *)(this + 0x52c);
    *(undefined4 *)(this + 0x52c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x55c);
    *(float *)(this + 0x550) = scale * *(float *)(this + 0x550);
    *(float *)(this + 0x554) = scale * *(float *)(this + 0x554);
    *(float *)(this + 0x558) = scale * *(float *)(this + 0x558);
    *(float *)(this + 0x55c) = scale * *(float *)(this + 0x55c);
    *(undefined4 *)(this + 0x55c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x58c);
    *(float *)(this + 0x580) = scale * *(float *)(this + 0x580);
    *(float *)(this + 0x584) = scale * *(float *)(this + 0x584);
    *(float *)(this + 0x588) = scale * *(float *)(this + 0x588);
    *(float *)(this + 0x58c) = scale * *(float *)(this + 0x58c);
    *(undefined4 *)(this + 0x58c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x5bc);
    *(float *)(this + 0x5b0) = scale * *(float *)(this + 0x5b0);
    *(float *)(this + 0x5b4) = scale * *(float *)(this + 0x5b4);
    *(float *)(this + 0x5b8) = scale * *(float *)(this + 0x5b8);
    *(float *)(this + 0x5bc) = scale * *(float *)(this + 0x5bc);
    *(undefined4 *)(this + 0x5bc) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x5ec);
    *(float *)(this + 0x5e0) = scale * *(float *)(this + 0x5e0);
    *(float *)(this + 0x5e4) = scale * *(float *)(this + 0x5e4);
    *(float *)(this + 0x5e8) = scale * *(float *)(this + 0x5e8);
    *(float *)(this + 0x5ec) = scale * *(float *)(this + 0x5ec);
    *(undefined4 *)(this + 0x5ec) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x61c);
    *(float *)(this + 0x610) = scale * *(float *)(this + 0x610);
    *(float *)(this + 0x614) = scale * *(float *)(this + 0x614);
    *(float *)(this + 0x618) = scale * *(float *)(this + 0x618);
    *(float *)(this + 0x61c) = scale * *(float *)(this + 0x61c);
    *(undefined4 *)(this + 0x61c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x64c);
    *(float *)(this + 0x640) = scale * *(float *)(this + 0x640);
    *(float *)(this + 0x644) = scale * *(float *)(this + 0x644);
    *(float *)(this + 0x648) = scale * *(float *)(this + 0x648);
    *(float *)(this + 0x64c) = scale * *(float *)(this + 0x64c);
    *(undefined4 *)(this + 0x64c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x67c);
    *(float *)(this + 0x670) = scale * *(float *)(this + 0x670);
    *(float *)(this + 0x674) = scale * *(float *)(this + 0x674);
    *(float *)(this + 0x678) = scale * *(float *)(this + 0x678);
    *(float *)(this + 0x67c) = scale * *(float *)(this + 0x67c);
    *(undefined4 *)(this + 0x67c) = uVar1;
    
    uVar1 = *(undefined4 *)(this + 0x69c);
    *(float *)(this + 0x690) = scale * *(float *)(this + 0x690);
    *(float *)(this + 0x694) = scale * *(float *)(this + 0x694);
    *(float *)(this + 0x698) = scale * *(float *)(this + 0x698);
    *(float *)(this + 0x69c) = scale * *(float *)(this + 0x69c);
    *(undefined4 *)(this + 0x69c) = uVar1;
  }
}