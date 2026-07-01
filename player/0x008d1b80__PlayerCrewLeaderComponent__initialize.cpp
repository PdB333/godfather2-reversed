// FUNC_NAME: PlayerCrewLeaderComponent::initialize

void __fastcall PlayerCrewLeaderComponent::initialize(PlayerCrewLeaderComponent* this) {
    // Initialize four crew member slots (sub-objects or arrays)
    this->initCrewMemberSlot();
    this->initCrewMemberSlot();
    this->initCrewMemberSlot();
    this->initCrewMemberSlot();
    // +0x78: reset active crew count to zero
    this->m_activeCrewCount = 0;
}