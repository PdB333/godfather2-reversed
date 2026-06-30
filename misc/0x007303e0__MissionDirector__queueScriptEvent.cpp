// FUNC_NAME: MissionDirector::queueScriptEvent
void __thiscall MissionDirector::queueScriptEvent(int *this, int *entity, int *contextObject)
{
  bool bLocalAllocated;
  bool bIsStoryMode;
  char cVar;
  int *piVar;
  int iVar;
  int *piTarget;
  int *localTarget;
  uint uiHashResult;
  int iLocalId1;
  int iLocalId2;
  int iLocalId3;
  undefined4 uStack_60;
  undefined ***pppScriptNode;
  undefined1 uStack_58;
  undefined4 uStack_54;
  undefined ***pppScriptNode2;
  undefined1 uStack_4c;
  undefined **ppScriptList;
  int iStack_44;
  int *piStack_40;
  int iStack_3c;
  undefined8 uTimestampHi;
  undefined4 uTimestampLo;
  undefined1 uStack_2c;
  undefined4 uStack_28;
  undefined **ppScriptList2;
  undefined4 uStack_20;
  int aiStack_1c [2];
  undefined8 uTimestampHi2;
  undefined4 uTimestampLo2;
  undefined1 uStack_8;
  undefined4 uStack_4;
  
  bLocalAllocated = false;
  localTarget = this;
  if (contextObject == (int *)0x0) {
    cVar = FUN_007f7c50();  // IsInGameMode?
    if (cVar == '\0') {
      cVar = (**(code **)(*entity + 0x1f8))();  // entity->isPlayerControlled?
      if ((((cVar != '\0') || (((uint)entity[0x23a] >> 0x11 & 1) != 0)) && (entity[0x71e] != 0))
         && (piVar = (int *)(entity[0x71e] + -0x48), piVar != (int *)0x0)) {
        uiHashResult = 0;
        cVar = (**(code **)(*piVar + 0x10))(0x55859efa,&uiHashResult);  // hash: "isActive"
        contextObject = (int *)(-(uint)(cVar != '\0') & uiHashResult);
      }
    }
    else {
      contextObject = (int *)FUN_007fd780();  // GetActiveDirector()
      bLocalAllocated = true;
    }
  }
  piTarget = (int *)(**(code **)(*this + 0x230))();  // this->getTargetEntity()
  if (piTarget != entity) {
    bIsStoryMode = false;
    iVar = FUN_00806440();  // GetGameMode()
    piTarget = entity;
    if (iVar == 3) {
      bIsStoryMode = true;
      if (contextObject == (int *)0x0) {
        return;
      }
      iLocalId3 = this[0x7b5];           // +0x1ED4? current event ID
      iVar = 0x637b907;                   // hash constant
      iLocalId1 = 0x637b907;
      iLocalId2 = 0;
      cVar = (**(code **)(*contextObject + 0x10))(0x369ac561,&iLocalId2); // hash: "hasComponent"
      if ((cVar != '\0') && (this != (int *)0x0)) {
        uiHashResult = this[0x84e];       // +0x2138? component ID
      }
      localTarget = (int *)0x0;
      cVar = (**(code **)(*entity + 0x10))(0x369ac561,&localTarget); // entity->hasComponent?
      if ((cVar != '\0') && (iLocalId2 != 0)) {
        iVar = *(int *)(iLocalId2 + 0x2138);  // component->getID?
      }
      if (iLocalId1 == iLocalId3) {
        if (iVar == iLocalId3) {
          piTarget = contextObject;
        }
      }
      else {
        piTarget = contextObject;
        if (iVar != iLocalId3) {
          return;   // ID mismatch, abort
        }
      }
    }
    else {
      cVar = FUN_007f7c50();
      if (cVar != '\0') {
        piTarget = (int *)FUN_007fd740();  // GetPlayerCamera()
      }
      if (piTarget == (int *)0x0) {
        return;
      }
    }
    // Build script event node
    uStack_30 = 0;
    uStack_38 = 0;
    ppScriptList = &PTR_FUN_00d5dbbc;   // vtable for ScriptEventNode
    iStack_44 = 0xffffffff;             // default event ID
    piStack_40 = (int *)0x0;
    iStack_3c = 0;
    uStack_2c = 0;
    uStack_28 = DAT_01205228;           // some GUID constant
    if ((bLocalAllocated) && (cVar = (**(code **)(*entity + 0x1f8))(), cVar == '\0')) {
      iStack_44 = -0x5d8bead7;          // hash for "playerControlled"?
    }
    else {
      iStack_44 = (-(uint)(((uint)entity[0x238] >> 0xd & 1) != 0) & 0xe6a08184) + 0x4937909e;
      // event type based on entity flags
    }
    if (piTarget == (int *)0x0) {
      piVar = (int *)0x0;
    }
    else {
      piVar = piTarget + 0x12;         // offset to list member?
    }
    if (piStack_40 != piVar) {
      if (piStack_40 != (int *)0x0) {
        FUN_004daf90(&piStack_40);      // release old list node
      }
      piStack_40 = piVar;
      if (piVar != (int *)0x0) {
        iStack_3c = piVar[1];           // save next pointer?
        piVar[1] = (int)&piStack_40;    // link
      }
    }
    iVar = FUN_00471610();              // GetTickCount()
    uStack_2c = 1;                      // valid flag
    uStack_38 = *(undefined8 *)(iVar + 0x30);  // timestamp
    uStack_30 = *(undefined4 *)(iVar + 0x38);
    piVar = localTarget + 0xf;
    pppScriptNode = &ppScriptList;
    uStack_60 = DAT_0112ad8c;           // script GUID
    uStack_58 = 0;
    FUN_00408bf0(&uStack_60,piVar,0);   // enqueueScriptEvent
    if (bIsStoryMode) {
      uStack_c = 0;
      uStack_14 = 0;
      ppScriptList2 = &PTR_FUN_00d5dbbc;
      aiStack_1c[0] = 0;
      aiStack_1c[1] = 0;
      uStack_8 = 0;
      uStack_4 = DAT_01205228;
      uStack_20 = 0xac5762b9;           // another hash
      FUN_0044b210(piTarget);           // process event?
      iVar = FUN_00471610();
      uStack_8 = 1;
      uStack_14 = *(undefined8 *)(iVar + 0x30);
      uStack_c = *(undefined4 *)(iVar + 0x38);
      pppScriptNode2 = &ppScriptList2;
      uStack_54 = DAT_0112ad8c;
      uStack_4c = 0;
      FUN_00408bf0(&uStack_54,piVar,0);
      if (aiStack_1c[0] != 0) {
        FUN_004daf90(aiStack_1c);
      }
    }
    if (piStack_40 != (int *)0x0) {
      FUN_004daf90(&piStack_40);
    }
  }
  return;
}