// FUNC_NAME: CrewLeaderComponent::validateCrewState
void __thiscall CrewLeaderComponent::validateCrewState(int this, char flag)
{
  int crewCount;
  int *crewArray;
  int firstState;
  int count;
  int action;

  crewCount = *(int *)(this + 0x3c8);
  if (crewCount == 0) {
    return;
  }
  crewArray = *(int **)(this + 0x3c4);
  if (*crewArray == 0) {
    return;
  }
  firstState = *(int *)(*crewArray + 0x10);

  if (flag == '\0') {
    if (firstState != 1) {
      if (firstState != 2) {
        goto LAB_fail;
      }
      action = 3;
      count = 0;
      if (crewCount == 0) goto LAB_success;
      do {
        if (*(int *)(*crewArray + 0x10) == 3) {
          count++;
        }
        crewArray++;
        crewCount--;
      } while (crewCount != 0);
      goto LAB_checkCount;
    }
  }
  else {
    if (firstState != 3) {
      if (firstState != 2) {
        goto LAB_fail;
      }
      action = 1;
      count = 0;
      if (crewCount == 0) goto LAB_success;
      do {
        if (*(int *)(*crewArray + 0x10) == 1) {
          count++;
        }
        crewArray++;
        crewCount--;
      } while (crewCount != 0);
LAB_checkCount:
      if (7 < count) {
LAB_fail:
        // Print failure message
        FUN_00408a00(DAT_011302c0, 0);
        return;
      }
      goto LAB_success;
    }
  }
  action = 2;

LAB_success:
  FUN_00408a00(DAT_011304d8, 0);
  FUN_00402050(DAT_011304d8, 0);
  FUN_00964350(action);
  return;
}