// FUNC_NAME: Player::createDamageEffect
undefined4 * Player::createDamageEffect(int this, float damageAmount, undefined4 damageType)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 unaff_EDI;
  undefined4 local_50 [5];
  undefined4 local_3c;
  undefined4 local_28;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  TlsGetValue(DAT_01139810);
  iVar2 = FUN_00aa2680(0x20,0x27); // Allocate 0x20 bytes for damage effect data
  *(undefined2 *)(iVar2 + 4) = 0x20;
  uVar3 = FUN_00a64b00(param_2); // Convert damage amount to some format
  fVar1 = *(float *)(param_1 + 0x84); // Get player's health +0x84
  FUN_0045cbe0(); // Get current time
  local_50[0] = DAT_00e2b1a4; // Default color/effect values
  local_3c = DAT_00e2b1a4;
  local_28 = DAT_00e2b1a4;
  local_20 = 0;
  local_18 = 0;
  local_14 = 0;
  local_1c = fVar1 * param_2; // Scale effect by health * damage
  TlsGetValue(DAT_01139810);
  iVar2 = FUN_00aa2680(0x70,0x27); // Allocate 0x70 bytes for effect parameters
  *(undefined2 *)(iVar2 + 4) = 0x70;
  uVar3 = FUN_00a6be50(uVar3,local_50); // Create effect with parameters
  TlsGetValue(DAT_01139810);
  puVar4 = (undefined4 *)FUN_00aa2680(0x170,0x31); // Allocate 0x170 bytes for damage effect object
  *(undefined2 *)(puVar4 + 1) = 0x170;
  FUN_009f0c70(uVar3,&DAT_011397d0,param_3); // Initialize effect with damage type
  *puVar4 = &PTR_FUN_00e39ec0; // Set vtable
  puVar4[0x58] = unaff_EDI; // Store some identifier
  puVar4[0x59] = param_1; // Store player pointer
  FUN_0043b490(); // Register effect
  FUN_009f01f0(0x2001,unaff_EDI,0); // Send network event
  return puVar4;
}