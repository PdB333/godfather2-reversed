// FUNC_NAME: GodfatherGameManager::setCurrentScenario
// Address: 0x007f8790
// Sets the current scenario ID and plays a sound if it changes.

void __thiscall GodfatherGameManager::setCurrentScenario(int newScenario)
{
    // Compare with current scenario stored at offset +0x1ef8
    if (newScenario != *(int *)(this + 0x1ef8))
    {
        // Call a method on a sub-object pointed to by +0x58
        // The sub-object's vtable+0x28 corresponds to a function taking a sound ID (0x80)
        (*(void (**)(int))(*(int *)(this + 0x58) + 0x28))(0x80);
        // Update the scenario ID
        *(int *)(this + 0x1ef8) = newScenario;
    }
}