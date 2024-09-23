#pragma once

#include "ImTypeDefs.h"

// [Internal] Key+Value for ImGuiStorage
struct ImGuiStoragePair
{
    ImGuiID key;
    union
    {
        int val_i;
        float val_f;
        void *val_p;
    };
    ImGuiStoragePair(ImGuiID _key, int _val)
    {
        key = _key;
        val_i = _val;
    }
    ImGuiStoragePair(ImGuiID _key, float _val)
    {
        key = _key;
        val_f = _val;
    }
    ImGuiStoragePair(ImGuiID _key, void *_val)
    {
        key = _key;
        val_p = _val;
    }
};