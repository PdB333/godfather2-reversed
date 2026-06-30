// FUNC_NAME: PlayerF2FSM::constructor
void __fastcall PlayerF2FSM::constructor(undefined4 param_1)
{
  undefined8 *in_EAX;
  int unaff_ESI;
  
  *(undefined1 *)(unaff_ESI + 0x160) = 0; // +0x160: some flag (e.g., bIsInF2F)
  *(undefined1 *)(unaff_ESI + 0x161) = 0; // +0x161: another flag
  *(undefined1 *)(unaff_ESI + 400) = 1;   // +0x190: some state flag (e.g., bInitialized)
  *(undefined8 *)(unaff_ESI + 0x100) = *in_EAX; // +0x100: copy of data from EAX (likely a struct/class pointer)
  *(undefined8 *)(unaff_ESI + 0x108) = in_EAX[1]; // +0x108: second qword
  *(undefined4 *)(unaff_ESI + 0x110) = *(undefined4 *)(in_EAX + 2); // +0x110: third dword
  FUN_00452df0(param_1); // likely base class constructor (e.g., PlayerSM::constructor)
  FUN_00655070(unaff_ESI); // likely init function (e.g., initF2FData)
  *(undefined4 *)(unaff_ESI + 0x19c) = 0; // +0x19c: some counter or state (e.g., m_f2fTimer)
  *(undefined4 *)(unaff_ESI + 0x1b4) = 4; // +0x1b4: some enum/state (e.g., eF2FState = 4)
  FUN_00655f50(); // likely another init function (e.g., resetF2F)
  return;
}