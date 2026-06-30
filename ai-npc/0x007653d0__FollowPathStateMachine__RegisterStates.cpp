// FUNC_NAME: FollowPathStateMachine::RegisterStates

void FollowPathStateMachine::RegisterStates(void)
{
    undefined4 someHash;

    someHash = GetSomeHash(); // Probably from string "SmootherPathST" or similar
    AddStateWithName("SmootherPathST", someHash);
    SetStateProperty("smoothPathing", 0xffffffff);
    AddState(0xb); // 11
    AddState(10);
    SetStateDefaultTransition(10);
    AddStateWithName("FollowPathST", 1);
    RegisterTerminateState("terminate", 1);
    SetStateProperty("terminate", 0xffffffff);
    AddState(2);
    RegisterStateMachine(0x3c52ffda, &FollowPathStateMachine::update, "SmootherPathSM");
    FinalizeRegistration();
}