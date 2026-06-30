// FUNC_NAME: VehicleBrain::VehicleBrain

#include <cstdint>

// Forward declaration of allocator interface (simplified)
struct AllocatorInterface {
    void* (*allocate)(uint32_t size, uint32_t* params); // params: {flags=2, alignment=0x10, unknown=0}
};

// Forward declaration of sub-object constructors
void __fastcall BaseVehicleConstructor(void* thisPtr); // FUN_006dd1b0
void __fastcall InitNavigationComponent(void* navPtr); // FUN_006dce00 (at offset +0x68)

// Global allocator singleton getter
AllocatorInterface* GetAllocatorGlobal(); // FUN_009c8f80

// Constructor for VehicleBrain (size 0x2e0)
uint32_t __fastcall VehicleBrain::VehicleBrain(void* thisPtr) {
    AllocatorInterface* alloc = GetAllocatorGlobal();
    uint32_t result = 0;

    // Allocation parameters: flags=2, alignment=0x10, unknown=0
    uint32_t allocParams[3] = {2, 0x10, 0};

    // Attempt to allocate memory for this object (0x2e0 = 736 bytes)
    void* allocatedObject = alloc->allocate(0x2e0, allocParams);
    if (allocatedObject != nullptr) {
        // Initialize base class (likely Vehicle, at offset 0)
        result = BaseVehicleConstructor(allocatedObject);

        // Initialize sub-component at offset 0x68 (e.g., HavokWheeledVehicle or Navigation)
        InitNavigationComponent(static_cast<char*>(allocatedObject) + 0x68);
    }

    return result;
}