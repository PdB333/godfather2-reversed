// FUNC_NAME: Unknown::checkAndExecuteSomething
int __fastcall FUN_00950a40(int this)
{
  int status;
  undefined4 unk1;
  
  // Check if field at +0x168 is 0 or 0x48 (76)
  if ((((*(int *)(this + 0x168) == 0) || (*(int *)(this + 0x168) == 0x48)) &&
      // Check if field at +0x144 is non-zero, OR any of the 4 consequent fields are non-zero
      ((*(int *)(this + 0x144) != 0 ||
       (((*(int *)(this + 0x148) != 0 || (*(int *)(this + 0x14c) != 0)) ||
        (*(int *)(this + 0x150) != 0)))))) &&
     // Check that these fields don't have specific sentinel values
     ((((*(int *)(this + 0x144) != -0x45245246 || (*(int *)(this + 0x148) != -0x41104111)) ||
       ((*(int *)(this + 0x14c) != -0x153ea5ab || (*(int *)(this + 0x150) != -0x6eeff6ef)))) &&
      // And some function returns non-zero for the pointer at +0x144
      (status = FUN_00446100((int *)(this + 0x144), 0), status != 0)))) {
    // If condition holds, call these functions
    unk1 = FUN_006b9c80(status, 0xd7e44d6a);
    FUN_006ba790(unk1);
    // If this is null, set status to 0, otherwise add 0x50 to this
    if (this == 0) {
      status = 0;
    } else {
      status = this + 0x50;
    }
    FUN_00791e70(status);
  }
  // Return if field at +0x168 is non-zero, return that + (-0x48)
  if (*(int *)(this + 0x168) != 0) {
    return *(int *)(this + 0x168) + -0x48;
  }
  return 0;
}