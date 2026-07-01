// FUNC_NAME: PlayerAimComponent::isAimOnTarget
undefined1 __thiscall PlayerAimComponent::isAimOnTarget(PlayerAimComponent *this, void *aimParam) {
    bool firstTargetMatched;
    undefined1 result;
    int *targetDataPtr;
    Transform *firstTransform;
    Transform *secondTransform;

    targetDataPtr = *(int **)((int)aimParam + 4); // param2+4 -> pointer to target data
    result = 0;
    if (targetDataPtr != 0) {
        if (*(int *)(targetDataPtr + 4) == 0) { // targetDataPtr->ptrToFirst
            firstTransform = 0;
        } else {
            firstTransform = (Transform *)(*(int *)(targetDataPtr + 4) - 0x48); // subtract header offset to get base
        }
        firstTargetMatched = false;
        // Check if this->firstAimVector is all zero OR matches firstTransform->aimVector
        if ((((this->firstAimVector.x == 0) && (this->firstAimVector.y == 0)) && 
             (this->firstAimVector.z == 0) && (this->firstAimVector.w == 0)) ||
            ((firstTransform != 0 && (firstTransform->aimVector.x == this->firstAimVector.x) && 
              (firstTransform->aimVector.y == this->firstAimVector.y) && 
              (firstTransform->aimVector.z == this->firstAimVector.z) && 
              (firstTransform->aimVector.w == this->firstAimVector.w)))) {
            firstTargetMatched = true;
        }
        if (*(int *)(targetDataPtr + 0xc) == 0) { // targetDataPtr->ptrToSecond
            secondTransform = 0;
        } else {
            secondTransform = (Transform *)(*(int *)(targetDataPtr + 0xc) - 0x48);
        }
        // Check if this->secondAimVector is all zero OR matches secondTransform->aimVector
        if ((((this->secondAimVector.x == 0) && (this->secondAimVector.y == 0)) && 
             (this->secondAimVector.z == 0) && (this->secondAimVector.w == 0)) ||
            ((secondTransform != 0 && (secondTransform->aimVector.x == this->secondAimVector.x) && 
              (secondTransform->aimVector.y == this->secondAimVector.y) && 
              (secondTransform->aimVector.z == this->secondAimVector.z) && 
              (secondTransform->aimVector.w == this->secondAimVector.w)))) {
            if (firstTargetMatched) {
                result = 1;
            }
        }
    }
    return result;
}