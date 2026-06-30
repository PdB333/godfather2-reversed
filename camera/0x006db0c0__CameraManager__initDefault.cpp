// FUNC_NAME: CameraManager::initDefault
undefined4 * __thiscall CameraManager::initDefault(CameraManager *this, CameraNode *cameraNode)
{
  int *listHead;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  // Load constants from global data (likely default camera settings)
  uVar5 = DAT_00e446dc;             // +0x?? default quaternion/angle component
  uVar4 = DAT_00d5efd0;             // +0x??
  uVar3 = DAT_00d5e288;             // +0x??
  uVar2 = _DAT_00d5780c;            // +0x?? (zero vector?)
  
  // Initialize basic fields
  this->field_04 = 0;                // +0x04
  *(byte *)(this + 0x08) = 0;       // +0x08 (byte, likely disabled)
  this->field_0C = 0xff;            // +0x0C (likely alpha or flag)
  this->vtable = &PTR_FUN_00d5f630; // +0x00 vtable
  
  // Initialize first camera state group (offsets 0x50-0x68)
  this->camState1_0x18 = uVar2;      // +0x18
  this->camState1_0x1B = uVar2;      // +0x1B (actually 0x6C)
  this->camState1_0x1C = uVar2;      // +0x1C (0x70)
  this->camState1_0x14 = uVar3;      // +0x14
  this->camState1_0x15 = uVar4;      // +0x15
  this->camState1_0x16 = uVar3;      // +0x16
  this->camState1_0x17 = uVar4;      // +0x17
  this->camState1_0x19 = uVar3;      // +0x19
  this->camState1_0x1A = uVar5;      // +0x1A
  
  // Initialize camera color/effect fields
  this->cameraColor1 = DAT_00d5f5f0;   // +0x10
  this->cameraColor2 = DAT_00d5f5f4;   // +0x14
  
  // Initialize second camera state group (offsets 0xC4-0xDC)
  this->camState2_0x31 = uVar2;      // +0x31 (0xC4)
  this->camState2_0x34 = uVar2;      // +0x34 (0xD0)
  this->camState2_0x35 = uVar2;      // +0x35 (0xD4)
  this->camState2_0x2D = uVar3;      // +0x2D
  this->camState2_0x2E = uVar4;      // +0x2E
  this->camState2_0x2F = uVar3;      // +0x2F
  this->camState2_0x30 = uVar4;      // +0x30
  this->camState2_0x32 = uVar3;      // +0x32
  this->camState2_0x33 = uVar5;      // +0x33
  
  // Second camera color duplicate
  this->cameraColor1_dup = DAT_00d5f5f0; // +0x1D (0x74)
  this->cameraColor2_dup = DAT_00d5f5f4; // +0x1E (0x78)
  
  // Zero out linked list node area (offsets 0xE0-0x160 approximately)
  this->listHead = 0;               // +0x38 (head of camera node list)
  this->listTail = 0;               // +0x39 (tail)
  this->listCount = 0;              // +0x3A
  this->listNext = 0;               // +0x3B
  this->unused1 = 0;                // +0x3C
  *(byte *)(this + 0x100) = 0;      // +0x40 (byte)
  this->vec3_A = uVar3;             // +0x41
  this->vec3_B = uVar4;             // +0x42
  // Zero out four ints (maybe for four camera states)
  this->stateFlagsA[0] = 0;         // +0x44
  this->stateFlagsA[1] = 0;         // +0x45
  this->stateFlagsA[2] = 0;         // +0x46
  this->stateFlagsA[3] = 0;         // +0x47
  // Another set of four zeros
  this->stateFlagsB[0] = 0;         // +0x48
  this->stateFlagsB[1] = 0;         // +0x49
  this->stateFlagsB[2] = 0;         // +0x4A
  this->stateFlagsB[3] = 0;         // +0x4B
  *(byte *)(this + 0x130) = 0;      // +0x4C (byte)
  this->vec3_C = uVar3;             // +0x4D
  this->vec3_D = uVar4;             // +0x4E
  // Yet another set of four zeros
  this->stateFlagsC[0] = 0;         // +0x50
  this->stateFlagsC[1] = 0;         // +0x51
  this->stateFlagsC[2] = 0;         // +0x52
  this->stateFlagsC[3] = 0;         // +0x53
  this->stateFlagsD[0] = 0;         // +0x54
  this->stateFlagsD[1] = 0;         // +0x55
  this->stateFlagsD[2] = 0;         // +0x56
  this->stateFlagsD[3] = 0;         // +0x57
  *(byte *)(this + 0x160) = 0;      // +0x58 (byte)
  this->vec3_E = uVar3;             // +0x59
  this->vec3_F = uVar4;             // +0x5A
  // Fourth set of zeros
  this->stateFlagsE[0] = 0;         // +0x5C
  this->stateFlagsE[1] = 0;         // +0x5D
  this->stateFlagsE[2] = 0;         // +0x5E
  this->stateFlagsE[3] = 0;         // +0x5F
  this->stateFlagsF[0] = 0;         // +0x60
  this->stateFlagsF[1] = 0;         // +0x61
  this->stateFlagsF[2] = 0;         // +0x62
  this->stateFlagsF[3] = 0;         // +0x63
  *(byte *)(this + 0x1A0) = 1;      // +0x68 (byte set to 1)
  
  // Handle optional camera node insertion into linked list
  listHead = &this->listHead;       // offset 0x38
  if (cameraNode == 0) {
    cameraNode = 0;
  } else {
    cameraNode = (CameraNode *)((int)cameraNode + 0x48); // offset to node inside camera object
  }
  if (*listHead != (int)cameraNode) {
    if (*listHead != 0) {
      FUN_004daf90(listHead);       // free old link?
    }
    *listHead = (int)cameraNode;
    if (cameraNode != 0) {
      this->listTail = *(int *)((int)cameraNode + 4);
      *(int **)((int)cameraNode + 4) = listHead; // link to previous head
      return this;
    }
  }
  return this;
}