// FUNC_NAME: BaseVehicle::isOccupiedAndOperable
bool __thiscall BaseVehicle::isOccupiedAndOperable(void *thisPtr) {
    // Check if the vehicle is occupied (byte flag at +0x1028)
    // and not in a disabled/unkillable state (int at +0xffc != 0 && != 0x48)
    bool isOccupied = *(char*)((char*)thisPtr + 0x1028) != 0;
    int state = *(int*)((char*)thisPtr + 0xffc);
    if (isOccupied && state != 0 && state != 0x48) {
        return true;
    }
    return false;
}