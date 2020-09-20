#ifndef SOUNDGAME_H
#define SOUNDGAME_H

#include <android/asset_manager.h>

class SoundGame {
    public:
        explicit SoundGame(AAssetManager&);
        void start();
        void onSurfaceCreated();
        void onSurfaceChanged(int width, int height);
        void onSurfaceDestroy();
        void tap(int64_t eventTimeAsUpTime);
        void tick();

    private:
        AAssetManager& mAssetManager;
};
#endif