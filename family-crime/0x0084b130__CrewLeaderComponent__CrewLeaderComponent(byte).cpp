// FUNC_NAME: CrewLeaderComponent::CrewLeaderComponent(byte)
// Address: 0x0084b130
// Role: Constructor; initializes base class and conditionally performs additional setup based on a flag bit.
// Parameter param_2: bit 0 controls whether to call additional initialization (FUN_009c8eb0).
CrewLeaderComponent* __thiscall CrewLeaderComponent::CrewLeaderComponent(byte param_2)
{
    // Call base class constructor (likely EARS::Component or similar)
    FUN_0084af70();
    
    // If the lowest bit of param_2 is set, perform extra initialization
    if ((param_2 & 1) != 0) {
        FUN_009c8eb0(this); // e.g., load specific CrewLeaderComponent data
    }
    
    return this;
}