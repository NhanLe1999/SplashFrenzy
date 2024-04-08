#include "CaculateQuickLevelLayer.h"
#include "CaculateQuickCocostudioMacro.h"
#include "CaculateQuickHelperManager.h"
#include "CaculateQuickSoundManager.h"
#include "CaculateQuickGameScene.h"

USING_NS_CC;

Scene *CaculateQuickLevelLayer::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = CaculateQuickLevelLayer::create();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }

    return scene;
}

CaculateQuickLevelLayer* CaculateQuickLevelLayer::createView()
{
    return CaculateQuickLevelLayer::create();
}

bool CaculateQuickLevelLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CaculateQuickHelperManager::GetInstance()->addLockLayer(this);

    ////////////////////////////////////////////////////////////////////////////////////

    Sprite *background = Sprite::create("CaculateQuick/Popup/Select_level.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //background->setContentSize(Size(1118, 798) * 0.85f);
    this->addChild(background);
    background->setScale(0.7f);

    auto backgroundSize = background->getContentSize();

    auto listView = ListView::create();
    listView->setContentSize(Size(backgroundSize.width * 0.86, backgroundSize.height * 0.75));
    listView->setPosition(Vec2(backgroundSize.width * 0.50, backgroundSize.height * 0.45));
    listView->setAnchorPoint(Point(0.5, 0.5));
    background->addChild(listView);
    listView->setScrollBarEnabled(true);
    listView->setScrollBarAutoHideTime(true);
    listView->setScrollBarColor(Color3B(204, 115, 33));
    listView->setLeftPadding(48);
    //listView->setItemsMargin(5);
    //listView->setBottomPadding(5);

    auto index = 0;

    auto levelId = UserDefault::getInstance()->getIntegerForKey("key_current_level_save", 0);
    // levelId = 10;

    for (int j = 0; j < 50; j++)
    {
        auto Item = ListView::create();
        Item->setDirection(ScrollView::Direction::HORIZONTAL);
        Item->setTouchEnabled(false);

        Item->setContentSize(Size(listView->getContentSize().width, listView->getContentSize().height * 0.33333));
        Item->setItemsMargin(70);
        Item->setScrollBarEnabled(false);

        for (int i = 0; i < 5; i++)
        {
            std::string path ="CaculateQuick/Popup/iconstar-%d.png";

            int num_start = UserDefault::getInstance()->getIntegerForKey(cocos2d::StringUtils::format(KEY_STAR_LEVEL, index).c_str(), 0);

            int n = num_start == 0 ? 2 : 1;

            auto pathItemStar = cocos2d::StringUtils::format(path.c_str(), n);

            ImageView* img = ImageView::create();
            img->setTag(index);
            img->setContentSize(Size(Item->getContentSize().height, Item->getContentSize().height));
            img->setName(std::to_string(index));
            Item->pushBackCustomItem(img);
            img->addClickEventListener([=](Ref* sender)
                {
                    auto node = dynamic_cast<Node*>(sender);
                    if (node->getTag() >= levelId)
                    {
                        UserDefault::getInstance()->setIntegerForKey(KEY_SAVE_LEVEL, node->getTag());
                    }
                    UserDefault::getInstance()->setIntegerForKey(KEY_CURENT_LEVEL, node->getTag() + 1);
                    SOUND_MANAGER->playClickEffect();
                    Director::getInstance()->replaceScene(TransitionFade::create(0.3f, CaculateQuickGameScene::createScene()));
                    CCLOG("%d____index", node->getTag()); });

            if (index <= levelId)
            {
                img->loadTexture("CaculateQuick/Popup/bgr-level-on.png");
                img->setTouchEnabled(true);
            }
            else
            {
                img->setTouchEnabled(false);
                img->loadTexture("CaculateQuick/Popup/bgr-level-off.png");
            }

            ImageView* img1 = ImageView::create(pathItemStar);
            img1->setAnchorPoint(Vec2(0.5f, 0));
            img1->setPosition(Vec2(img->getContentSize().width / 2, 20));
            img->addChild(img1);

            
            auto levelId = ui::Text::create(std::to_string(index + 1), "fonts/GROBOLD.ttf", 40);
            levelId->setPosition(Vec2(img->getContentSize() / 2));
            img->addChild(levelId);
            levelId->setColor(Color3B::WHITE);


            index++;
        }

        listView->pushBackCustomItem(Item);
    }

    auto backButton = cocos2d::ui::Button::create("CaculateQuick/Popup/btn_close.png", "CaculateQuick/Popup/btn_close.png", "CaculateQuick/Popup/btn_close.png", TextureResType::LOCAL);
    backButton->setPosition(Vec2(visibleSize.width * 0.97, visibleSize.height * 0.90));
    backButton->setAnchorPoint(Vec2(1.0f, 0.5f));
    backButton->setPressedActionEnabled(true);
    backButton->setScale(0.75f);
    backButton->addClickEventListener([=](Ref *sender)
                                      {
                                          SOUND_MANAGER->playClickEffect();
    
                                          this->removeFromParent(); });
    this->addChild(backButton, 1000);

    return true;
}
