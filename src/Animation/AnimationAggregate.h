#ifndef SNOWING_ANIMATIONAGGREGATE_H
#define SNOWING_ANIMATIONAGGREGATE_H

#include <vector>
#include "IAnimation.h"

class AnimationAggregate : public IAnimation {
public:
    ~AnimationAggregate() override;

    void init() override;
    int computing() override;
    void render(float globalFading) const override;
    void processKeys(const bool keys[]) override;

    void addAnimation(IAnimation * animation);

private:
    std::vector<IAnimation *> animations{};
};


#endif
