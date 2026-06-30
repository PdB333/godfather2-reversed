// FUNC_NAME: getPlayerCar
// Address: 0x0074E1C0
// Role: Retrieve the player's current car (if any) and verify it is drivable.
//        Iterates the player manager's linked list (manager type 9), takes each player's
//        vehicle pointer at offset 0x380 (Player::currentVehicle), validates the vehicle,
//        and checks flag bit 1 at vehicle+0x180->+0x34 (likely Vehicle::drivingFlags bit1).
//        Returns vehicle pointer if valid and bit1=0 (drivable), otherwise 0.

#include <cstdint>

// Forward declarations for external functions
void* GetManagerFromType(uint32_t managerType);      // global manager lookup
int   IsVehicleValid(void* vehicle);                 // returns nonzero if vehicle is alive

// Linked list node used by the player manager
struct PlayerNode {
    void* playerObject;       // +0x00: Player*
    PlayerNode* next;         // +0x04: next node
};

// Player structure (partial, only needed offsets)
struct Player {
    uint8_t pad0380[0x380];   // padding to reach currentVehicle
    void* currentVehicle;     // +0x380: pointer to vehicle (WheeledVehicle*)
};

// Vehicle structure (partial)
struct Vehicle {
    uint8_t pad0180[0x180];
    void* someComponent;      // +0x180: pointer to a component (e.g., VehicleDrivingComponent)
};

// Component structure (partial)
struct VehicleComponent {
    uint32_t flags;           // +0x34: bitfield flags
};

// Main function
void* getPlayerCar()
{
    void* vehiclePtr = nullptr;

    // Get the player manager singleton (type 9)
    PlayerNode** headPtr = (PlayerNode**)GetManagerFromType(9);
    if (!headPtr)
        return 0;

    PlayerNode* currentNode = *headPtr;   // head of linked list
    if (!currentNode)
        return 0;

    // Walk the list of players; keep the last player's vehicle (expected single player)
    do {
        if (currentNode->playerObject) {
            Player* player = (Player*)currentNode->playerObject;
            vehiclePtr = player->currentVehicle;   // offset 0x380
        }
        currentNode = currentNode->next;
    } while (currentNode);

    // If no vehicle obtained, return 0
    if (!vehiclePtr)
        return 0;

    // Validate the vehicle
    int validationResult = IsVehicleValid(vehiclePtr);
    if (validationResult == 0)
        return 0;

    // Check drivability flag: bit 1 of (vehicle->component->flags) must be 0
    Vehicle* vehicle = (Vehicle*)vehiclePtr;
    VehicleComponent* component = (VehicleComponent*)(vehicle->someComponent);
    // shift right 1, invert, then AND 1 → true only if original bit 1 is 0
    if ((~(uint8_t)(component->flags >> 1) & 1) != 0)
        return vehiclePtr;
    else
        return 0;
}