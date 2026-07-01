// FUNC_NAME: Player::getCrewComponentValue
int Player::getCrewComponentValue(Player *this) {
    // Call internal function that returns a pointer to a component (e.g., CrewComponent)
    CrewComponent *crew = (CrewComponent *) FUN_008ff210(this);
    if (crew != 0) {
        // Retrieve an integer property from the component (e.g., crew ID, score, etc.)
        return FUN_00980050(crew);
    }
    return 0;
}