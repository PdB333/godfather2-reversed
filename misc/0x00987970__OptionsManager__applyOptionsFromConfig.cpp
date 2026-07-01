// FUNC_NAME: OptionsManager::applyOptionsFromConfig
void __fastcall OptionsManager::applyOptionsFromConfig(int this)
{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_10;
  
  iVar1 = DAT_01129938; // global config pointer
  *(undefined4 *)(this + 0x54) = 0; // currentOptionIndex = 0
  if (*(int *)(this + 0x60) != 0) { // optionCount != 0
    do {
      if (*(int *)(this + 0x58) == 0) { // optionType == 0 (video options)
        iVar3 = *(int *)(this + 0x54); // currentOptionIndex
        if (iVar3 == 0) {
          // Resolution
          local_10 = (undefined4)(longlong)ROUND(DAT_00d5d7b8 * *(float *)(iVar1 + 0x1c));
          goto LAB_00987c26;
        }
        if (iVar3 == 1) {
          // Refresh rate
          local_10 = (undefined4)(longlong)ROUND(DAT_00d5d7b8 * *(float *)(iVar1 + 0x18));
          *(undefined4 *)(this + 0x68) = local_10; // optionValue
        }
        else if (iVar3 == 2) {
          // VSync
          *(uint *)(this + 0x68) = *(byte *)(iVar1 + 0x14) & 1;
        }
        else if (iVar3 == 3) {
          // Anti-aliasing
          local_10 = *(undefined4 *)(iVar1 + 0x40);
          goto LAB_00987c26;
        }
      }
      else if (*(int *)(this + 0x58) == 1) { // optionType == 1 (quality options)
        iVar3 = *(int *)(this + 0x54); // currentOptionIndex
        if (iVar3 == 0) {
          // Texture quality
          *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x6c); // default value
        }
        else if (iVar3 == 1) {
          // Window mode
          cVar2 = FUN_0069bc30("Window.Fullscreen",1);
          if (cVar2 == '\0') {
            *(undefined4 *)(this + 0x70) = 1; // fullscreen
            *(undefined4 *)(this + 0x68) = 1;
          }
          else {
            *(undefined4 *)(this + 0x70) = 0; // windowed
            *(undefined4 *)(this + 0x68) = 0;
          }
        }
        else {
          if (iVar3 == 2) {
            // Shadow quality
            local_10 = *(undefined4 *)(iVar1 + 0x38);
            *(undefined4 *)(this + 0x74) = local_10; // shadowQuality
          }
          else if (iVar3 == 3) {
            // Lighting quality
            local_10 = *(undefined4 *)(iVar1 + 0x44);
            *(undefined4 *)(this + 0x78) = local_10; // lightingQuality
          }
          else if (iVar3 == 4) {
            // Texture filter
            iVar3 = FUN_0069f080(); // getTextureFilterMode
            if (iVar3 == 2) {
              *(undefined4 *)(this + 0x7c) = 0; // bilinear
              local_10 = 0;
            }
            else if (iVar3 == 3) {
              *(undefined4 *)(this + 0x7c) = 1; // trilinear
              local_10 = 1;
            }
            else if (iVar3 == 4) {
              *(undefined4 *)(this + 0x7c) = 2; // anisotropic 2x
              local_10 = *(undefined4 *)(this + 0x7c);
            }
            else {
              *(undefined4 *)(this + 0x7c) = 3; // anisotropic 4x
              local_10 = *(undefined4 *)(this + 0x7c);
            }
          }
          else if (iVar3 == 5) {
            // Level of detail
            local_10 = FUN_0069f230(0,1); // getQualityOption(0)
            *(undefined4 *)(this + 0x80) = local_10; // lodQuality
          }
          else if (iVar3 == 6) {
            // Terrain quality
            local_10 = FUN_0069f230(1,1);
            *(undefined4 *)(this + 0x84) = local_10; // terrainQuality
          }
          else {
            if (iVar3 != 7) {
              if (iVar3 == 8) {
                // Edge AA
                uVar4 = FUN_0069f230(3,1);
                *(undefined4 *)(this + 0x8c) = uVar4; // edgeAAQuality
                FUN_0069bcc0("QualityOptions.EdgeAA",0);
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x8c);
              }
              else {
                if (iVar3 != 9) {
                  if (iVar3 == 10) {
                    // Motion blur
                    local_10 = FUN_0069f230(5,1);
                    *(undefined4 *)(this + 0x94) = local_10; // motionBlurQuality
                  }
                  else if (iVar3 == 0xb) {
                    // Depth of field
                    local_10 = FUN_0069f230(7,1);
                    *(undefined4 *)(this + 0x98) = local_10; // dofQuality
                  }
                  else if (iVar3 == 0xc) {
                    // Bloom
                    local_10 = FUN_0069f230(6,1);
                    *(undefined4 *)(this + 0x9c) = local_10; // bloomQuality
                  }
                  else if (iVar3 == 0xd) {
                    // SSAO
                    local_10 = FUN_0069f230(9,1);
                    *(undefined4 *)(this + 0xa0) = local_10; // ssaoQuality
                  }
                  else if (iVar3 == 0xe) {
                    // HDR
                    local_10 = FUN_0069f230(8,1);
                    *(undefined4 *)(this + 0xa4) = local_10; // hdrQuality
                  }
                  else if (iVar3 == 0xf) {
                    // Lens flare
                    local_10 = FUN_0069f230(10,1);
                    *(undefined4 *)(this + 0xa8) = local_10; // lensFlareQuality
                  }
                  else {
                    if (iVar3 != 0x10) goto LAB_00987c29;
                    // Color grading
                    local_10 = FUN_0069f230(0xb,1);
                    *(undefined4 *)(this + 0xac) = local_10; // colorGradingQuality
                  }
                  goto LAB_00987c26;
                }
                // Blur quality
                uVar4 = FUN_0069f230(4,1);
                *(undefined4 *)(this + 0x90) = uVar4; // blurQuality
                FUN_0069bcc0("QualityOptions.Blur",0);
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x90);
              }
              goto LAB_00987c29;
            }
            // Particle quality
            local_10 = FUN_0069f230(2,1);
            *(undefined4 *)(this + 0x88) = local_10; // particleQuality
          }
LAB_00987c26:
          *(undefined4 *)(this + 0x68) = local_10; // store final option value
        }
      }
LAB_00987c29:
      FUN_005a04a0("InitOptionValue",0,&DAT_00d90fa8,0); // log option initialization
      *(int *)(this + 0x54) = *(int *)(this + 0x54) + 1; // increment option index
    } while (*(uint *)(this + 0x54) < *(uint *)(this + 0x60)); // loop through all options
  }
  return;
}