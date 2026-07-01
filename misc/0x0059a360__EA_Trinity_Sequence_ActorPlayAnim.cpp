// Xbox PDB: EA::Trinity::Sequence::ActorPlayAnim
// FUNC_NAME: Sequence::actorPlayAnim
void __fastcall Sequence::actorPlayAnim(Sequence *this) {
  AnimRecord *animRec = *(AnimRecord **)((char *)this + 8);
  
  if (animRec->magic != 0x6c) {
    (*(void (__cdecl **)(void))(*DAT_01205590 + 4))(); // error/assert handler
  }
  
  // Build actor ID from four 8-bit components stored as ints
  int actorID = ((animRec->byte1 * 0x100 + animRec->byte2) * 0x100 + animRec->byte3) * 0x100 + animRec->byte4;
  Actor *actor = this->findActorByID(actorID); // FUN_00599aa0
  
  if (actor == nullptr) {
    (*(void (__cdecl **)(int, const char *, const char *))(*DAT_01205590 + 8))
      (DAT_01205590, "ERROR : Sequence::actorPlayAnim : actor hasn't been created for %s",
       (const char *)this + 0x30);
    return;
  }
  
  // Call actor methods via vtable
  actor->playAnim(animRec->animParam);                           // vtable+0x2c
  actor->setAnimationParams(animRec->animParamsBlock,            // vtable+0x5c
                            animRec->flag != 0,                  // m_flag
                            animRec->paramC, 
                            animRec->paramD, 
                            animRec->paramE, 
                            animRec->paramF);
}