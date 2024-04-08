#include "MySlider.h"


USING_NS_CC;

INITIALIZE_READER(MySlider);

std::once_flag _main_MySlider;//4.

MySlider* MySlider::createView()
{
    std::call_once(_main_MySlider, []
        {
            REGISTER_CSB_READER(MySlider);
        });

    auto view = reinterpret_cast<MySlider*>(CSLoader::createNode("csb/ui/Level/MySlider.csb"));

    if (view)
    {
        view->didLoadFromCSB();
        return view;
    }

    CC_SAFE_DELETE(view);

    return nullptr;
}

void MySlider::didLoadFromCSB()
{
    _sliderRight = utils::findChild<Slider*>(this, "s_r");
    _sliderLeft = utils::findChild<Slider*>(this, "s_l");
    _sliderDown = utils::findChild<Slider*>(this, "s_d");
    _sliderUp = utils::findChild<Slider*>(this, "s_u");

    _sliderRight->setZoomScale(0.0f);
    _sliderLeft->setZoomScale(0.0f);
    _sliderDown->setZoomScale(0.0f);
    _sliderUp->setZoomScale(0.0f);

}

void MySlider::SetSizeForSlideBar(Size mapSize)
{
    float m = 120;
    auto point = this->getPosition() - Vec2(40, 0);
    this->setPosition(point);
    _sliderRight->setContentSize(Size(mapSize.width - point.x - m, 80));
    _sliderLeft->setContentSize(Size(point.x - m, 80));
    _sliderDown->setContentSize(Size(point.y - m, 80));
    _sliderUp->setContentSize(Size(mapSize.height - point.y - m, 80));

}

ui::Widget::ccWidgetTouchCallback MySlider::onLocateTouchCallback(const std::string& callback_name) {

    if (callback_name == "onTouch")
    {
        return CC_CALLBACK_2(MySlider::onTouch, this);
    }

    return nullptr;
}

void MySlider::onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType event_type) {

    auto obj = static_cast<ui::Widget*>(sender);

    bool isSucess = false;


    switch (event_type)
    {
    case ui::Widget::TouchEventType::BEGAN:
    {
        // obj->setScale(1.0f);
        _startTouchPos = obj->getTouchMovePosition();
        break;
    }

    case ui::Widget::TouchEventType::MOVED:
    {
        Vec2 currentTouchPos = obj->getTouchMovePosition();
        float deltaX = currentTouchPos.x - _startTouchPos.x;
        float deltaY = currentTouchPos.y - _startTouchPos.y;

        CCLOG("point_x:%f, y:%f", currentTouchPos.x, currentTouchPos.y);

        auto distance = currentTouchPos.distance(_startTouchPos);

        if (_sliderCurret != nullptr)
        {
            OnSetPersentSlider(_sliderLeft, distance);
            return;
        }

        if (abs(deltaX) > abs(deltaY)) {
            if (deltaX > 0) {
                _currentTypeMove = TypeMove::LEFT;
                OnSetPersentSlider(_sliderLeft, distance);

            }
            else {
                _currentTypeMove = TypeMove::RIGHT;
                OnSetPersentSlider(_sliderRight, distance);
            }
        }
        else {
            if (deltaY > 0) {
                _currentTypeMove = TypeMove::UP;
                OnSetPersentSlider(_sliderUp, distance);

            }
            else {
                _currentTypeMove = TypeMove::DOWN;
                OnSetPersentSlider(_sliderDown, distance);

            }
        }

        break;
    }
    case ui::Widget::TouchEventType::ENDED:
        _sliderCurret = nullptr;
        break;

    case ui::Widget::TouchEventType::CANCELED:
    {
        _sliderCurret = nullptr;

        break;
    }
    default:
        break;
    }
}

void MySlider::OnSetPersentSlider(Slider* sl, float distance)
{
    _sliderCurret = sl;
    auto total = std::abs(sl->getContentSize().width);
    auto ratio = distance / total;
    if (ratio > (80.0f / sl->getContentSize().width))
    {
       // sl->setTouchEnabled(true);
    }
    sl->setPercent(ratio * 100.0f);
}
