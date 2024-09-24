#pragma once

// [Internal] Storage used by IsKeyDown(), IsKeyPressed() etc functions.
// If prior to 1.87 you used io.KeysDownDuration[] (which was marked as internal), you should use GetKeyData(key)->DownDuration and *NOT* io.KeysData[key]->DownDuration.
struct ImGuiKeyData
{
    bool Down;              // True for if key is down
    float DownDuration;     // Duration the key has been down (<0.0f: not pressed, 0.0f: just pressed, >0.0f: time held)
    float DownDurationPrev; // Last frame duration the key has been down
    float AnalogValue;      // 0.0f..1.0f for gamepad values
};