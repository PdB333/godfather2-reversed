// FUNC_NAME: CrewLeaderComponent::updateCrewMembers
void CrewLeaderComponent::updateCrewMembers(CrewMemberIterator* iterator)
{
  if (iterator == nullptr) return;

  IteratorState state; // stack locals for iterator state
  iterator->begin(&state); // vtable+0x1cc

  do {
    CrewMember* member = iterator->getNext(state); // vtable+500
    if (member != nullptr) {
      // Skip members that are already in the target crew (e.g., don't need reassignment)
      if (!shouldSkip(member)) { // FUN_00543050 returns 0 to indicate "no skip"
        // Get the crew leader's target manager (e.g., current mission target)
        int targetManager = getTargetManager(this->m_crewManager + 0x17c); // FUN_0072d1e0
        if (targetManager != 0) {
          member->assignToTarget(); // vtable+0x260
          // Mark the target manager as having an active assignment
          *(uint*)(targetManager + 0x1d0) |= 0x4000;
        }
      }
    }
  } while (iterator->hasMore(state)); // vtable+0x1d0
}