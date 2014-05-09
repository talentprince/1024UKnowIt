//
//  CardSprite.h
//  1024UKnowIt
//
//  Created by chenchen on 14-5-9.
//
//

#ifndef __CardSprite__
#define __CardSprite__

#include "cocos2d.h"

class CardSprite : public cocos2d::Sprite {
public:
    //CC: initial card with number width height x and y
    static CardSprite* createCardSprite(int number, int width, int height, float cardX, float cardY);

    //CC: implement of static create
    virtual bool init();
    CREATE_FUNC(CardSprite);

    //CC: set and get of number
    int getNumber();
    void setNumber(int number);
    
private:
    //CC: number
    int number;
    void birthCardInit(int number, int width, int height, float cardX, float cardY);
    //CC: number label
    cocos2d::LabelTTF* numberLabel;
    //CC: card background
    cocos2d::LayerColor* layerBG;
};

#endif /* defined(__CardSprite__) */
