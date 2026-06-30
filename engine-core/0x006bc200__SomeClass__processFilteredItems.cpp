// FUNC_NAME: SomeClass::processFilteredItems
void __thiscall SomeClass::processFilteredItems(void* param_2) {
    // param_2 is likely a container or data source
    DataIterator::init(param_2);
    // 0xe6a05c33 is probably a hash identifying a specific filter/subset
    DataIterator::setFilter(param_2, 0xe6a05c33);

    while (DataIterator::hasNext()) {
        int itemType = DataIterator::getCurrentType(); // Returns 0 or 1
        if (itemType == 0) {
            // Get the actual data pointer for this iteration
            void* dataPtr = DataIterator::getCurrentData();
            // Store value at offset +0x8 of the data into this+0x184
            // This overwrites any previous value (last one wins)
            *(void**)(this + 0x184) = *(void**)((char*)dataPtr + 8);
        } else if (itemType == 1) {
            // For type 1, we skip the data pointer and instead get a value
            DataIterator::getCurrentData(); // Called but result ignored (maybe advances internal state)
            uint32 value = DataIterator::getCurrentValue();
            // Append value to an array/list at this+0x188
            // FUN_004089b0 appears to be a push_back or add operation
            ArrayPushBack((void**)(this + 0x188), (void*)value);
        }
        DataIterator::advance();
    }
}