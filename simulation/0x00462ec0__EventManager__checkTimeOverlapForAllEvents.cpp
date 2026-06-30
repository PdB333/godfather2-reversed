// FUNC_NAME: EventManager::checkTimeOverlapForAllEvents
void EventManager::checkTimeOverlapForAllEvents(TimeRange* timeRange)
{
    // Iterate over group list (linked list at this+0x28)
    for (EventGroupNode* groupNode = *(EventGroupNode**)(this + 0x28); groupNode != nullptr; groupNode = groupNode->next)
    {
        // Each group node points to a list of event items (first event pointer, next field at +0x124)
        for (EventItem* eventItem = groupNode->firstEvent; eventItem != nullptr; eventItem = *(EventItem**)((int)eventItem + 0x124))
        {
            bool overlapping = false;

            // Check if eventItem's time range (at +0x60) overlaps with the given time range
            if (timeRange->startTime <= *(uint32_t*)(eventItem + 0x60) &&
                *(uint32_t*)(eventItem + 0x60) < timeRange->endTime)
            {
                *(uint32_t*)(eventItem + 0x138) |= 1;          // Set bit 0 as active
                overlapping = true;
            }

            int numSubEvents = FUN_00579170();                 // Get count of sub-events for this item (?)
            for (int idx = 0; idx < numSubEvents; idx++)
            {
                // Calculate index into sub-event array (circular buffer based on some sum)
                int sum = *(int*)(eventItem + 0x2e8) + *(int*)(eventItem + 0x2e4);
                int arrayLen = *(int*)(eventItem + 0x2e4);
                int index = (sum % arrayLen) - idx;             // Note: idx is subtracted, so it's like scanning backwards
                // Stride per sub-event element: 0xE0 bytes, time field at +0x60 within that
                uint32_t subTime = *(uint32_t*)(*(int*)(eventItem + 0x2ec) + index * 0xE0 + 0x60);
                if (timeRange->startTime <= subTime && subTime < timeRange->endTime)
                {
                    overlapping = true;
                    *(uint32_t*)(eventItem + 0x138) |= (4 << (idx & 0x1f));  // Set corresponding bit for this sub-event
                }
            }

            if (overlapping)
            {
                *(int*)(eventItem + 0x134) += 1;               // Increment overlap counter
            }
        }
    }
}