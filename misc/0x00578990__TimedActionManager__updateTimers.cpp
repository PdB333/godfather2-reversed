// FUNC_NAME: TimedActionManager::updateTimers
// Function at 0x00578990: Updates a pool of timed actions, decrementing timers and triggering callbacks when expired.
// Iterates a circular buffer of timed actions (stride 0xE0 bytes). Each action has a remaining time (float at +0x1d*4),
// elapsed time (float at +0x1e*4), max duration (float at +0x1f*4), active flag (byte at +0x1c*4), and a flag at +0x20*4.
// Calls vtable method at offset 0x14 on each action if it should be processed; if no action has flag==1, calls it on this.

void TimedActionManager::updateTimers(float deltaTime)
{
    bool anyActiveWithFlag1 = false;
    int totalCount = this->getActiveCount();  // FUN_00579170
    int* previousItem = nullptr;
    int i = 0;
    
    if (totalCount > 0) {
        do {
            // Compute circular index: (currentIndex - i + capacity) % capacity
            int index = ((this->currentWriteIndex - i) + this->capacity) % this->capacity;
            int* item = this->itemArrayBase + index * (0xE0 / sizeof(int));  // 0xE0 bytes per item, stride in ints
            
            // Subtract deltaTime from remaining time (float at +0x1d)
            float remainingTime = reinterpret_cast<float&>(item[0x1d]);  // +0x74 (0x1d * 4)
            if (remainingTime > 0.0f) {
                remainingTime -= deltaTime;
                reinterpret_cast<float&>(item[0x1d]) = remainingTime;
            }
            
            if (remainingTime <= 0.0f) {
                // Compute new elapsed time (float at +0x1e)
                float& elapsedTime = reinterpret_cast<float&>(item[0x1e]);  // +0x78
                float newElapsed = elapsedTime + deltaTime - remainingTime;  // remainingTime is <=0, so subtract means add
                elapsedTime = newElapsed;
                item[0x1d] = 0;  // remaining time set to 0
                
                // Check if elapsed exceeded max duration (float at +0x1f)
                float maxDuration = reinterpret_cast<float&>(item[0x1f]);  // +0x7C
                if (newElapsed >= maxDuration) {
                    elapsedTime = maxDuration;
                    *reinterpret_cast<uint8_t*>(&item[0x1c]) = 0;  // clear active flag at +0x70
                }
            }
            
            // Check active flag (byte at +0x1c)
            if (*reinterpret_cast<uint8_t*>(&item[0x1c]) == 0) {
                break;  // stop iterating if this item is inactive
            }
            
            // Decide whether to call the action's process method
            bool shouldCall = false;
            if (previousItem == nullptr) {
                if (item[0x20] == 1) {  // flag at +0x80
                    anyActiveWithFlag1 = true;
                }
                shouldCall = true;
            } else {
                uint8_t prevActive = *reinterpret_cast<uint8_t*>(&previousItem[0x1c]);
                int prevFlag = previousItem[0x20];
                if (prevActive != 0 && prevFlag == 1) {
                    // Skip calling this item's method because previous item still has priority
                } else {
                    shouldCall = true;
                }
            }
            
            if (shouldCall) {
                // Call vtable method at offset 0x14 on the item
                // The item's first word is its vtable pointer
                void* vtable = reinterpret_cast<void**>(item)[0];
                typedef void (__thiscall* FuncType)(void*);
                FuncType method = reinterpret_cast<FuncType>(reinterpret_cast<int*>(vtable)[0x14 / 4]);
                method(item);
            }
            
            i++;
            previousItem = item;
        } while (i < totalCount);
    }
    
    if (!anyActiveWithFlag1) {
        // Fallback: call the same vtable method on 'this' object
        void* vtable = reinterpret_cast<void**>(this)[0];
        typedef void (__thiscall* FuncType)(void*);
        FuncType method = reinterpret_cast<FuncType>(reinterpret_cast<int*>(vtable)[0x14 / 4]);
        method(this);
    }
}