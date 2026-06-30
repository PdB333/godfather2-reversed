// FUNC_NAME: AudioManager::SetStreamOffsetFromPositions
void AudioManager::SetStreamOffsetFromPositions()
{
    int pos1 = GetStreamPosition(1); // Get position of stream 1
    int pos2 = GetStreamPosition(2); // Get position of stream 2
    SetStreamOffset(pos1 - pos2);    // Set offset based on difference
}