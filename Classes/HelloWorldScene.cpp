#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    //CC: bind touch listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    //CC: bind keyboard listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    //CC: get beginning touch point
    auto touchPoint = touch->getLocation();
    beginX = touchPoint.x;
    beginY = touchPoint.y;
    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    //CC: get move direction
    auto touchPoint = touch->getLocation();
    endX = beginX - touchPoint.x;
    endY = beginY - touchPoint.y;

    //CC: figure direction
    if (abs(endX) > abs(endY)) {
        if(endX > 0)
            doLeft();
        else
            doRight();
    } else {
        if(endY > 0)
            doDown();
        else
            doUp();
    }
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
            doLeft();
            break;
        }
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
            doRight();
            break;
        }
        case EventKeyboard::KeyCode::KEY_UP_ARROW: {
            doUp();
            break;
        }
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
            doDown();
            break;
        }
        default:
            break;
    }
}

bool HelloWorld::doLeft() {
    log("touch left");
    return true;
}

bool HelloWorld::doRight() {
    log("touch right");
    return true;
}

bool HelloWorld::doUp() {
    log("touch up");
    return true;
}

bool HelloWorld::doDown() {
    log("touch down");
    return true;
}
