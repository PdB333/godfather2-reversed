// FUNC_NAME: SimPlayer::initVehicleChoice
undefined4 * __thiscall FUN_00999d40(undefined4 *this, undefined4 vehicleId, int vehicleData, undefined4 param_4)
{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 vehicleTransform[16]; // 0x40 bytes (4x4 matrix)
  undefined1 someBuffer[76]; // likely a string or small struct
  
  this[1] = vehicleId;
  this[2] = vehicleData;
  *this = &PTR_FUN_00d923a8; // vtable
  uVar1 = FUN_0042b400(); // malloc/new
  this[4] = uVar1;
  uVar1 = FUN_0042b400(); // malloc/new
  this[5] = uVar1;
  
  // Get vehicle transform matrix from the vehicle data (likely a Havok transform)
  puVar2 = (undefined4 *)(**(code **)(**(int **)(vehicleData + 8) + 4))();
  vehicleTransform[0] = *puVar2;
  vehicleTransform[1] = puVar2[1];
  vehicleTransform[2] = puVar2[2];
  vehicleTransform[3] = puVar2[3];
  vehicleTransform[4] = puVar2[4];
  vehicleTransform[5] = puVar2[5];
  vehicleTransform[6] = puVar2[6];
  vehicleTransform[7] = puVar2[7];
  vehicleTransform[8] = puVar2[8];
  vehicleTransform[9] = puVar2[9];
  vehicleTransform[10] = puVar2[10];
  vehicleTransform[11] = puVar2[11];
  vehicleTransform[12] = puVar2[12];
  vehicleTransform[13] = puVar2[13];
  vehicleTransform[14] = puVar2[14];
  vehicleTransform[15] = puVar2[15];
  
  // Check if we have a game type that requires specific vehicle setup
  iVar3 = FUN_004a3790(0xd550688c);
  if (iVar3 != 0) {
    FUN_004a36a0(someBuffer);
    FUN_00999b80(vehicleTransform); // likely process vehicle transform
  }
  
  uVar1 = FUN_009d2e50(param_4, vehicleTransform); // likely create vehicle entity from transform
  this[3] = uVar1;
  
  // Check for special vehicle types (e.g., police, taxi) and update reference data
  puVar2 = (undefined4 *)FUN_004a3790(0xb6495298);
  if ((puVar2 == (undefined4 *)0x0) || (puVar2[5] != 2)) {
    puVar2 = (undefined4 *)FUN_004a3790(0x136decc4);
    if ((puVar2 == (undefined4 *)0x0) || (puVar2[5] != 2)) goto LAB_00999e2c;
    uVar1 = thunk_FUN_0042a990(*puVar2); // get vehicle data
  }
  else {
    uVar1 = *puVar2; // get vehicle ID
  }
  this[5] = uVar1;
  this[4] = uVar1;
  
LAB_00999e2c:
  if (this[3] != 0) {
    FUN_009d3070(this[5]); // initialize vehicle entity
  }
  return this;
}