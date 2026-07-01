// FUNC_NAME: CheatCodeTracker::incrementKeyFrequency (0x0084a910)
// This function maintains a sorted frequency table of float keys (presumably cheat code hashes).
// When a key is entered repeatedly and becomes the sole entry with a count equal to a threshold,
// it triggers cheat activation logic. The special key 0x637b907 triggers an alternative cheat path.

void __thiscall CheatCodeTracker::incrementKeyFrequency(int *this, float keyHash)
{
    int keyAsInt;
    int *entryPtr;
    int i;
    int threshold;

    keyAsInt = (int)keyHash;  // truncate float to int for storage, but comparison uses float
    i = 0;
    if (this[5] != 0) {
        entryPtr = (int *)this[4];
        do {
            if ((float)*entryPtr == keyHash) {
                // Found existing entry – increment its count
                if (i != 0xffffffff) {
                    entryPtr = (int *)this[4] + i * 2 + 1; // point to count part of the entry
                    *entryPtr = *entryPtr + 1;
                    // Re-sort if more than one entry exists
                    if (1 < (uint)this[5]) {
                        _qsort((void *)this[4], this[5], 8, (_PtFuncCompare *)&compareFloatPairs_0x0084a120);
                    }
                    goto checkTrigger;
                }
                break;
            }
            i = i + 1;
            entryPtr = entryPtr + 2;
        } while (i < (uint)this[5]);
    }

    // Key not found – add new entry
    if (this[5] == this[6]) {
        // Resize array if full
        int newCapacity;
        if (this[6] == 0) {
            newCapacity = 1;
        } else {
            newCapacity = this[6] * 2;
        }
        resizeArray_0x0084a270(newCapacity);  // realloc and update this[4], this[6]
    }

    entryPtr = (int *)(this[4] + this[5] * 8); // address of new entry (two ints)
    this[5] = this[5] + 1;
    *entryPtr = keyAsInt;   // store key as int (but comparison uses float)
    entryPtr[1] = 1;        // initial count is 1

checkTrigger:
    // Determine if this key is the sole entry and has reached the required count
    threshold = *(int *)(*this + 4); // threshold stored in a config structure pointed by this[0]
    if ((this[5] == 1) && (((int *)this[4])[1] == threshold)) {
        // First and only entry’s count equals threshold – remember its key
        keyAsInt = *(int *)this[4];
    } else {
        keyAsInt = 0;
    }

    if (keyAsInt == (int)keyHash) {
        // The key hash equals the sole entry’s key (i.e., it reached threshold while being alone)
        uint cheatFlag1 = *(char *)(DAT_01129904 + 0x3c);  // global cheat enabled flag
        uint cheatFlag2 = *(char *)(DAT_0112a590 + 4);     // another global flag
        if ((cheatFlag1 == '\0') || (cheatFlag2 == '\0') || ((int)keyHash != 0x637b907)) {
            // Normal cheat activation path
            char isCheatPermitted = FUN_0084a670();  // check if cheats are allowed
            if (isCheatPermitted != '\0') {
                FUN_008c78d0((int)keyHash, *this);   // trigger cheat effect
            }
        } else {
            // Special path for cheat hash 0x637b907 (e.g., "unlock all")
            FUN_0093f6c0(1, *(undefined4 *)*this, &LAB_0084a6d0); // show splash/message
            playSoundEffect_0x007e7df0(0x1d);
            playCutscene_0x007e8e10(*(undefined4 *)(*this + 0x48));
            float newValue = 0.0f;
            getStatOrVariable_0x008934e0(0x903cd299, &newValue); // retrieve something
            int someCount = getSomeCount_0x0084ad70(0x637b907);
            float countFloat = (float)someCount;
            if (someCount < 0) {
                countFloat = countFloat + DAT_00e44578; // add a bias for negative ints
            }
            if (newValue < countFloat) {
                setStatOrVariable_0x00894ea0(0x903cd299, countFloat, 0);
            }
            if (someCount == *(int *)(DAT_0112a590 + 0xc)) {
                showMessage_0x0093f6c0(4, 0, 0);
                finalizeCheat_0x00894c90(0x43051991);
                return;
            }
        }
    }
}