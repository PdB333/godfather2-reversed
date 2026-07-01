// FUNC_NAME: NetSession::handleNetEvent
void __thiscall NetSession::handleNetEvent(int this, undefined4 *eventData)
{
  int eventType;
  undefined1 localStack1[12];
  undefined1 localStack2[12];
  
  eventType = (**(code **)*eventData)();
  if (eventType == 0x27a0f69c) {
    eventType = FUN_007ab6f0();
    if (eventType != 0) {
      FUN_007c3900(localStack2,localStack1,*(undefined4 *)(this + 0x58),eventType);
      FUN_00755410(localStack2,localStack1,1,*(undefined4 *)(*(int *)(this + 0x58) + 0x1fdc),0);
    }
  }
  return;
}