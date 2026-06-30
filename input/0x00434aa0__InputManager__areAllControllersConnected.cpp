// FUNC_NAME: InputManager::areAllControllersConnected
// Checks if all controller slots in the range [startIndex, endIndex] are connected.
// Returns true if every slot is connected, false otherwise.
bool InputManager::areAllControllersConnected(uint startIndex, uint endIndex)
{
    bool result = true;
    if (startIndex <= endIndex)
    {
        do
        {
            bool current = this->isControllerConnected(startIndex);
            startIndex++;
            result = result && current;
        } while (startIndex <= endIndex);
    }
    return result;
}