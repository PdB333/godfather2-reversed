// FUNC_NAME: Building::initFromData
void __thiscall Building::initFromData(Building *this, undefined4 *data)
{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  undefined1 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  // Copy building data from the data array into member fields
  *(undefined4 *)(this + 0x184) = *data;           // +0x184: buildingType or some ID
  *(undefined4 *)(this + 0x188) = data[1];         // +0x188
  *(undefined4 *)(this + 0x18c) = data[2];         // +0x18c
  *(undefined4 *)(this + 400) = data[3];           // +0x190 (400 decimal)
  *(undefined4 *)(this + 0x38) = data[5];          // +0x38: buildingIndex or ID
  *(undefined4 *)(this + 0x48) = data[6];          // +0x48
  *(undefined4 *)(this + 0x40) = data[4];          // +0x40
  *(undefined4 *)(this + 0x3c) = data[4];          // +0x3c (same as above)
  *(uint *)(this + 0x34) = *(uint *)(this + 0x34) | data[7]; // +0x34: flags bitmask
  *(undefined2 *)(this + 0x36) = 0;                // +0x36: clear some field
  *(undefined4 *)(this + 0xc4) = data[8];          // +0xc4
  *(undefined4 *)(this + 0x50) = data[9];          // +0x50
  uVar3 = data[0xc];
  uVar1 = data[0xd];
  *(undefined4 *)(this + 0x10) = data[0xb];       // +0x10: position X
  *(undefined4 *)(this + 0x14) = uVar3;            // +0x14: position Y
  *(undefined4 *)(this + 0x18) = uVar1;            // +0x18: position Z
  uVar3 = data[0xf];
  uVar1 = data[0x10];
  *(undefined4 *)(this + 0x1c) = data[0xe];       // +0x1c: rotation quaternion or euler
  *(undefined4 *)(this + 0x20) = uVar3;            // +0x20
  *(undefined4 *)(this + 0x24) = uVar1;            // +0x24
  uVar3 = data[0x12];
  uVar1 = data[0x13];
  *(undefined4 *)(this + 0x28) = data[0x11];      // +0x28: scale or additional transform
  *(undefined4 *)(this + 0x2c) = uVar3;            // +0x2c
  *(undefined4 *)(this + 0x30) = uVar1;            // +0x30
  *(undefined4 *)(this + 0x104) = data[0x14];     // +0x104
  *(undefined4 *)(this + 0x108) = data[0x15];     // +0x108
  
  // Call some functions on data elements (likely string or resource references)
  FUN_004d3d90(data[0x16]);  // Possibly addRef or register
  FUN_004d3d90(data[0x17]);
  FUN_004d3d90(data[0x18]);
  FUN_004d3d90(data[0x19]);
  FUN_004d3d90(data[0x1a]);
  FUN_004d3d90(data[0x1b]);
  
  local_10 = (undefined1 *)0x0;
  local_c = 0;
  local_8 = 0;
  local_4 = (code *)0x0;
  
  // Format building name string: "building_name_%03u" using buildingIndex
  FUN_004d4ad0(&local_10, "building_name_%03u", *(undefined4 *)(this + 0x38));
  puVar2 = local_10;
  if (local_10 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e;  // Empty string fallback
  }
  uVar3 = FUN_004dafd0(puVar2);  // Likely hash or register string
  *(undefined4 *)(this + 0xdc) = uVar3;  // +0xdc: name hash or pointer
  
  if (local_10 != (undefined1 *)0x0) {
    (*local_4)(local_10);  // Free temporary string
  }
  return;
}