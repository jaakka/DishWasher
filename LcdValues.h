#ifndef IMAGES_H
#define IMAGES_H

// Text positions
enum TextPosition {
    CENTER_TOP = 0,
    CENTER_BOTTOM = 1
};

// Icon positions
enum LargeIconPosition {
    CENTER_ICON = 1
};

enum SmallIconPositionRightTop {

    // Right top circle icons
    RIGHT_TOP_ONE = 0,

    RIGHT_TOP_TWO_1 = 7,
    RIGHT_TOP_TWO_2 = 6,

    RIGHT_TOP_TREE_1 = 8,
    RIGHT_TOP_TREE_2 = 0,
    RIGHT_TOP_TREE_3 = 9,

    RIGHT_TOP_FOUR_1 = 10,
    RIGHT_TOP_FOUR_2 = 11,
    RIGHT_TOP_FOUR_3 = 12,
    RIGHT_TOP_FOUR_4 = 13

};

enum SmallIconPositionRightBottom {

    // Right bottom circle icons
    RIGHT_BOTTOM_ONE = 23,

    RIGHT_BOTTOM_TWO_1 = 25,
    RIGHT_BOTTOM_TWO_2 = 24,

    RIGHT_BOTTOM_TREE_1 = 27,
    RIGHT_BOTTOM_TREE_2 = 23,
    RIGHT_BOTTOM_TREE_3 = 26,

    RIGHT_BOTTOM_FOUR_1 = 28,
    RIGHT_BOTTOM_FOUR_2 = 29,
    RIGHT_BOTTOM_FOUR_3 = 30,
    RIGHT_BOTTOM_FOUR_4 = 31

};

enum SmallIconPositionLeftBottom {

    // Left bottom circle icons
    LEFT_BOTTOM_ONE = 32,

    LEFT_BOTTOM_TWO_1 = 33,
    LEFT_BOTTOM_TWO_2 = 34,

    LEFT_BOTTOM_TREE_1 = 36,
    LEFT_BOTTOM_TREE_2 = 32,
    LEFT_BOTTOM_TREE_3 = 35,

    LEFT_BOTTOM_FOUR_1 = 37,
    LEFT_BOTTOM_FOUR_2 = 38,
    LEFT_BOTTOM_FOUR_3 = 39,
    LEFT_BOTTOM_FOUR_4 = 40

};

enum SmallIconPositionLeftTop {

    // Left top circle icons
    LEFT_TOP_ONE = 0,

    LEFT_TOP_TWO_1 = 7,
    LEFT_TOP_TWO_2 = 6,

    LEFT_TOP_TREE_1 = 8,
    LEFT_TOP_TREE_2 = 0,
    LEFT_TOP_TREE_3 = 9,

    LEFT_TOP_FOUR_1 = 10,
    LEFT_TOP_FOUR_2 = 11,
    LEFT_TOP_FOUR_3 = 12,
    LEFT_TOP_FOUR_4 = 13

};

// Background image positions

enum BgImagePosition {
    RIGHT_TOP = 5,
    RIGHT_BOTTOM = 4,
    LEFT_BOTTOM = 3,
    LEFT_TOP = 2
};


// Background images

enum BgImageRightTop {

    // Circle right top
    EMPTY = 62,
    
    ONE = 60,
    ONE_SELECTED = 61,

    TWO = 48,
    TWO_1_SELECTED = 49,
    TWO_2_SELECTED = 50,

    THREE = 51,
    THREE_1_SELECTED = 52,
    THREE_2_SELECTED = 53,
    THREE_3_SELECTED = 54,

    FOUR = 55,
    FOUR_1_SELECTED = 56,
    FOUR_2_SELECTED = 57,
    FOUR_3_SELECTED = 58,
    FOUR_4_SELECTED = 59
};

enum BgImageRightBottom {

    // Circle right bottom
    EMPTY = 63,

    ONE = 46,
    ONE_SELECTED = 47,

    TWO = 34,
    TWO_1_SELECTED = 35,
    TWO_2_SELECTED = 36,

    THREE = 37,
    THREE_1_SELECTED = 38,
    THREE_2_SELECTED = 39,
    THREE_3_SELECTED = 40,

    FOUR = 41,
    FOUR_1_SELECTED = 42,
    FOUR_2_SELECTED = 43,
    FOUR_3_SELECTED = 44,
    FOUR_4_SELECTED = 45
};

enum BgImageLeftBottom {

    // Circle left bottom
    EMPTY = 64,

    ONE = 32,
    ONE_SELECTED = 33,

    TWO = 20,
    TWO_1_SELECTED = 21,
    TWO_2_SELECTED = 22,

    THREE = 23,
    THREE_1_SELECTED = 24,
    THREE_2_SELECTED = 25,
    THREE_3_SELECTED = 26,

    FOUR = 27,
    FOUR_1_SELECTED = 28,
    FOUR_2_SELECTED = 29,
    FOUR_3_SELECTED = 30,
    FOUR_4_SELECTED = 31
};

enum BgImageLeftTop {

    // Circle left top
    EMPTY = 65,

    ONE = 18,
    ONE_SELECTED = 19,

    TWO = 6,
    TWO_1_SELECTED = 7,
    TWO_2_SELECTED = 8,

    THREE = 9,
    THREE_1_SELECTED = 10,
    THREE_2_SELECTED = 11,
    THREE_3_SELECTED = 12,

    FOUR = 13,
    FOUR_1_SELECTED = 14,
    FOUR_2_SELECTED = 15,
    FOUR_3_SELECTED = 16,
    FOUR_4_SELECTED = 17

#endif