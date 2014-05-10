//
//  CardSprite.cpp
//  1024UKnowIt
//
//  Created by chenchen on 14-5-9.
//
//

#include "CardSprite.h"
USING_NS_CC;

static int CARD_PADDING = 15;

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
    layerBG = LayerColor::create(Color4B(200, 190, 180, 255), width - CARD_PADDING, height - CARD_PADDING);
    layerBG->setPosition(Point(cardX, cardY));

    //CC: add label to bg
    numberLabel = LabelTTF::create("", "HiraKakuProN-W6", 100);
    numberLabel->setColor(Color3B::BLACK);
    if(number>0)
        setNumber(number);

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

    //CC: small font big score
    if(number >= 1024){
        numberLabel->setFontSize(55);
    }else if(number >= 128){
        numberLabel->setFontSize(70);
    }else if (number >= 16) {
        numberLabel->setFontSize(90);
    }else{
		numberLabel->setFontSize(100);
    }

    //CC: different bg
    switch (number) {
        case 0:
            layerBG->setColor(Color3B(200,190,180));
            break;
        case 2:
            layerBG->setColor(Color3B(240,230,220));
            break;
        case 4:
            layerBG->setColor(Color3B(240,220,200));
            break;
        case 8:
            layerBG->setColor(Color3B(240,180,120));
            break;
        case 16:
            layerBG->setColor(Color3B(240,140,90));
            break;
        case 32:
            layerBG->setColor(Color3B(240,120,90));
            break;
        case 64:
            layerBG->setColor(Color3B(240,90,60));
            break;
        case 128:
            layerBG->setColor(Color3B(240,90,60));
            break;
        case 256:
            layerBG->setColor(Color3B(240,200,70));
            break;
        case 512:
            layerBG->setColor(Color3B(240,200,70));
            break;
        case 1024:
            layerBG->setColor(Color3B(0,130,0));
            break;
        case 2048:
            layerBG->setColor(Color3B(0,130,0));
            break;
        default:
            layerBG->setColor(Color3B(0,130,0));
            break;
    }

    if(number > 0) {
        numberLabel->setString(String::createWithFormat("%i", number)->getCString());
    } else {
        numberLabel->setString("");
    }
}
