// FUNC_NAME: GameManager::initializePlayerSystem
// Address: 0x008dc610
// Description: Initializes player system, allocates and registers player object if gameplay is active.

void __fastcall GameManager::initializePlayerSystem(void* param_1)
{
    // Engine and subsystem initialization
    Engine::initialize();                          // FUN_004df600
    Subsystem::initialize();                       // FUN_008dc450

    // Check if gameplay is active (e.g., not in menu)
    if (Gameplay::isActive())                      // FUN_00481660
    {
        // Allocate player object (size 0x38 bytes)
        Player* player = (Player*)Memory::allocate(0x38); // FUN_009c8e50
        if (player != nullptr)
        {
            // Construct player with given parameter (e.g., player index or config)
            Player* constructedPlayer = Player::construct(player, param_1); // FUN_008db8f0
            // Register player with the manager
            PlayerManager::registerPlayer(constructedPlayer); // FUN_00481690
            return;
        }
        // Allocation failed, register null
        PlayerManager::registerPlayer(nullptr);
    }
}