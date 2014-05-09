//
//  CardSprite.cpp
//  1024UKnowIt
//
//  Created by chenchen on 14-5-9.
//
//

#include "CardSprite.h"
using namespace cocos2d;

CardSprite* CardSprite::createCardSprite(int number, int width, int height, float cardX, float cardY) {
    auto birthCard = new CardSprite();
    //CC: custom static create()
    if(birthCard && birthCard->init()) {
        birthCard->autorelease();
        birthCard->birthCardInit(number, width, height, cardX, cardY);
        return  birthCard;
    }
    //CC: inital failed
    CC_SAFE_DELETE(birthCard);
    return NULL;
}

bool CardSprite::init() {
    //CC: super init
    if(!Sprite::init()) {
        return false;
    }
    return true;
}

void CardSprite::birthCardInit(int number, int width, int height, float cardX, float cardY) {
    //CC: initial number
    this->number = number;

    //CC: create background
    layerBG = LayerColor::create(Color4B(200, 190, 180, 255), width - 15, height - 15);
    layerBG->setPosition(Point(cardX, cardY));

    //CC: add label to bg
    if(number>0) {
        numberLabel = LabelTTF::create(String::createWithFormat("%i", number)->getCString(), "HiraKakuProN-W6", 100);
    } else {
        numberLabel = LabelTTF::create("", "HiraKakuProN-W6", 100);
    }
    numberLabel->setPosition(Point(layerBG->getContentSize().width/2, layerBG->getContentSize().height/2));
    numberLabel->setTag(8);
    layerBG->addChild(numberLabel);

    //CC:add card
    this->addChild(layerBG);
}

int CardSprite::getNumber() {
    return number;
}

void CardSprite::setNumber(int number) {
    this->number = number;

    if(number > 0) {
        numberLabel->setString(String::createWithFormat("%i", number)->getCString());
    } else {
        numberLabel->setString("");
    }
}
