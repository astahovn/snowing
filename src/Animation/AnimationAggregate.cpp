#include "AnimationAggregate.h"

AnimationAggregate::~AnimationAggregate() {
    for (auto & animation : animations) {
        delete animation;
    }
    animations.clear();
}

void AnimationAggregate::init() {
    for (auto & animation : animations) {
        animation->init();
    }
}

int AnimationAggregate::computing() {
    for (auto & animation : animations) {
        if (IAnimation::COMPUTING_END == animation->computing()) {
            return IAnimation::COMPUTING_END;
        }
    }
    return IAnimation::COMPUTING_OK;
}

void AnimationAggregate::render(float globalFading) const {
    for (auto & animation : animations) {
        animation->render(globalFading);
    }
}

void AnimationAggregate::processKeys(const bool *keys) {
    for (auto & animation : animations) {
        animation->processKeys(keys);
    }
}

void AnimationAggregate::addAnimation(IAnimation * animation) {
    animations.push_back(animation);
}
