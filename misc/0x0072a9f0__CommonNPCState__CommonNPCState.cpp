// FUNC_NAME: CommonNPCState::CommonNPCState
void __thiscall CommonNPCState::CommonNPCState(CommonNPCState *this)
{
  // +0x3B0: pointer to some state data or flag (e.g., m_pParentState)
  if (*(int *)(this + 0x3b0) != 0) {
    // Clean up existing parent state or similar
    ParentStateInit();
  }

  int uVar2 = DAT_012067e8;   // Global manager handle
  int uVar1 = DAT_01205224;   // Global manager handle

  // Build registration information structure
  int local_c = 0;                    // Unknown field (e.g., flags)
  int local_8 = 0xd42a2c49;           // State ID (hash)
  int local_4 = (int)this;            // Pointer to this state

  // Register state with the state machine using a name and the struct
  int uVar3 = RegisterStateType("CommonNPCST", &local_c);

  // Assign a class identifier (0x1a2bb90 is likely a vtable or class token)
  uVar3 = AssignStateClass(0x1a2bb90, uVar3, &local_c);

  // Finalize registration with the two global managers
  FinalizeStateRegistration(uVar1, uVar2, uVar3, 0, 0);
}