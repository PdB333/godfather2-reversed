// FUNC_NAME: VehicleData::initVehiclePhysics
void __fastcall VehicleData::initVehiclePhysics(undefined4 *param_1Unknown, undefined4 *param_2Velocity, int this, undefined4 *param_4Orientation, undefined4 *param_5Unknown, undefined4 param_6Mass)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar4 = DAT_00e2b1a4;
  *(undefined4 *)(this + 0x49d00) = 0; // +0x49D00: some large offset, likely a physics state
  *(undefined2 *)(this + 0x49d04) = 0; // +0x49D04
  *(undefined2 *)(this + 0x49d06) = 0; // +0x49D06
  *(undefined2 *)(this + 0x49d08) = 0; // +0x49D08
  *(undefined2 *)(this + 0x49d0a) = 0; // +0x49D0A
  *(undefined2 *)(this + 0x49d0c) = 0; // +0x49D0C
  *(undefined4 *)(this + 0x18) = 0;     // +0x18: probably a flag or ID
  *(undefined4 *)(this + 0x60) = uVar4; // +0x60: set to default
  *(undefined4 *)(this + 100) = 0;     // +0x64
  *(undefined4 *)(this + 0x68) = 0;    // +0x68
  *(undefined4 *)(this + 0x6c) = 0;    // +0x6C
  *(undefined4 *)(this + 0x70) = 0;    // +0x70
  *(undefined4 *)(this + 0x74) = uVar4; // +0x74
  *(undefined4 *)(this + 0x78) = 0;    // +0x78
  *(undefined4 *)(this + 0x7c) = 0;    // +0x7C
  *(undefined4 *)(this + 0x80) = 0;    // +0x80
  *(undefined4 *)(this + 0x84) = 0;    // +0x84
  *(undefined4 *)(this + 0x88) = uVar4; // +0x88
  *(undefined4 *)(this + 0x8c) = 0;    // +0x8C
  *(undefined4 *)(this + 0x90) = 0;    // +0x90
  *(undefined4 *)(this + 0x94) = 0;    // +0x94
  *(undefined4 *)(this + 0x98) = 0;    // +0x98
  *(undefined4 *)(this + 0x9c) = uVar4; // +0x9C

  // Copy orientation (param_4) - probably a 4x4 matrix or quaternion
  uVar1 = param_4Orientation[1];
  uVar2 = param_4Orientation[2];
  uVar3 = param_4Orientation[3];
  *(undefined4 *)(this + 0xa0) = *param_4Orientation;   // +0xA0
  *(undefined4 *)(this + 0xa4) = uVar1;                 // +0xA4
  *(undefined4 *)(this + 0xa8) = uVar2;                 // +0xA8
  *(undefined4 *)(this + 0xac) = uVar3;                 // +0xAC

  // Copy another 4-vector (param_5)
  uVar1 = param_5Unknown[1];
  uVar2 = param_5Unknown[2];
  uVar3 = param_5Unknown[3];
  *(undefined4 *)(this + 0xb0) = *param_5Unknown;       // +0xB0
  *(undefined4 *)(this + 0xb4) = uVar1;                 // +0xB4
  *(undefined4 *)(this + 0xb8) = uVar2;                 // +0xB8
  *(undefined4 *)(this + 0xbc) = uVar3;                 // +0xBC

  // Copy velocity (param_2) - 16 floats (4x4 matrix?)
  uVar1 = param_2Velocity[1];
  uVar2 = param_2Velocity[2];
  uVar3 = param_2Velocity[3];
  *(undefined4 *)(this + 0xe0) = *param_2Velocity;      // +0xE0
  *(undefined4 *)(this + 0xe4) = uVar1;                 // +0xE4
  *(undefined4 *)(this + 0xe8) = uVar2;                 // +0xE8
  *(undefined4 *)(this + 0xec) = uVar3;                 // +0xEC

  uVar1 = param_2Velocity[5];
  uVar2 = param_2Velocity[6];
  uVar3 = param_2Velocity[7];
  *(undefined4 *)(this + 0xf0) = param_2Velocity[4];    // +0xF0
  *(undefined4 *)(this + 0xf4) = uVar1;                 // +0xF4
  *(undefined4 *)(this + 0xf8) = uVar2;                 // +0xF8
  *(undefined4 *)(this + 0xfc) = uVar3;                 // +0xFC

  uVar1 = param_2Velocity[9];
  uVar2 = param_2Velocity[10];
  uVar3 = param_2Velocity[0xb];
  *(undefined4 *)(this + 0x100) = param_2Velocity[8];   // +0x100
  *(undefined4 *)(this + 0x104) = uVar1;                // +0x104
  *(undefined4 *)(this + 0x108) = uVar2;                // +0x108
  *(undefined4 *)(this + 0x10c) = uVar3;                // +0x10C

  uVar1 = param_2Velocity[0xd];
  uVar2 = param_2Velocity[0xe];
  uVar3 = param_2Velocity[0xf];
  *(undefined4 *)(this + 0x110) = param_2Velocity[0xc]; // +0x110
  *(undefined4 *)(this + 0x114) = uVar1;                // +0x114
  *(undefined4 *)(this + 0x118) = uVar2;                // +0x118
  *(undefined4 *)(this + 0x11c) = uVar3;                // +0x11C

  // Copy param_1 (unknown, possibly another matrix)
  uVar1 = param_1Unknown[1];
  uVar2 = param_1Unknown[2];
  uVar3 = param_1Unknown[3];
  *(undefined4 *)(this + 0x120) = *param_1Unknown;      // +0x120
  *(undefined4 *)(this + 0x124) = uVar1;                // +0x124
  *(undefined4 *)(this + 0x128) = uVar2;                // +0x128
  *(undefined4 *)(this + 300) = uVar3;                  // +0x12C

  uVar1 = param_1Unknown[5];
  uVar2 = param_1Unknown[6];
  uVar3 = param_1Unknown[7];
  *(undefined4 *)(this + 0x130) = param_1Unknown[4];    // +0x130
  *(undefined4 *)(this + 0x134) = uVar1;                // +0x134
  *(undefined4 *)(this + 0x138) = uVar2;                // +0x138
  *(undefined4 *)(this + 0x13c) = uVar3;                // +0x13C

  uVar1 = param_1Unknown[9];
  uVar2 = param_1Unknown[10];
  uVar3 = param_1Unknown[0xb];
  *(undefined4 *)(this + 0x140) = param_1Unknown[8];    // +0x140
  *(undefined4 *)(this + 0x144) = uVar1;                // +0x144
  *(undefined4 *)(this + 0x148) = uVar2;                // +0x148
  *(undefined4 *)(this + 0x14c) = uVar3;                // +0x14C

  uVar1 = param_1Unknown[0xd];
  uVar2 = param_1Unknown[0xe];
  uVar3 = param_1Unknown[0xf];
  *(undefined4 *)(this + 0x150) = param_1Unknown[0xc];  // +0x150
  *(undefined4 *)(this + 0x154) = uVar1;                // +0x154
  *(undefined4 *)(this + 0x158) = uVar2;                // +0x158
  *(undefined4 *)(this + 0x15c) = uVar3;                // +0x15C

  *(undefined4 *)(this + 0x160) = uVar4; // +0x160: default
  *(undefined4 *)(this + 0x164) = 0;    // +0x164
  *(undefined4 *)(this + 0x168) = 0;    // +0x168
  *(undefined4 *)(this + 0x16c) = 0;    // +0x16C
  *(undefined4 *)(this + 0x170) = 0;    // +0x170
  *(undefined4 *)(this + 0x174) = uVar4; // +0x174
  *(undefined4 *)(this + 0x178) = 0;    // +0x178
  *(undefined4 *)(this + 0x17c) = 0;    // +0x17C
  *(undefined4 *)(this + 0x180) = 0;    // +0x180
  *(undefined4 *)(this + 0x184) = 0;    // +0x184
  *(undefined4 *)(this + 0x188) = uVar4; // +0x188
  *(undefined4 *)(this + 0x18c) = 0;    // +0x18C
  *(undefined4 *)(this + 400) = 0;      // +0x190
  *(undefined4 *)(this + 0x194) = 0;    // +0x194
  *(undefined4 *)(this + 0x198) = 0;    // +0x198
  *(undefined4 *)(this + 0x19c) = uVar4; // +0x19C
  *(undefined4 *)(this + 0x1c) = param_6Mass; // +0x1C: mass/inertia
  return;
}