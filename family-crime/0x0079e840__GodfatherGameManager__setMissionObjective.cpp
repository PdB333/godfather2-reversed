// FUNC_NAME: GodfatherGameManager::setMissionObjective
void __thiscall GodfatherGameManager::setMissionObjective(int this, undefined4 objectiveId, undefined4 *position, undefined4 radius, undefined4 *rotation)
{
  undefined4 uVar1;
  char cVar2;
  
  cVar2 = FUN_00481620(); // likely isMissionActive() or similar check
  uVar1 = _DAT_00d5780c; // some global constant or current value
  if (cVar2 != '\0') {
    *(undefined4 *)(this + 0xda0) = objectiveId; // +0xda0: currentObjectiveId
    *(undefined4 *)(this + 0xd90) = *position;    // +0xd90: objectivePosition.x
    *(undefined4 *)(this + 0xd94) = position[1];  // +0xd94: objectivePosition.y
    *(undefined4 *)(this + 0xd98) = position[2];  // +0xd98: objectivePosition.z
    *(undefined4 *)(this + 0xd9c) = uVar1;        // +0xd9c: objectiveRadius or some flag
    *(undefined4 *)(this + 0xd84) = radius;       // +0xd84: objectiveRadius
    if (rotation != (undefined4 *)0x0) {
      *(undefined4 *)(this + 0xd80) = *rotation;      // +0xd80: objectiveRotation.x
      *(undefined4 *)(this + 0xd84) = rotation[1];    // +0xd84: objectiveRotation.y (overwrites radius!)
      *(undefined4 *)(this + 0xd88) = rotation[2];    // +0xd88: objectiveRotation.z
      *(undefined4 *)(this + 0xd8c) = rotation[3];    // +0xd8c: objectiveRotation.w
    }
    FUN_006d9da0(); // likely updateObjectiveUI() or notifyObjectiveChanged()
    FUN_00424ea0(*(undefined4 *)(this + 0x564), this + 0xd60, 0); // likely sendObjectiveToScript(scriptContext, objectiveData, 0)
  }
  return;
}