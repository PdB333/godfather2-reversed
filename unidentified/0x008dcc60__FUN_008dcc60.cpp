// FUNC_NAME: SomeClass::spawnExplosionEffect
void __fastcall spawnExplosionEffect(int this)
{
  float *pfVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  float *pfVar5;
  float fVar6;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50 [12];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  // Check if explosion effect already exists at +0x1BC
  if (*(int *)(this + 0x1bc) == 0) {
    // Get some float array (likely a matrix or transform)
    pfVar1 = (float *)FUN_00471610();
    pfVar5 = local_50;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar5 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar5 = pfVar5 + 1;
    }
    
    // Initialize local variables with global data
    local_90 = _DAT_00d5780c;
    local_7c = _DAT_00d5780c;
    local_68 = _DAT_00d5780c;
    local_60 = local_20;
    local_5c = local_1c;
    local_8c = 0;
    local_88 = 0;
    local_84 = 0;
    local_80 = 0;
    local_78 = 0;
    local_74 = 0;
    local_70 = 0;
    local_6c = 0;
    local_64 = 0;
    local_58 = local_18;
    local_54 = 0;
    
    // Thread-local storage access
    TlsGetValue(DAT_01139810);
    
    // Allocate memory for some structure (0x20 bytes, type 0x27)
    iVar4 = FUN_00aa2680(0x20, 0x27);
    
    // Calculate explosion radius based on vector magnitude
    fVar6 = SQRT(local_50[2] * local_50[2] + local_50[1] * local_50[1] + local_50[0] * local_50[0])
            * _DAT_00d5c458;
    
    // Set size field at offset +4
    *(undefined2 *)(iVar4 + 4) = 0x20;
    
    // Create some resource/object with the calculated size
    puVar2 = (undefined4 *)FUN_00a64b00(fVar6);
    
    // Another allocation (0x160 bytes, type 0x31)
    TlsGetValue(DAT_01139810);
    iVar4 = FUN_00aa2680(0x160, 0x31);
    *(undefined2 *)(iVar4 + 4) = 0x160;
    
    // Create the actual explosion effect
    uVar3 = FUN_0043b490();
    uVar3 = FUN_00540c60(10, 0x1f, uVar3);
    uVar3 = FUN_009f0c70(puVar2, &local_90, uVar3);
    
    // Store the effect handle at +0x1BC
    *(undefined4 *)(this + 0x1bc) = uVar3;
    
    // Register for updates
    FUN_0043b490();
    FUN_009f01f0(0x2001, this, 0);
    
    // Decrement reference count and possibly delete
    if ((*(short *)(puVar2 + 1) != 0) &&
       (*(short *)((int)puVar2 + 6) = *(short *)((int)puVar2 + 6) + -1,
       *(short *)((int)puVar2 + 6) == 0)) {
      (**(code **)*puVar2)(1);
    }
  }
  return;
}