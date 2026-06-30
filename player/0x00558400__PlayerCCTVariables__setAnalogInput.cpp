// FUNC_NAME: PlayerCCTVariables::setAnalogInput
void __thiscall PlayerCCTVariables::setAnalogInput(undefined4 param_2, undefined4 param_3)
{
  int subObject;
  
  // Check if pointer at this+0x1c is valid (likely a subcomponent handle)
  if (*(int *)(this + 0x1c) == 0) {
    subObject = 0;
  }
  else {
    // Dereference to get subcomponent object, then read pointer at +0x10 from it
    subObject = *(int *)(*(int *)(this + 0x1c) + 0x10);
  }
  // If sub-object exists, store the two input values (e.g., analog stick X, Y)
  if (subObject != 0) {
    *(undefined4 *)(subObject + 0x40) = param_2;  // +0x40: first axis/input
    *(undefined4 *)(subObject + 0x44) = param_3;  // +0x44: second axis/input
  }
  return;
}