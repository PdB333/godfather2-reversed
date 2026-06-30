// FUNC_NAME: DistrictManager::generateDistrictSpawns
// Function address: 0x00589360
// This function generates spawn points (buildings, vehicles, npcs) in a district.
// The generation state is stored in an internal struct (pointed by ESI/this):
//   +0x00: currentIndex - index into global spawn tables (e.g., for building templates)
//   +0x04: stepCounter - accumulated step amount (used for some spatial distribution)
//   +0x0C: generatedCount - number of spawn entries generated so far
// param_1: pointer to an array of 16-byte spawn data records (e.g., spawn locations)
// param_2: start index (inclusive) for generation range
// param_3: end index (exclusive) for generation range

void DistrictManager::generateDistrictSpawns(void* spawnDataArray, int startIndex, int endIndex)
{
    int generatedCount = this->generatedCount;
    uint randomVal;
    uint branch;

    // Fast-forward generation to reach startIndex without modifying spawn data array
    while (generatedCount < startIndex)
    {
        generatedCount = this->generatedCount;
        randomVal = getRandomUlonglong() >> 32;  // extract upper 32 bits for pseudo-random
        branch = randomVal & 3;
        if (branch - 1 < 3)   // branches 1,2,3 – increment index by 1
        {
            this->currentIndex += 1;
        }
        else                  // branch 0 – increment index by 3
        {
            this->currentIndex += 3;
        }
        this->stepCounter += 6;
        generatedCount++;
        this->generatedCount = generatedCount;
    }

    // Actual generation for indices [startIndex, endIndex)
    generatedCount = this->generatedCount;
    while (true)
    {
        if (endIndex <= generatedCount)
        {
            return;
        }
        randomVal = getRandomUlonglong() >> 32;
        branch = randomVal & 3;
        if (branch == 1)
        {
            // Spawn type A (e.g., a building)
            spawnBuildingTypeA(this->currentIndex);
            this->currentIndex += 1;
        }
        else if (branch == 2)
        {
            // Spawn type B (e.g., a vehicle)
            spawnVehicleTypeB(this->currentIndex);
            this->currentIndex += 1;
        }
        else if (branch == 3)
        {
            // Spawn type C (e.g., an NPC)
            spawnNPCTypeC(this->currentIndex);
            this->currentIndex += 1;
        }
        else  // branch == 0
        {
            // Spawn a large item (e.g., a compound) that uses 3 index slots
            spawnLargeItem(spawnDataArray);
            this->currentIndex += 3;
        }
        this->stepCounter += 6;
        this->generatedCount = generatedCount + 1;
        spawnDataArray = (char*)spawnDataArray + 0x10;  // advance to next spawn record
        generatedCount = this->generatedCount;
    }
}