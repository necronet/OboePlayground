#ifndef FFMPEG_NDKMEDIAEXTRACTOR_H
#define FFMPEG_NDKMEDIAEXTRACTOR_H

#include <cstdint>
#include <android/asset_manager.h>
#include "GameConstants.h"


class NDKExtractor {

public:
    static int32_t decode(AAsset *asset, uint8_t *targetData, AudioProperties targetProperties);
};


#endif