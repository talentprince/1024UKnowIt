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

    //CC: visible size
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //CC: add score label
    auto scoreLabelName = LabelTTF::create("SCORE", "HiraKakuProN-W6", 80);
    scoreLabelName->setPosition(Point(visibleSize.width/3, visibleSize.height - UNIT_MARGIN));
    this->addChild(scoreLabelName);
    scoreLabel = LabelTTF::create("0", "HiraKakuProN-W6", 80);
    scoreLabel->setPosition(Point(visibleSize.width/3 + scoreLabelName->getBoundingBox().size.width + UNIT_MARGIN, visibleSize.height - UNIT_MARGIN));
    this->addChild(scoreLabel);

    //CC: create card
    createCardSprite(visibleSize, scoreLabelName->getBoundingBox().size.height);

    //CC: generate card
    autoBirth();
    autoBirth();

    return true;
}

void HelloWorld::createCardSprite(cocos2d::Size size, int labelHeight) {
    //calculate unit w and h
    int unitSize = (size.height - labelHeight)/4;
    //calculate margin left
    int marginLeft = (abs(size.width - size.height + labelHeight))/2;
    //create card for each unit
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            CardSprite* card = CardSprite::createCardSprite(0, unitSize, unitSize, unitSize * i + marginLeft, unitSize * j + UNIT_MARGIN);
            this->addChild(card);
            cards[i][j] = card;
        }
    }
}

void HelloWorld::gotScore(int score) {
    this->score += score;
    scoreLabel->setString(String::createWithFormat("%i", this->score)->getCString());
}

void HelloWorld::autoBirth() {
    int i = CCRANDOM_0_1() * 4;
    int j = CCRANDOM_0_1() * 4;
    //if already has birth again
    if(cards[i][j]->getNumber() > 0) {
        autoBirth();
    } else {
        cards[i][j]->setNumber(CCRANDOM_0_1() < 1 ? 2 : 4);
    }
}

void HelloWorld::checkOver() {
    bool over = true;
    for (int y = 0; y < 4 && over; y++) {
        for(int x = 0; x < 4 && over; x++)
            if(cards[x][y]->getNumber() == 0 ||
               (x>0 && cards[x][y]->getNumber() == cards[x-1][y]->getNumber())||
               (x<3 && cards[x][y]->getNumber() == cards[x+1][y]->getNumber())||
               (y>0 && cards[x][y]->getNumber() == cards[x][y-1]->getNumber())||
               (y<3 && cards[x][y]->getNumber() == cards[x][y+1]->getNumber())) {
                over = false;
            }
        }
    if(over) {
        Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
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
    //CC: move?
    bool move = false;

    //CC: figure direction
    if (abs(endX) > abs(endY)) {
        if(endX > 0)
            move = doLeft();
        else
            move = doRight();
    } else {
        if(endY > 0)
            move = doDown();
        else
            move= doUp();
    }
    //CC: if moved, birth one card and check over
    if(move){
        autoBirth();
        checkOver();
    }
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    //CC: move?
    bool move = false;
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
            move = doLeft();
            break;
        }
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
            move = doRight();
            break;
        }
        case EventKeyboard::KeyCode::KEY_UP_ARROW: {
            move = doUp();
            break;
        }
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
            move = doDown();
            break;
        }
        default:
            break;
    }
    //CC: if moved, birth one card and check over
    if(move){
        autoBirth();
        checkOver();
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
                        //score!!!!
                        gotScore(cards[x][y]->getNumber());
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
                        //score!!!!
                        gotScore(cards[x][y]->getNumber());
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
                        //score!!!!
                        gotScore(cards[x][y]->getNumber());
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
                        //score!!!!
                        gotScore(cards[x][y]->getNumber());
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
