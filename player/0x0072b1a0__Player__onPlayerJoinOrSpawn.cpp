// FUNC_NAME: Player::onPlayerJoinOrSpawn
// Address: 0x0072b1a0
// Part of EA EARS engine (The Godfather 2)
// Handles player identity validation and state machine initialization

void __fastcall Player::onPlayerJoinOrSpawn(Player* this)
{
    int iVar1;
    byte local_19; // used as output for GUID lookup
    int local_18;  // holds this pointer for callback context

    // Call base class initialization (likely EARS::Entity or Player base)
    BaseClass::init(this);  // FUN_00738d20

    // Set up a callback function pointer in the player's state machine/component
    // Offset +0x5F4 likely points to a PlayerStateMachine or ComponentData structure
    PlayerStateMachine* stateMachine = *(PlayerStateMachine**)((uint)this + 0x5F4);
    // Store a function pointer (state handler?) and this pointer into the structure
    // Offsets +0x34 and +0x3C etc.
    stateMachine->callbackFn = (code*)FUN_00736570;  // +0x34
    stateMachine->context = this;                     // +0x38? Actually stored as high 32-bit of the 8-byte value at +0x34
    *(uint64*)((uint)stateMachine + 0x3C) = 0;       // Clear another callback field
    *(uint64*)((uint)stateMachine + 0x44) = 0x0072A56000000000ULL; // Store a default handler address and zero

    // Check if the player has a non-zero and non-default GUID
    // GUID stored as 4 int32 at offsets 0x26C0, 0x26C4, 0x26C8, 0x26CC
    uint guidPart0 = *(uint*)((uint)this + 0x26C0);
    uint guidPart1 = *(uint*)((uint)this + 0x26C4);
    uint guidPart2 = *(uint*)((uint)this + 0x26C8);
    uint guidPart3 = *(uint*)((uint)this + 0x26CC);

    // Default/empty GUID values (magic constants from game)
    const uint kDefaultGuidPart0 = 0xBAEDBBBA;  // -0x45245246
    const uint kDefaultGuidPart1 = 0xBEEFBEEF;  // -0x41104111
    const uint kDefaultGuidPart2 = 0xEAC15A55;  // -0x153EA5AB
    const uint kDefaultGuidPart3 = 0x91100911;  // -0x6EEFF6EF

    // If GUID is not all zero AND not equal to the default "null" GUID
    if ((guidPart0 != 0 || guidPart1 != 0 || guidPart2 != 0 || guidPart3 != 0) &&
        !(guidPart0 == kDefaultGuidPart0 && guidPart1 == kDefaultGuidPart1 &&
          guidPart2 == kDefaultGuidPart2 && guidPart3 == kDefaultGuidPart3))
    {
        // Attempt to find an entity or session by this GUID
        iVar1 = EntityManager::findByGuid((EntityManager*)this + 0x26C0, &local_19);  // FUN_00448100
        if (iVar1 != 0)
        {
            Entity* foundEntity = (Entity*)iVar1;
            EntityManager::processEntity(foundEntity); // FUN_00710e70
            EntityManager::finalizeEntityProcessing(); // FUN_00716820
        }
    }

    // Finalize player setup (may trigger state machine transitions)
    Player::finalizeInitialization(this); // FUN_0072A3E0
}