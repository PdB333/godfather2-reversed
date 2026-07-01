// FUNC_NAME: NPCCrewComponent::~NPCCrewComponent
void __fastcall NPCCrewComponent::destructor(int this)

{
  if (*(int *)(this + 0x1c88) != 0) {
    FUN_0054e520(); // likely a deallocation or cleanup function
    FUN_0054e2e0(*(undefined4 *)(this + 0x1c88)); // free or release the crew data handle
    *(undefined4 *)(this + 0x1c88) = 0; // null out the pointer
  }
  return;
}