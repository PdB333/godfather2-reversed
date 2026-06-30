// FUNC_NAME: NetworkManager::setMaxGhostCount
// Sets the maximum number of ghost objects (replicated via TNL) to 0x70 (112).
void __thiscall NetworkManager::setMaxGhostCount(int category)
{
    int maxGhostCount = 0x70; // +0x70 constant for ghost slot limit
    // Calls internal helper to set integer parameter by category.
    NetworkManager::setIntParameter(this, category, &maxGhostCount, 1);
}