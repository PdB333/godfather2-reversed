// FUNC_NAME: ParticleSystem::renderParticles
void __thiscall ParticleSystem::renderParticles(int this, int renderContext, char *particleData)
{
  int iVar1;
  uint uVar2;
  int iVar3;
  float *pfVar4;
  undefined1 *puVar5;
  uint uVar6;
  uint uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float local_64;
  undefined8 local_40;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  // Check if particle data is valid
  if (((*particleData == '\0') || (*(int *)(particleData + 4) == 0)) ||
     (*(char *)(*(int *)(particleData + 4) + 0x1e) != '\0')) {
    // Get particle buffer entry
    if (*(uint *)(renderContext + 0x16c) < 0x1000) {
      puVar5 = &DAT_011a0f28 + *(uint *)(renderContext + 0x16c) * 0x38;
    }
    else {
      puVar5 = (undefined1 *)0x0;
    }
    
    iVar3 = *(int *)(this + 0x20); // +0x20: particle system config
    uVar2 = *(uint *)(iVar3 + 0x14); // +0x14: flags
    
    // Get particle size based on flags
    if ((uVar2 & 8) == 0) {
      fVar12 = *(float *)(iVar3 + 0x30); // +0x30: base size
      fVar10 = *(float *)(particleData + 0x28); // +0x28: size X
      fVar8 = *(float *)(particleData + 0x2c); // +0x2c: size Y
    }
    else {
      fVar10 = (float)*(ushort *)(puVar5 + 2) * (DAT_00e44564 - _DAT_01218dc0);
      fVar8 = (float)*(ushort *)(puVar5 + 4) * DAT_01218dd4;
      fVar12 = DAT_00e2cd54;
    }
    
    iVar1 = *(int *)(this + 0x20);
    fVar8 = fVar8 * fVar12;
    fVar10 = fVar10 * fVar12;
    fVar12 = *(float *)(particleData + 0x20) * *(float *)(iVar1 + 0x2c) + *(float *)(particleData + 0x18);
    fVar13 = *(float *)(particleData + 0x24) * *(float *)(iVar1 + 0x2c) + *(float *)(particleData + 0x1c);
    local_64 = *(float *)(this + 0x28) * *(float *)(particleData + 0xc); // +0x28: alpha multiplier
    
    // Apply alpha modifiers
    if ((*(byte *)(iVar1 + 0x14) & 0x10) != 0) {
      local_64 = *(float *)(particleData + 0x10) * local_64;
    }
    if ((uVar2 & 0x20) != 0) {
      local_64 = *(float *)(particleData + 0x14) * local_64;
    }
    
    if (DAT_00e2af44 < local_64) {
      uVar6 = *(uint *)(iVar1 + 0x28); // +0x28: color
      fVar14 = *(float *)(iVar1 + 0x38) * *(float *)(particleData + 8) +
               *(float *)(iVar1 + 0x34) * DAT_00e445c8;
      local_40._0_4_ = (uint)(longlong)ROUND((float)*(byte *)(iVar1 + 0x2b) * local_64);
      uVar6 = (uint)local_40 | (uVar6 << 0x10 | uVar6 & 0xff00 | uVar6 >> 0x10 & 0xff) << 8;
      
      // Check if using texture or procedural rendering
      if (*(char *)(iVar1 + 0x10) == '\0') {
        // Texture-based rendering
        if (*(int *)(this + 0x24) != 0) {
          uVar7 = (uint)local_40 & 0xff;
          local_40 = CONCAT44((float)(uVar6 >> 0x10 & 0xff) * DAT_00e44640,
                              (float)(uVar6 >> 0x18) * DAT_00e44640);
          local_38 = (float)(uVar6 >> 8 & 0xff) * DAT_00e44640;
          local_34 = DAT_00e44640 * (float)uVar7;
          FUN_005071d0(&local_40, fVar12, fVar13, 0x3f800000, 0x3f800000, fVar14,
                       *(float *)(iVar1 + 0x20) * fVar10, *(float *)(iVar1 + 0x20) * fVar8,
                       *(int *)(this + 0x24), uVar2 >> 7 & 0xffffff01);
          return;
        }
      }
      else {
        // Procedural particle rendering
        uVar2 = *(uint *)(iVar1 + 0x24);
        local_40 = (longlong)ROUND(local_64 * (float)*(byte *)(iVar1 + 0x27));
        uVar2 = (uint)local_40 | (uVar2 << 0x10 | uVar2 & 0xff00 | uVar2 >> 0x10 & 0xff) << 8;
        
        // Calculate particle count
        if (*(byte *)(iVar1 + 0x11) < 4) {
          local_64 = 4.2039e-45;
        }
        else if (*(byte *)(iVar3 + 0x11) < 0x20) {
          local_64 = (float)(uint)*(byte *)(iVar3 + 0x11);
        }
        else {
          local_64 = 4.48416e-44;
        }
        
        if (*(char *)(iVar3 + 0x10) == '\x02') {
          local_64 = (float)((int)local_64 + 1U & 0xfffffffe);
        }
        
        // Setup rendering state
        FUN_00536800(); // Begin particle rendering
        _DAT_0121a2a0 = (float)(*(byte *)(this + 0x1e) & 0xf) * DAT_00e2e638;
        _DAT_0121a2a4 = (float)(*(byte *)(this + 0x1e) >> 4) * DAT_00e2e638;
        _DAT_0121a2a8 = 0;
        _DAT_0121a2ac = 0;
        local_20 = DAT_01218e44 * DAT_00e2b04c;
        local_1c = DAT_01218e48 * DAT_00e2b04c;
        local_30 = fVar12;
        local_2c = fVar13;
        local_28 = fVar10;
        local_24 = fVar8;
        
        if (*particleData != '\0') {
          iVar3 = *(int *)(particleData + 4);
          local_18 = ((float)*(byte *)(iVar3 + 0x1c) + DAT_00e2cd54) * DAT_00e445e4;
          local_14 = ((float)*(byte *)(iVar3 + 0x1d) + DAT_00e2cd54) * DAT_00e2ee80;
          if (DAT_0120575b == '\0') {
            _DAT_0121a300 = *(undefined4 *)(iVar3 + 0x24);
          }
          else {
            FUN_00536990(); // Set texture
          }
        }
        
        FUN_00536ad0(); // Set vertex format
        FUN_00536550(); // Set render state
        
        iVar3 = FUN_0060cd00(5, (int)local_64 * 2 + 2, 0, 1, 0); // Allocate vertex buffer
        fVar8 = DAT_00e44934;
        fVar10 = DAT_00e44930;
        fVar12 = DAT_00e44760;
        
        if (iVar3 != 0) {
          uVar7 = 0;
          fVar13 = DAT_00e44760 / (float)(int)local_64;
          pfVar4 = (float *)(iVar3 + 8);
          
          // Generate particle vertices
          do {
            fVar9 = fVar14;
            if ((0 < (int)uVar7) && ((int)uVar7 < (int)local_64)) {
              fVar9 = (float)(int)uVar7 * fVar13 + fVar14;
            }
            
            // Wrap angle
            if (fVar8 <= fVar9) {
              if (fVar10 < fVar9) {
                fVar9 = fVar9 - fVar12;
              }
            }
            else {
              fVar9 = fVar9 + fVar12;
            }
            
            iVar3 = *(int *)(this + 0x20);
            if (*(char *)(iVar3 + 0x10) == '\x02') {
              fVar15 = 0.0;
              if ((uVar7 & 1) != 0) goto LAB_00508309;
              fVar11 = *(float *)(iVar3 + 0x1c);
            }
            else {
              iVar3 = *(int *)(this + 0x20);
              fVar15 = *(float *)(iVar3 + 0x1c);
LAB_00508309:
              fVar11 = *(float *)(iVar3 + 0x20);
            }
            
            // Write vertex data
            pfVar4[-2] = (float)((uVar2 & 0xff0000 | uVar2 >> 0x10) >> 8 |
                                (uVar2 << 0x10 | uVar2 & 0xff00) << 8);
            pfVar4[-1] = fVar15;
            *pfVar4 = fVar9;
            pfVar4[1] = (float)((uVar6 & 0xff0000 | uVar6 >> 0x10) >> 8 |
                               (uVar6 & 0xff00 | uVar6 << 0x10) << 8);
            pfVar4[2] = fVar11;
            pfVar4[3] = fVar9;
            
            uVar7 = uVar7 + 1;
            pfVar4 = pfVar4 + 6;
          } while ((int)uVar7 <= (int)local_64);
        }
        
        FUN_0060cde0(); // Draw primitives
        FUN_00612e00(); // End rendering
        _DAT_0121a310 = 0;
        _DAT_0121a314 = 0;
        _DAT_0121a318 = 0;
      }
    }
  }
  return;
}