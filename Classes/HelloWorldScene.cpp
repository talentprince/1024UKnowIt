#include "HelloWorldScene.h"
#include "CardSprite.h"

USING_NS_CC;

//CC: double of CARD_PADDING
static int UNIT_MARGIN = 30;

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

    //CC: set bg
    this->addChild(LayerColor::create(Color4B(180, 170, 160, 255)));

    //CC: create card
    createCardSprite(Director::getInstance()->getVisibleSize());

    return true;
}

void HelloWorld::createCardSprite(cocos2d::Size size) {
    //calculate unit w and h
    int unitSize = (size.height - UNIT_MARGIN)/4;
    //calculate margin left
    int marginLeft = (abs(size.width - size.height + UNIT_MARGIN))/2;
    //create card for each unit
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            CardSprite* card = CardSprite::createCardSprite(8, unitSize, unitSize, unitSize * i + marginLeft, unitSize * j + UNIT_MARGIN);
            this->addChild(card);
            cards[i][j] = card;
        }
    }
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
    bool move = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            for (int right = x + 1; right < 4; right++) {
                //right has card
                if(cards[right][y]->getNumber() > 0) {
                    //target no card
                    if(cards[x][y]->getNumber() <= 0) {
                        //set it with
                        cards[x][y]->setNumber(cards[right][y]->getNumber());
                        cards[right][y]->setNumber(0);
                        //reset target
                        x--;
                        move = true;
                    } else if(cards[x][y]->getNumber() == cards[right][y]->getNumber()){
                        //the same, combine
                        cards[x][y]->setNumber(cards[x][y]->getNumber() * 2);
                        cards[right][y]->setNumber(0);
                        move = true;
                    }
                    //one move one merge
                    break;
                }
            }
        }
    }
    return move;
}

bool HelloWorld::doRight() {
    bool move = false;
    for (int y = 0; y < 4; y++) {
       for (int x = 3; x >= 0; x--) {
            for (int left = x - 1; left >= 0; left--) {
                //left has card
                if(cards[left][y]->getNumber() > 0) {
                    //target no card
                    if(cards[x][y]->getNumber() <= 0) {
                        //set it with
                        cards[x][y]->setNumber(cards[left][y]->getNumber());
                        cards[left][y]->setNumber(0);
                        //reset target
                        x++;
                        move = true;
                    } else if(cards[x][y]->getNumber() == cards[left][y]->getNumber()){
                        //the same, combine
                        cards[x][y]->setNumber(cards[x][y]->getNumber() * 2);
                        cards[left][y]->setNumber(0);
                        move = true;
                    }
                    //one move one merge
                    break;
                }
            }
        }
    }
    return move;
}

bool HelloWorld::doUp() {
    bool move = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 3; y > 0; y--) {
            for (int below = y - 1; below >= 0; below--) {
                //has card below
                if(cards[x][below]->getNumber() > 0) {
                    //target no card
                    if(cards[x][y]->getNumber() <= 0) {
                        //set it with
                        cards[x][y]->setNumber(cards[x][below]->getNumber());
                        cards[x][below]->setNumber(0);
                        //reset target
                        y++;
                        move = true;
                    } else if(cards[x][y]->getNumber() == cards[x][below]->getNumber()){
                        //the same, combine
                        cards[x][y]->setNumber(cards[x][y]->getNumber() * 2);
                        cards[x][below]->setNumber(0);
                        move = true;
                    }
                    //one move one merge
                    break;
                }
            }
        }
    }
    return move;
}

bool HelloWorld::doDown() {
    bool move = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            for (int above = y + 1; above < 4; above++) {
                //has card above
                if(cards[x][above]->getNumber() > 0) {
                    //target no card
                    if(cards[x][y]->getNumber() <= 0) {
                        //set it with
                        cards[x][y]->setNumber(cards[x][above]->getNumber());
                        cards[x][above]->setNumber(0);
                        //reset target
                        y--;
                        move = true;
                    } else if(cards[x][y]->getNumber() == cards[x][above]->getNumber()){
                        //the same, combine
                        cards[x][y]->setNumber(cards[x][y]->getNumber() * 2);
                        cards[x][above]->setNumber(0);
                        move = true;
                    }
                    //one move one merge
                    break;
                }
            }
        }
    }
    return move;
}
