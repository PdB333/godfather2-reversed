// FUNC_NAME: AICharacter::resolveBehaviorPriority
int AICharacter::resolveBehaviorPriority() {
    char result;

    result = checkIsHostile(this);  // +0x? - test if character is hostile (e.g., target in combat)
    if (result != 0) {
        return 0; // Hostile priority
    }

    result = checkIsNeutral(this);  // +0x? - test if character is neutral (e.g., civilian)
    if (result != 0) {
        return 1; // Neutral priority
    }

    result = checkIsFriendly(this); // +0x? - test if character is friendly (e.g., family member)
    if (result != 0) {
        return 2; // Friendly priority
    }

    return 3; // Unknown/other priority
}