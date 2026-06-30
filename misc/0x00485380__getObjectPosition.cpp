// FUNC_NAME: getObjectPosition
// Address: 0x00485380
// Role: Retrieves the position of an object by calling the first virtual method on a global entity manager singleton.

#include <cstdint>

struct Vector3
{
    float x;
    float y;
    float z;
    
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
};

// Abstract interface for the entity manager (returned by FUN_009c8f80)
class IEntityManager
{
public:
    virtual void getPosition(uint32_t objectHandle, Vector3* outPosition) = 0;
};

// Singleton accessor (FUN_009c8f80)
IEntityManager* GetEntityManager();

void getObjectPosition(uint32_t objectHandle, Vector3* outPosition)
{
    // Initialize output to zero for safety (matching the original zeros)
    *outPosition = Vector3();
    
    // Obtain the global entity manager
    IEntityManager* manager = GetEntityManager();
    
    // Call the first virtual method (vtable index 0)
    manager->getPosition(objectHandle, outPosition);
}