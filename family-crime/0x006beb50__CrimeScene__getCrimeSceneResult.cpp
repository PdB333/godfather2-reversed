// FUNC_NAME: CrimeScene::getCrimeSceneResult
uint __fastcall CrimeScene::getCrimeSceneResult(CrimeScene* this) {
    // +0x34 is bitfield flags; check bit 0
    if (((this->flags & 1) != 0) &&
        ((this->subObject1 != nullptr && *this->subObject1->typeId == 0x637b907) ||
         (this->subObject2 != nullptr && *this->subObject2->typeId == 0x637b907))) {
        // Return magic crime scene constant indicating active scene?
        return 0x637b900;
    }
    // Otherwise return bool indicating whether some other field is zero
    return (uint)(this->someOtherField == 0);
}