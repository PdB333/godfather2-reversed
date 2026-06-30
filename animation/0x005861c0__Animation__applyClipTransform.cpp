// FUNC_NAME: Animation::applyClipTransform

int Animation::applyClipTransform(Animation* this, undefined8* transformData, byte flags)
{
    char* weightArray;
    int numTracks;
    undefined4 uVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    int iVar6;
    int iVar7;
    undefined8 tempTransform;
    undefined4 tempTransformExtra;

    if ((this != 0) && (iVar6 = Animation::allocate(), iVar6 != 0)) {
        if ((flags & 4) == 0) {
            Animation::validate();
            Animation::prepare(this);
            iVar7 = *(int *)(*(int *)(this + 0x38) + 0xc);  // +0x38: pointer to track data, +0xc: track count
            iVar2 = *(int *)(this + 0x34);                    // +0x34: pointer to clip source data
            if (*(int *)(iVar6 + 0x3c) == 0) {               // +0x3c: flag for additive mode
                weightArray = (char *)(iVar2 + 0x14);         // +0x14: weight array
                if (*(char *)(iVar2 + 0x10) == '\0') {        // +0x10: is additive flag
                    for (; 0 < iVar7; iVar7 = iVar7 + -1) {
                        tempTransformExtra = *(undefined4 *)(transformData + 1);
                        tempTransform = *transformData;
                        if (*weightArray == '\x02') {         // weight value = 2 indicates full influence
                            Animation::applySingleTransform(&tempTransform);
                        }
                        weightArray = weightArray + 1;
                    }
                }
                else {
                    for (; 0 < iVar7; iVar7 = iVar7 + -1) {
                        Animation::applySingleTransform(transformData);
                    }
                }
            }
            else {
                weightArray = (char *)(iVar2 + 0x14);
                if (*(char *)(iVar2 + 0x10) == '\0') {
                    for (; 0 < iVar7; iVar7 = iVar7 + -1) {
                        tempTransformExtra = *(undefined4 *)(transformData + 1);
                        tempTransform = *transformData;
                        if (*weightArray == '\x02') {
                            Animation::applySingleTransform(&tempTransform);
                        }
                        weightArray = weightArray + 1;
                    }
                }
                else {
                    for (; 0 < iVar7; iVar7 = iVar7 + -1) {
                        Animation::applySingleTransform(transformData);
                    }
                }
            }
        }
        if (((flags & 8) == 0) && (*(char *)(this + 0x30) == '\x02')) {  // +0x30: animation state/type
            uVar3 = *(undefined4 *)(this + 0x14);
            uVar4 = *(undefined4 *)(this + 0x18);
            uVar5 = *(undefined4 *)(this + 0x1c);
            *(undefined4 *)(iVar6 + 0x10) = *(undefined4 *)(this + 0x10); // copy transform matrix (position+rotation)
            *(undefined4 *)(iVar6 + 0x14) = uVar3;
            *(undefined4 *)(iVar6 + 0x18) = uVar4;
            *(undefined4 *)(iVar6 + 0x1c) = uVar5;
            uVar3 = *(undefined4 *)(this + 0x24);
            uVar4 = *(undefined4 *)(this + 0x28);
            uVar5 = *(undefined4 *)(this + 0x2c);
            *(undefined4 *)(iVar6 + 0x20) = *(undefined4 *)(this + 0x20);
            *(undefined4 *)(iVar6 + 0x24) = uVar3;
            *(undefined4 *)(iVar6 + 0x28) = uVar4;
            *(undefined4 *)(iVar6 + 0x2c) = uVar5;
            *(undefined1 *)(iVar6 + 0x30) = 2; // set new state
        }
        return iVar6;
    }
    return 0;
}