// FUNC_NAME: Sentient::updateBoneSen0
void __thiscall Sentient::updateBoneSen0(Sentient* this)
{
    int boneIndex;
    int itemCount;
    int* boneDataPtr;
    int* itemPtr;
    int* dataBase;
    uint itemIdx;
    int* boneArrayPtr;
    int* currentBoneSlot;
    int local_14;
    uint local_10[3];

    *(int8_t*)(this + 8) = 0;
    if ((*(int*)(this + 0x580) != 0) && (*(int*)(this + 0x56C) != 0)) {
        FUN_00c9eac0(); // begin critical section / lock
        currentBoneSlot = (int*)(this + 0x480);
        local_14 = 5;
        do {
            itemIdx = 0;
            if (currentBoneSlot[1] != 0) {
                dataBase = (int*)(*currentBoneSlot + 4);
                do {
                    if (*(int*)(*dataBase + 0x28) == 0x53656e30) { // "Sen0" four-cc
                        if ((int)itemIdx >= 0) { // always true
                            boneArrayPtr = (int*)(this + 0x470);
                            if (*(int*)(boneArrayPtr + itemIdx) != 0) {
                                local_10[0] = 0;
                                local_10[1] = 0;
                                local_10[2] = 0;
                                int sen0Id = FUN_00c9cd50(0x53656e30); // hash/ID for "Sen0"
                                FUN_00c9cbe0(*(int*)(this + 0x580), sen0Id, 0, local_10); // send event
                                local_10[0] = 0;
                                FUN_00c9cd40(0, local_10); // clear event
                            }
                        }
                        break;
                    }
                    itemIdx++;
                    dataBase += 3; // 12-byte stride
                } while (itemIdx < (uint)currentBoneSlot[1]);
            }
            currentBoneSlot += 0xC; // 12-byte slot stride
            local_14--;
        } while (local_14 != 0);
        FUN_00c9eae0(); // end critical section / unlock
    }
}