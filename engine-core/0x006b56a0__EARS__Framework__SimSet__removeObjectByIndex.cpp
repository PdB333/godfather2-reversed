// FUNC_NAME: EARS::Framework::SimSet::removeObjectByIndex
// Function at 0x006b56a0: Removes an object from an internal array (swap + pop) and handles network/ref-count cleanup.
// Class fields (inferred from offsets):
//   +0xa8: mObjectArray (int*) - pointer to array of object pointers (size = mCount * 4)
//   +0xac: mCount (int) - number of objects currently in array
//   +0xfc: mIsNetworked (int) - if nonzero, object needs to be released before removal
//   +0x88: mNumPermanent (int) - count of permanent objects
//   +0xa0: mNumTransient (int) - count of transient objects
//   +0xb8: mNumActive (int) - count of active objects
void __thiscall SimSet::removeObjectByIndex(int thisPtr, int elemIndex)
{
    int* objectArray = *(int**)(thisPtr + 0xa8); // +0xa8: array of object pointers
    int removedObject = objectArray[elemIndex]; // object to remove
    int count = *(int*)(thisPtr + 0xac); // +0xac: current count

    // If not removing the last element, move last element into its slot
    if (elemIndex != count - 1) {
        objectArray[elemIndex] = objectArray[count - 1];
    }

    // Decrement count (effectively pops the last element)
    *(int*)(thisPtr + 0xac) = count - 1;

    // If the container manages network objects, release the removed object
    if (*(int*)(thisPtr + 0xfc) != 0) { // +0xfc: mIsNetworked
        FUN_006bebf0(removedObject); // likely release or decrement refcount
    }

    // Network/multiplayer handling
    char isNetworkInitialized = FUN_00791230(); // check if network is ready
    if (isNetworkInitialized == 0) {
        int isClient = FUN_00791300(); // check if this is a client
        if (isClient != 0) {
            char isHost = FUN_007f47a0(); // check if host
            if (isHost != 0) {
                FUN_00790110(0); // possibly disable network notifications
                FUN_00791350(thisPtr); // notify removal to network
                goto LAB_006b573b;
            }
        }
        // On client (non-host) or non-host server: queue object for deletion locally
        FUN_006b4c10(removedObject); // likely markForDelete or queue
    }
    else {
        // Network is not initialized yet: disable notifications and destroy locally
        FUN_00790110(0);
        FUN_00791350(thisPtr);
        FUN_00792d80(removedObject); // likely destroyObject
    }

LAB_006b573b:
    // If all internal counts are zero, release global mutex; otherwise lock it.
    if ( (*(int*)(thisPtr + 0x88) == 0) &&   // mNumPermanent
         (*(int*)(thisPtr + 0xa0) == 0) &&   // mNumTransient
         (*(int*)(thisPtr + 0xac) == 0) &&   // mCount
         (*(int*)(thisPtr + 0xb8) == 0) ) {  // mNumActive
        FUN_004086d0(&DAT_0112a640); // release mutex (unlock)
    }
    else {
        FUN_00408680(&DAT_0112a640); // acquire mutex (lock)
    }
}