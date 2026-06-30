// FUNC_NAME: VehicleBrain::create
//
// Address: 0x006c59a0
// Role: Factory/initialization for a VehicleBrain object (size 0x310)
// Uses custom allocator from FUN_009c8f80 (likely gMemoryManager)

// Assuming this function is a static method or member of VehicleBrain
// Because it allocates a new block and returns a pointer.
// param_1 is 'this' pointer for the calling context? Actually passed as argument, so likely a parent/owner pointer.
// Let's treat param_1 as a Context* or Owner* pointer (maybe this is a member of a manager).

int __fastcall VehicleBrain::create(VehicleBrain* this) // this is actually the owner? Ghidra shows param_1, but fastcall with one param means ECX = this
{
    undefined4 *allocatorFuncTable;
    int newObj;
    undefined4 retVal;
    AllocDescriptor allocDesc; // struct { int size; int flags; int alignment; } at stack offset

    // Get the global memory allocator function table
    allocatorFuncTable = (undefined4 *)FUN_009c8f80(); // likely gMemoryManager->vtable

    // Setup allocation descriptor: size 2, flags 0x10, alignment 0
    allocDesc.size = 2;        // +0x00
    allocDesc.flags = 0x10;    // +0x04
    allocDesc.alignment = 0;   // +0x08

    // Allocate 0x310 bytes using the allocator
    newObj = (**(code **)*allocatorFuncTable)(0x310, &allocDesc);
    if (newObj == 0) {
        retVal = 0;
    } else {
        // Construct the new object with the owner (this) as parameter
        retVal = FUN_006c3360(newObj, this); // likely VehicleBrain::construct(NewObj, this)
    }

    // Check a state field at this+0x90 (owner's state)
    // If state is 0 (kStateIdle) or 0x48 (kStateActive?), do some setup
    if ((*(int *)(this + 0x90) == 0) || (*(int *)(this + 0x90) == 0x48)) {
        // Get a transform or component at this+0x58
        undefined4 *transform = FUN_00445ff0(this + 0x58, 0); // likely GetTransformPtr(this+0x58, NULL)
        // Set a parameter: float constant 0x38523fc3 (~0.02f? Actually 0.0000501f but might be a fixed-point)
        FUN_004480d0(transform, 0x38523fc3, &stack_extra); // stack_extra likely is from allocDesc? Actually &stack0xffffffe8 is the local allocDesc? But code passes &stack0xffffffe8, which is the address of the allocDesc? That seems odd. Might be a different variable.
        // Note: The decompiler shows &stack0xffffffe8, which is likely the address of the allocDesc on stack. But this call uses that as an extra parameter? Possibly to store result.
    }

    // Call an initialization function on a sub-object at this+0x68
    FUN_006c16d0(this + 0x68); // likely InitSubObject(this+0x68)

    return retVal;
}