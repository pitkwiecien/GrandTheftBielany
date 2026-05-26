#include "systems/AnimationSystem.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/SpriteComp.hpp"
#include "ecs/components/AnimationComp.hpp"

void AnimationSystem::update(Registry& reg, float dt) {
    reg.view<AnimationComp, SpriteComp>(
        [&](Entity e, AnimationComp& anim, SpriteComp& sprite) 
    {
        // don't animate if stopped
        if (!anim.isPlaying) {
            anim.currentFrame = 0;
        } else {
            anim.accumulator += dt;
            if (anim.accumulator >= anim.frameTime) {
                anim.accumulator -= anim.frameTime;
                
                anim.currentFrame = (anim.currentFrame + 1) % anim.numFrames;
            }
        }

        sprite.srcRect.x = anim.currentFrame * anim.frameWidth;
        sprite.srcRect.y = 0; 
        sprite.srcRect.w = anim.frameWidth;
        sprite.srcRect.h = anim.frameHeight;
    });
}