// FUNC_NAME: BaseVehicle::isMoving
// Function address: 0x00705b40
// Checks if the vehicle is currently moving. Returns false if stopped or parked (state 0 or 0x48).
// The motion component pointer is at offset +0xf0 from 'this', and its state int is at +0x74c.
bool __fastcall BaseVehicle::isMoving() // __fastcall with ECX as 'this' (implicit)
{
    // Get pointer to a motion/state component at offset +0xf0
    int* motionComponent = *(int**)((char*)this + 0xf0);
    if (motionComponent != 0)
    {
        // Read vehicle motion state from component at +0x74c
        int state = *(int*)((char*)motionComponent + 0x74c);
        // 0 = stopped, 0x48 = parked (72 decimal)
        if (state == 0 || state == 0x48)
            return false;
    }
    return true;
}