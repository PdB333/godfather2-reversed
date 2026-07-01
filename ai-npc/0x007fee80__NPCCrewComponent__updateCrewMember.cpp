// FUNC_NAME: NPCCrewComponent::updateCrewMember
void __fastcall NPCCrewComponent::updateCrewMember(int *this)
{
  bool isAlive;
  int *crewMemberPtr; // piVar6
  int crewMemberHandle; // iVar5
  int someGlobal; // iVar5
  undefined8 transformData; // uVar1
  code *vfunc; // pcVar2
  undefined4 transformDataHigh; // uStack_4
  float10 timeValue; // fVar7

  // Check if the NPC is alive via vtable function at +0x2d8
  isAlive = (**(code **)(*this + 0x2d8))();
  if (!isAlive) {
    crewMemberPtr = this + 0x7a2; // +0x1E88 offset for crew member handle
    if ((this[0x7a2] != 0) && (FUN_005f72f0(this[0x7a2]), *crewMemberPtr != 0)) {
      FUN_004daf90(crewMemberPtr); // Release crew member
      *crewMemberPtr = 0;
      return;
    }
  } else {
    crewMemberPtr = this + 0x7a2;
    if (this[0x7a2] == 0) {
      // Create new crew member handle
      undefined4 handle = (**(code **)(*this + 0x1e0))(); // Get some resource handle
      crewMemberHandle = FUN_005f7290(handle); // Convert to crew member
      if (*crewMemberPtr != crewMemberHandle) {
        if (*crewMemberPtr != 0) {
          FUN_004daf90(crewMemberPtr); // Release old
        }
        *crewMemberPtr = crewMemberHandle;
        if (crewMemberHandle != 0) {
          this[0x7a3] = *(int *)(crewMemberHandle + 4); // +0x7A3 = linked list prev
          *(int **)(crewMemberHandle + 4) = crewMemberPtr; // Link back
        }
      }
      if (*crewMemberPtr != 0) {
        FUN_005f7250(*crewMemberPtr); // Initialize crew member
        FUN_007fa770(this); // Update crew component
      }
      if (*crewMemberPtr == 0) {
        return;
      }
    }
    // Update transform data
    someGlobal = FUN_00471610(); // Get some global transform source
    transformData = *(undefined8 *)(someGlobal + 0x30); // +0x30 = transform low
    vfunc = *(code **)(*this + 0x4c); // vtable +0x4c = getTransform
    transformDataHigh = *(undefined4 *)(someGlobal + 0x38); // +0x38 = transform high
    crewMemberHandle = *crewMemberPtr;
    // Store transform data into crew member at offsets 0x10, 0x14, 0xc
    *(undefined4 *)(crewMemberHandle + 0x10) = (undefined4)transformData;
    *(undefined4 *)(crewMemberHandle + 0x14) = transformDataHigh;
    *(undefined4 *)(crewMemberHandle + 0xc) = (undefined4)((ulonglong)transformData >> 0x20);
    // Call getTransform
    (*vfunc)(&transformData);
    crewMemberHandle = *crewMemberPtr;
    vfunc = *(code **)(*this + 0x2c4); // vtable +0x2c4 = getTime
    // Store additional data at offsets 0x1c, 0x20
    *(undefined4 *)(crewMemberHandle + 0x1c) = unaff_ESI;
    *(undefined4 *)(crewMemberHandle + 0x20) = transformData._4_4_;
    timeValue = (float10)(*vfunc)();
    *(float *)(crewMemberHandle + 0x18) = (float)timeValue; // Store time at +0x18
  }
  return;
}