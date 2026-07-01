// FUNC_NAME: PlayerSM::setPlayerSwitchState
void __thiscall setPlayerSwitchState(int this, char newState)
{
  if (*(char *)(this + 0x5e1) == newState) {
    // Toggle the state flag and reset a timer value
    *(bool *)(this + 0x5e1) = newState == '\0';          // +0x5e1: player switch state boolean
    *(undefined4 *)(this + 0x5e8) = DAT_01205220;        // +0x5e8: switch timer (set to global timer value)
  }
}