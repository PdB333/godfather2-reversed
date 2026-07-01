// FUNC_NAME: SomeTimerClass::updateCurrentWorldTime
void __fastcall SomeTimerClass::updateCurrentWorldTime(void* this)
{
  int currentTime;

  currentTime = FUN_008fe480(); // Get some current world time value
  if (currentTime != *(int *)((int)this + 0xdc)) { // +0xdc: lastKnownWorldTime
    FUN_008fddc0(); // Handle world time change
    FUN_008fe5e0(currentTime); // Store new world time to local data
  }
  return;
}