#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class CardSprite;

class GameWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameWorld);

    //CC: touch and keyboard event listener
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //CC: move function
    bool doUp();
    bool doDown();
    bool doLeft();
    bool doRight();

private:
    //CC: touch point
    int beginX, beginY, endX, endY;
    //CC: create card
    void createCardSprite(cocos2d::Size size, int labelHeight);
    //CC: auto birth
    void autoBirth();
    //CC: check over
    void checkOver();

    //CC: card save
    CardSprite* cards[4][4];
    //CC: score and score label
    int score;
    cocos2d::LabelTTF* scoreLabel;
    void gotScore(int score);
};

#endif // __HELLOWORLD_SCENE_H__
