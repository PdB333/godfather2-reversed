// FUNC_NAME: Player::getReputation

bool __thiscall Player::getReputation(float &outReputation) {
    PlayerReputationTracker* tracker = reinterpret_cast<PlayerReputationTracker*>(this->getReputationTracker());
    if (tracker != nullptr) {
        float rep = tracker->reputation; // +0x280: reputation value
        outReputation = rep;
        // Global constants defining the valid reputation range
        if (rep >= kMinReputation && rep <= kMaxReputation) {
            return true;
        }
    }
    return false;
}