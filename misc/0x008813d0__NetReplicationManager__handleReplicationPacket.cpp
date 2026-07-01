// FUNC_NAME: NetReplicationManager::handleReplicationPacket
// Address: 0x008813d0
// Role: Handles an incoming replication packet (type 0x12). Looks up the object by hash,
// sets the current object pointer, and marks a flag if the object is expired.

int __thiscall NetReplicationManager::handleReplicationPacket(int thisPtr, int param2, int param3, int param4, int packetType, int param6)
{
    char charRet;
    int result;
    int hashArray[5]; // local_18
    int iterOut; // local_20
    int objectPtr; // local_24
    int tempObject; // local_1c

    // If packet type is not 0x12, delegate to another handler
    if (packetType != 0x12) {
        return FUN_00882b10(param2, param3, param4, packetType, param6);
    }

    // Only process if the object container at +0x68 is non-null
    if (*(int *)(thisPtr + 0x68) != 0) {
        objectPtr = 0;
        charRet = getGlobalObjectHashes(hashArray, 4); // FUN_00543390
        if (charRet != 0) {
            int count = getGlobalObjectHashCount(); // FUN_00543370
            for (int i = 0; i < count; i++) {
                if (hashArray[i] != 0) {
                    int temp; // local_20 reused
                    iterOut = 0;
                    charRet = (**(code **)(*(int *)hashArray[i] + 0x10))(0x369ac561, &iterOut); // findObjectByHash
                    if ((charRet != 0) && (iterOut != 0)) {
                        *(int *)(thisPtr + 0x84) = *(int *)(iterOut + 0x2134); // set current object pointer
                        objectPtr = *(int *)(iterOut + 0x1ed4); // get some value
                    }
                    break;
                }
            }
        }

        // If current object not set, try to iterate through the container at +0x68
        if (*(int *)(thisPtr + 0x84) == 0) {
            int container = *(int *)(thisPtr + 0x68);
            iterOut = 0;
            tempObject = 0;
            charRet = (**(code **)(*(int *)container + 0x1cc))(&iterOut); // getFirstObject
            while (charRet != 0) {
                int isValid = FUN_00875990(&iterOut);
                if (isValid != 0) {
                    int objPointer = FUN_00790d90();   // get object from iter
                    *(int *)(thisPtr + 0x84) = objPointer;
                    objectPtr = FUN_007914e0();        // get some value from iter
                }
                if (*(int *)(thisPtr + 0x84) != 0) break;
                charRet = (**(code **)(*(int *)container + 0x1d0))(&iterOut, &iterOut); // getNextObject
            }
        }

        // Validate the current object
        if ((*(int *)(thisPtr + 0x84) == 0) ||
            (int resolved = FUN_006b07e0(*(int *)(thisPtr + 0x84)), resolved == 0) ||
            (*(int *)(*(int *)(resolved + 0x180) + 0xfc) == 0)) {
            return 1;
        }

        // Check if the object is marked as expired/removed
        charRet = FUN_006be980(objectPtr);
        if (charRet != 0) {
            *(int *)(thisPtr + 0x78) |= 0x40; // set flag bit
        }
    }

    return 1;
}