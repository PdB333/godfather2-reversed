// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_PromoteFamilyMember
// FUNC_NAME: PromotionManager::endPromotion
void __thiscall PromotionManager::endPromotion(uint param_2)
{
  int newPromotionId;
  
  newPromotionId = this->getNextPromotion(this->currentPromotionId);
  if (gPromotionBase + 0x18 + this->currentPromotionId * 0x24 != 0) {
    this->promotionCleanup(param_2);
  }
  this->setCurrentPromotion(this->currentPromotionId, newPromotionId);
  this->currentPromotionId = newPromotionId;
  *(int *)(this + 0x104) = 1;
  *(byte *)((int)this + 0x12c) = 0; // maybe a flag
  gEventManager->sendEvent("EndPromotion", 0, &DAT_00d8fe44, 0);
  gScheduler->pushCallback(&localStackVar, 0); // stack variable used for callback
  this->stateMachine->pushState(&LAB_005bfc10, 0);
  this->stateMachine->processCurrentState();
  this->stateMachine->pushState(&LAB_005bfbe0, 0);
}