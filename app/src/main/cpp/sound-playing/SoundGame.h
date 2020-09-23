#ifndef SOUNDGAME_H
#define SOUNDGAME_H

#include <android/asset_manager.h>
#include <oboe/Oboe.h>
#include <future>
#include "Player.h"
#include "Mixer.h"
#include "LockFreeQueue.h"

using namespace oboe;

enum class GameState {
    Loading, Playing, FailedToLoad
};

class SoundGame : public AudioStreamCallback {
public:
    explicit SoundGame(AAssetManager &);

    void start();

    void stop();

    void load();

    void onSurfaceCreated();

    void onSurfaceChanged(int width, int height);

    void onSurfaceDestroy();

    void tap(int64_t eventTimeAsUpTime);

    void tick();

    bool setupAudioSources();

    bool openStream();

    DataCallbackResult
    onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

private:
    std::unique_ptr<Player> mClap;
    std::unique_ptr<Player> mBackingTrack;
    Mixer mixer;
    AAssetManager &mAssetManager;
    ManagedStream mAudioStream{nullptr};
    std::atomic<GameState> mGameState { GameState::Loading };
    std::future<void> mLoadingResult;

    LockFreeQueue<int64_t, 4> mClapEvents;
    std::atomic<int64_t> mCurrentFrame { 0 };
    std::atomic<int64_t> mSongPositionMs { 0 };
};

#endif