// FUNC_NAME: PlayerActionableInfo::reset
void PlayerActionableInfo::reset(void)
{
  // +0x00: activeAction (int) - set to 0
  // +0x04: actionType (byte) - set to 0
  // +0x05: actionSubType (byte) - set to 0
  // +0x5C: targetEntity (int) - set to 0
  // +0x60: targetObject (int) - set to 0
  // +0x64: targetId (int) - set to 0xFFFFFFFF (-1)
  // +0x0C: actionFlags (int) - set to 0
  // +0x10: actionParam (int) - set to 0
  // +0x08: actionPriority (int) - set to 1
  // +0x14: actionTimer (int) - set to DAT_00e2b04c (some global timer value)
  // +0x3C: actionCooldown (int) - set to 0
  // +0x28: actionState (byte) - set to 0
  // +0x2C: actionDuration (int) - set to DAT_00e2b1a4 (some global duration value)
  // +0x34: actionStartTime (int) - set to DAT_00e2b050 (some global start time)
  // +0x38: actionEndTime (int) - set to 0
  // +0x40: actionRange (int) - set to 0
  // +0x44: actionAngle (int) - set to 0
  // +0x48: actionSpeed (int) - set to DAT_00e2b1a4
  // +0x4C: actionAcceleration (int) - set to DAT_00e2b1a4
  // +0x50: actionDeceleration (int) - set to DAT_00e2b1a4
  // +0x54: actionMaxSpeed (int) - set to 100
  // +0x58: actionMinSpeed (int) - set to 0
  // +0x68: actionUserData (int) - set to 0
  // +0x6C: actionUserData2 (int) - set to 0

  this->activeAction = 0;
  *(byte *)&this->actionType = 0;
  *(byte *)((int)&this->actionType + 1) = 0; // actionSubType
  this->targetEntity = 0;
  this->targetObject = 0;
  this->targetId = 0xFFFFFFFF;
  this->actionFlags = 0;
  this->actionParam = 0;
  this->actionPriority = 1;
  *(byte *)((int)&this->actionType + 1) = 0; // actionSubType (redundant)
  this->actionTimer = DAT_00e2b04c;
  this->actionCooldown = 0;
  *(byte *)((int)this + 0x29) = 0; // actionState
  this->actionDuration = DAT_00e2b1a4;
  this->actionStartTime = DAT_00e2b050;
  this->actionEndTime = 0;
  this->actionRange = 0;
  this->actionAngle = 0;
  this->actionSpeed = DAT_00e2b1a4;
  this->actionAcceleration = DAT_00e2b1a4;
  this->actionDeceleration = DAT_00e2b1a4;
  this->actionMaxSpeed = 100;
  this->actionMinSpeed = 0;
  this->actionUserData = 0;
  this->actionUserData2 = 0;
}