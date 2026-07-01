// FUNC_NAME: GodfatherGameManager::setMissionTargets
void __thiscall GodfatherGameManager::setMissionTargets(int this, undefined8 param_1, undefined8 param_2, undefined8 param_3)
{
  // +0x9c: missionTarget1
  // +0xa4: missionTarget2
  // +0xac: missionTarget3
  *(undefined8 *)(this + 0x9c) = param_1;
  *(undefined8 *)(this + 0xa4) = param_2;
  *(undefined8 *)(this + 0xac) = param_3;
  return;
}