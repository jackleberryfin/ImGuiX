#pragma once

#include "Basic/ImTypeDefs.h"

// This extends ImGuiKeyData but only for named keys (legacy keys don't support the new features)
// Stored in main context (1 per named key). In the future it might be merged into ImGuiKeyData.
struct ImGuiKeyOwnerData
{
    ImGuiID OwnerCurr;
    ImGuiID OwnerNext;
    bool LockThisFrame;    // Reading this key requires explicit owner id (until end of frame). Set by ImGuiInputFlags_LockThisFrame.
    bool LockUntilRelease; // Reading this key requires explicit owner id (until key is released). Set by ImGuiInputFlags_LockUntilRelease. When this is true LockThisFrame is always true as well.

    ImGuiKeyOwnerData()
    {
        OwnerCurr = OwnerNext = ImGuiKeyOwner_NoOwner;
        LockThisFrame = LockUntilRelease = false;
    }
};