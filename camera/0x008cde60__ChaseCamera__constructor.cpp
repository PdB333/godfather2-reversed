// FUNC_NAME: ChaseCamera::constructor
undefined4 * __thiscall ChaseCamera::constructor(undefined4 *this, int param_2, int param_3)
{
  float fVar1;
  float *pfVar2;
  int iVar3;
  uint uVar4;
  float fVar5;
  float fVar6;
  float afStack_50 [6];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  float fStack_14;
  
  // Call base class constructor (likely Camera or Entity)
  (**(code **)(**(int **)(param_2 + 8) + 4))();
  
  // Set vtable pointer
  *this = &PTR_FUN_00d7ca70;
  
  // Initialize member variables
  this[1] = 0;  // +0x04: some float/int
  this[2] = param_2;  // +0x08: pointer to something
  this[3] = 0;  // +0x0C: some float/int
  this[4] = 0;  // +0x10: some float/int
  this[5] = 0;  // +0x14: some float/int
  *(undefined1 *)(this + 0xc) = 1;  // +0x30: boolean flag
  
  // Call some initialization function
  FUN_0060ffd0();
  
  // Initialize local array with a global constant
  afStack_50[0] = _DAT_00d5780c;  // Some constant (likely 1.0f or similar)
  fVar5 = 0.0;
  uVar4 = 0;
  
  // Initialize more members
  this[8] = 0;   // +0x20: x component of direction/vector
  this[9] = 0;   // +0x24: y component
  this[10] = 0;  // +0x28: z component
  this[0xb] = afStack_50[0];  // +0x2C: some float
  
  fVar1 = DAT_00e445c8;  // Global scale factor
  
  // Process parameter data (likely from a data file or config)
  if (*(short *)(param_3 + 0x20) != 0) {
    do {
      pfVar2 = *(float **)(*(int *)(param_3 + 0x1c) + uVar4 * 4);
      fVar6 = pfVar2[4];  // Some identifier/type field
      
      // Check identifier values and assign accordingly
      if ((uint)fVar6 < 0xbfe9519a) {
        if (fVar6 == -1.8228027) {  // Some identifier constant
          this[10] = *pfVar2;  // +0x28: z component
        }
        else if (fVar6 == -0.0016504416) {  // Another identifier
          fVar6 = *pfVar2;
          this[4] = fVar6 * fVar1;  // +0x10: scaled value
          this[5] = fVar6 * fVar1;  // +0x14: scaled value
        }
        else if (fVar6 == -1.8228024) {  // Another identifier
          this[8] = *pfVar2;  // +0x20: x component
        }
        else if (fVar6 == -1.8228025) {  // Another identifier
          this[9] = *pfVar2;  // +0x24: y component
        }
      }
      else if (fVar6 == -8.909788e+23) {  // Another identifier
        this[3] = *pfVar2 * fVar1;  // +0x0C: scaled value
      }
      else if (fVar6 == -3.6446247e+24) {  // Another identifier
        this[1] = *pfVar2 * fVar1;  // +0x04: scaled value
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(ushort *)(param_3 + 0x20));
  }
  
  // Normalize the direction vector (this[8], this[9], this[10])
  fVar1 = (float)this[8];
  fVar6 = fVar1 * fVar1 + (float)this[9] * (float)this[9] +
          (float)this[10] * (float)this[10];
  if (DAT_00d5f2b4 < fVar6) {  // Check if squared length > some epsilon
    fVar5 = afStack_50[0] / SQRT(fVar6);  // Calculate normalization factor
  }
  this[8] = fVar1 * fVar5;   // Normalized x
  this[9] = (float)this[9] * fVar5;  // Normalized y
  this[10] = (float)this[10] * fVar5;  // Normalized z
  
  // Initialize local arrays for matrix/quaternion operations
  afStack_50[1] = 0.0;
  afStack_50[2] = 0.0;
  afStack_50[3] = 0.0;
  afStack_50[4] = 0.0;
  afStack_50[5] = afStack_50[0];
  uStack_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  fStack_28 = afStack_50[0];
  uStack_24 = 0;
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  fStack_14 = afStack_50[0];
  
  // Call matrix/quaternion functions
  FUN_0056b8a0(this[4],0,0,afStack_50);  // Some transformation function
  FUN_00610040(afStack_50);  // Another transformation function
  
  // Check if we need to initialize additional data
  iVar3 = (**(code **)(**(int **)(param_2 + 8) + 4))();
  if (iVar3 != 0) {
    FUN_00610160(this + 0x10);  // Initialize additional data at offset +0x40
  }
  
  return this;
}