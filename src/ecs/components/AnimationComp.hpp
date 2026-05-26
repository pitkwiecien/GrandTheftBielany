#pragma once

struct AnimationComp {
    int numFrames = 1;        // total frames in the sprite sheet
    int currentFrame = 0;     // which frame is currently displaying
    float frameTime = 0.1f;   // seconds each frame stays on screen
    float accumulator = 0.f;  // Internal timer
    
    int frameWidth = 0;       // width of a SINGLE frame (not the whole sheet)
    int frameHeight = 0;      // height of the frame
    
    bool isPlaying = false;   // whether the animation is currently ticking
};