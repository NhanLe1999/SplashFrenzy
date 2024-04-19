#include "cocos2d.h"

using namespace cocos2d;

class CircularMove : public cocos2d::ActionInterval
{
public:
    static CircularMove* create(float duration, const cocos2d::Vec2& center, float radius)
    {
        CircularMove *ret = new (std::nothrow) CircularMove();
        if (ret && ret->initWithDuration(duration, center, radius))
        {
            ret->autorelease();
            return ret;
        }
        else
        {
            delete ret;
            return nullptr;
        }
    }

    bool initWithDuration(float duration, const cocos2d::Vec2& center, float radius)
    {
        if (ActionInterval::initWithDuration(duration))
        {
            _center = center;
            _radius = radius;
            return true;
        }
        return false;
    }

    void SetSpr(Sprite* spr) {
        _spr = spr;
    }

    void update(float time) override
    {
        if (_target)
        {
            float angle = 2 * M_PI * time;
            float x = _center.x + _radius * cos(angle);
            float y = _center.y + _radius * sin(angle);
            _target->setPosition(Vec2(x, y));

         _spr->getPhysicsBody()->setVelocity(Vec2(x, y) * 0.25f);

        }
      
    }

    void SetSpeed()
    {
       // _spr->getPhysicsBody()->setVelocity(Vec2(-_radius * M_PI, 0));
    }

protected:
    cocos2d::Vec2 _center;
    Sprite* _spr = nullptr;
    float _radius;
};
