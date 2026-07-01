// FUNC_NAME: ParticleSystem::spawnExplosionParticles
void __fastcall ParticleSystem::spawnExplosionParticles(int this)
{
  float fVar1;
  undefined *puVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  // Get particle template data - either from assigned template or default
  if ((*(int *)(this + 0x1bc4) == 0) ||
     (puVar2 = *(undefined **)(*(int *)(this + 0x1bc4) + 0x38), puVar2 == (undefined *)0x0)) {
    puVar2 = &DAT_00e53b50; // Default particle template
  }
  
  // Get min/max particle lifetime range
  fVar1 = *(float *)(puVar2 + 0xcc); // +0xCC: minLifetime
  fVar6 = *(float *)(puVar2 + 0xd0); // +0xD0: maxLifetime
  if (fVar6 < fVar1) {
    fVar6 = fVar1 + _DAT_00d5780c; // Clamp if max < min
  }
  
  // Get velocity and spread multipliers
  fVar10 = *(float *)(puVar2 + 200) * DAT_00d7007c; // +0xC8: velocityMultiplier
  fVar11 = *(float *)(puVar2 + 0xc4) * DAT_00d7007c; // +0xC4: spreadMultiplier
  
  pfVar4 = (float *)(this + 0x1c10); // +0x1C10: particleData array (8 particles, 3 floats each)
  iVar5 = 8; // Spawn 8 particles
  
  do {
    // Random lifetime within range
    iVar3 = _rand();
    fVar7 = (float)iVar3 * DAT_00e44590 * (fVar6 - fVar1) + fVar1;
    
    // Random horizontal spread
    iVar3 = _rand();
    fVar8 = ((float)iVar3 - _DAT_00d71c40) * _DAT_00d71c3c; // Random in [-1, 1]
    
    // Random vertical spread with lifetime influence
    iVar3 = _rand();
    fVar9 = ((float)iVar3 - _DAT_00d71c40) * _DAT_00d71c3c * fVar7 * fVar11 + DAT_00d5f52c;
    
    // Store particle data: velocityX, velocityY, lifetime
    pfVar4[-1] = fVar8 * fVar7 * fVar10; // velocityX
    *pfVar4 = fVar9;                     // velocityY
    pfVar4[1] = fVar7;                   // lifetime
    
    pfVar4 = pfVar4 + 3;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  
  // Copy explosion position from some global
  iVar5 = FUN_00471610(); // Get explosion origin
  *(undefined8 *)(this + 0x1c6c) = *(undefined8 *)(iVar5 + 0x20); // +0x1C6C: positionX, positionY
  *(undefined4 *)(this + 0x1c74) = *(undefined4 *)(iVar5 + 0x28); // +0x1C74: positionZ
  
  return;
}