// FUNC_NAME: Vehicle::createWheeledVehicle
undefined4 * FUN_0054e170(int param_1, undefined4 param_2, float param_3, undefined4 param_4, undefined4 param_5)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 unaff_EDI;
  undefined4 local_70;
  float local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_5c;
  undefined4 local_50[5];
  undefined4 local_3c;
  undefined4 local_28;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;

  local_70 = param_2;
  local_6c = param_3;
  local_68 = param_4;
  local_64 = DAT_00e2b1a4; // Likely a vector constant (0,0,0)
  TlsGetValue(DAT_01139810); // Get thread local storage
  iVar1 = FUN_00aa2680(0x30, 0x27); // Allocate 0x30 bytes (0x27 = memory tag for physics)
  uVar2 = _DAT_00ef3a9c; // Some global physics data
  *(undefined2 *)(iVar1 + 4) = 0x30; // Set allocation size
  uVar2 = FUN_00a66df0(&local_70, uVar2); // Create rigid body? Takes vector and returns something
  local_5c = *(float *)(param_1 + 0x84) * param_3 + _DAT_01126040; // Calculate scale factor from some parameter + offset
  FUN_0045cbe0(); // Unknown function, possibly debug related
  local_50[0] = DAT_00e2b1a4; // Zero vector for position
  local_3c = DAT_00e2b1a4;   // Zero vector for rotation
  local_28 = DAT_00e2b1a4;   // Zero vector for scale?
  local_20 = 0;              // Padding
  local_1c = local_5c;       // Scale factor
  local_18 = 0;              // Padding
  local_14 = 0;              // Padding
  TlsGetValue(DAT_01139810);
  iVar1 = FUN_00aa2680(0x70, 0x27); // Allocate 0x70 bytes for vehicle data
  *(undefined2 *)(iVar1 + 4) = 0x70;
  uVar2 = FUN_00a6be50(uVar2, local_50); // Create vehicle physics object from rigid body + transform
  TlsGetValue(DAT_01139810);
  puVar3 = (undefined4 *)FUN_00aa2680(0x170, 0x31); // Allocate 0x170 bytes for vehicle object (0x31 = memory tag)
  *(undefined2 *)(puVar3 + 1) = 0x170; // Set allocation size at offset 4
  FUN_009f0c70(uVar2, &DAT_011397d0, param_5); // Initialize vehicle with physics object, some data, and audio?
  *puVar3 = &PTR_FUN_00e39ec0; // Setup vtable pointer
  puVar3[0x58] = unaff_EDI;     // +0x160: Store some parameter
  puVar3[0x59] = param_1;      // +0x164: Store the parent object reference
  FUN_0043b490(); // Unknown function
  FUN_009f01f0(0x2001, unaff_EDI, 0); // Send creation message/event (0x2001 = create event?)
  return puVar3;
}