// FUNC_NAME: Creature::updateCreature
void __fastcall Creature::updateCreature(int *thisPtr)
{
  int creatureModel;
  char isActive;
  undefined4 localStack[4];
  
  creatureModel = thisPtr[0xba]; // +0x2e8 - pointer to creature model instance
  isActive = (**(code **)(*thisPtr + 0x19c))(); // virtual call - isCreatureActive?
  if (isActive != '\0') {
    FUN_0055dbd0(); // likely some cleanup or deactivation function
    return;
  }
  if (creatureModel != 0) {
    localStack[0] = 0;
    localStack[1] = 0;
    localStack[2] = 0;
    localStack[3] = DAT_00e2b1a4; // some global constant, possibly identity quaternion or zero vector
    FUN_009f2000(); // push matrix/transform stack
    (**(code **)(*(int *)(creatureModel + 0xd0) + 0x40))(&localStack); // model->getLocalTransform() - extracts local transform
    FUN_009f2000(); // pop matrix/transform stack
    (**(code **)(*(int *)(creatureModel + 0xd0) + 0x44))(localStack); // model->setLocalTransform() - applies modified transform
  }
  return;
}