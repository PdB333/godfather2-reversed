// FUNC_NAME: NetSessionManager::updateAllConnections

void __thiscall NetSessionManager::updateAllConnections(int this, char isProcess) {
    int* connArrayPtr;
    uint i;
    int globalData = DAT_0112e2e8; // gNetSessionManager
    uint countA = *(uint*)(globalData + 0x60); // +0x60: count of first array
    uint countB = *(uint*)(globalData + 0x6c); // +0x6c: count of second array
    int* arrayAPtr = *(int**)(globalData + 0x5c); // +0x5c: pointer to first array
    int* arrayBPtr = *(int**)(globalData + 0x68); // +0x68: pointer to second array

    int localArray[3]; // stack container for local connection list
    int localCount = 0; // local_8
    int localPtr = 0; // local_c
    // local_4 unused

    if (isProcess == '\0') {
        // Reset path: just call pollConnection with flag=0 for all connections
        i = 0;
        if (countA != 0) {
            do {
                FUN_00950be0(0, *(int*)(this + 0x13c)); // m_netInterface
                i++;
            } while (i < countA);
        }

        i = 0;
        if (countB != 0) {
            do {
                FUN_00950be0(0, *(int*)(this + 0x13c));
                i++;
            } while (i < countB);
        }

        // Get local connection list and process them
        localArray[0] = 0;
        localArray[1] = 0;
        localArray[2] = 0;
        FUN_00922200(localArray); // getConnectionListFromLocal
        int localCount = localArray[1]; // local_8
        i = 0;
        if (localCount != 0) {
            do {
                FUN_00950be0(0, *(int*)(this + 0x13c));
                i++;
            } while (i < localCount);
        }

        // Reset managers
        FUN_0097d9d0(); // resetFirstManager
        FUN_0097d750(); // resetSecondManager
        FUN_0097db10(); // resetThirdManager
    } else {
        // Process path: poll connections with flag=1, and process active ones
        i = 0;
        if (countA != 0) {
            do {
                char active = FUN_00950be0(1, *(int*)(this + 0x13c));
                if (active != '\0') {
                    int* entry = arrayAPtr + i * 2; // 8-byte entries, so offset i*8
                    int data = entry[0]; // first int in entry
                    if (data == 0) {
                        data = 0;
                    } else {
                        data -= 0x48; // offset back to containing object
                    }
                    FUN_0097e0d0(data); // processConnectionTypeA
                }
                i++;
            } while (i < countA);
        }

        i = 0;
        if (countB != 0) {
            do {
                char active = FUN_00950be0(1, *(int*)(this + 0x13c));
                if (active != '\0') {
                    int* entry = arrayBPtr + i * 2;
                    int data = entry[0];
                    if (data == 0) {
                        data = 0;
                    } else {
                        data -= 0x48;
                    }
                    FUN_0097e150(data); // processConnectionTypeB
                }
                i++;
            } while (i < countB);
        }

        // Process local list
        localArray[0] = 0;
        localArray[1] = 0;
        localArray[2] = 0;
        FUN_00922200(localArray);
        int localCount = localArray[1];
        int* localList = (int*)localArray[0]; // local_c
        i = 0;
        if (localCount != 0) {
            do {
                char active = FUN_00950be0(1, *(int*)(this + 0x13c));
                if (active != '\0') {
                    int data = localList[i];
                    FUN_0097e280(data); // processConnectionTypeC
                }
                i++;
            } while (i < localCount);
        }
    }

    // Free local list if allocated
    if (localArray[0] != 0) {
        FUN_009c8f10(localArray[0]);
    }
}