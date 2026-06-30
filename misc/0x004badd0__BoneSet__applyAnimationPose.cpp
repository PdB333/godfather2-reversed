// FUNC_NAME: BoneSet::applyAnimationPose
int __thiscall BoneSet::applyAnimationPose(BoneSet* this, AnimationPose* pose) {
    // First loop: apply bone transforms from pose's local bone array
    int boneCount = *(int*)(pose + 8); // pose->boneTransformCount
    if (boneCount != 0) {
        int boneBase = *(int*)(pose + 4); // pose->boneTransforms
        for (int i = 0; i < boneCount; i++) {
            int boneEntry = boneBase + i * 0x34; // each bone transform is 0x34 bytes
            int field0  = *(int*)(boneEntry + 0);      // +0x00
            int field4  = *(int*)(boneEntry + 4);      // +0x04 (index into something)
            int field8  = *(int*)(boneEntry + 8);      // +0x08
            int field30 = *(int*)(boneEntry + 0x30);   // +0x30
            // Apply the bone transform using a global base offset
            FUN_004baef0(field8, field4 * 0x10 + *(int*)(pose + 0x1c), field0, field30);
        }
    }

    // Second loop: link bones from this->boneArray using pose's link entries
    int linkCount = *(int*)(pose + 0x14); // pose->linkCount
    if (linkCount != 0) {
        int linkBase = *(int*)(pose + 0x10); // pose->links
        for (int j = 0; j < linkCount; j++) {
            int linkEntry = linkBase + j * 0x20; // each link is 0x20 bytes
            int linkId1 = *(int*)(linkEntry + 0x10); // link source bone ID
            int linkId2 = *(int*)(linkEntry + 0x14); // link target bone ID

            // Search for bone with ID = linkId1 in this->boneArray
            int bone1 = 0;
            if (linkId1 != -1) {
                int thisBoneCount = *(int*)(this + 8); // this->boneCount
                if (thisBoneCount != 0) {
                    int thisBoneBase = *(int*)(this + 4); // this->bones
                    for (uint k = 0; k < (uint)thisBoneCount; k++) {
                        int bone = thisBoneBase + k * 0x34;
                        if (*(int*)(bone + 8) == linkId1) { // compare bone ID at offset +8
                            bone1 = bone;
                            break;
                        }
                    }
                }
            }

            // Search for bone with ID = linkId2 in this->boneArray
            int bone2 = 0;
            if (linkId2 != -1) {
                int thisBoneCount = *(int*)(this + 8);
                if (thisBoneCount != 0) {
                    int thisBoneBase = *(int*)(this + 4);
                    for (uint l = 0; l < (uint)thisBoneCount; l++) {
                        int bone = thisBoneBase + l * 0x34;
                        if (*(int*)(bone + 8) == linkId2) {
                            bone2 = bone;
                            break;
                        }
                    }
                }
            }

            // Link the two bones using the link entry
            FUN_004bafc0(linkEntry, bone1, bone2);
        }
    }

    return (int)this;
}