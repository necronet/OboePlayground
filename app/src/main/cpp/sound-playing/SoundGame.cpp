#include "SoundGame.h"
#include "AAssetDataSource.h"
#include "logger.h"

constexpr int64_t kMillisecondsInSecond = 1000;
constexpr int64_t kNanosecondsInMillisecond = 1000000;

enum class TapResult {
    Early,
    Late,
    Success
};

int64_t nowUptimeMillis();

constexpr int64_t convertFramesToMillis(const int64_t frames, const int sampleRate){
    return static_cast<int64_t>((static_cast<double>(frames)/ sampleRate) * kMillisecondsInSecond);
}

TapResult getTapResult(int64_t tapTimeInMillis, int64_t tapWindowInMillis);

void renderEvent(TapResult r);


SoundGame::SoundGame(AAssetManager &assetManager): mAssetManager(assetManager) {

}

void SoundGame::onSurfaceCreated() {

}

void SoundGame::start() {
    mLoadingResult = std::async(&SoundGame::load, this);
}

void SoundGame::stop() {

}

void SoundGame::onSurfaceChanged(int width, int height) {

}

void SoundGame::onSurfaceDestroy() {

}

void SoundGame::tick() {

    switch(mGameState) {
        case GameState::Playing:
            SetGLScreenColor(kPlayingColor);
            break;
        case GameState::Loading:
            SetGLScreenColor(kLoadingColor);
            break;
        case GameState::FailedToLoad:
            SetGLScreenColor(kLoadingFailedColor);
            break;
    }

}

void SoundGame::tap(int64_t eventTimeAsUpTime) {
    mClap->setPlaying(true);
}

void SoundGame::load() {
    if (!openStream()) {
        LOGD("Failed to open a stream");
        mGameState = GameState::FailedToLoad;
        return;
    }

    if (!setupAudioSources()) {
        LOGD("Failed to setup the audio sources");
        mGameState = GameState::FailedToLoad;
        return;
    }

    mClapEvents.push(0);
    mClapEvents.push(500);
    mClapEvents.push(1000);

    Result result = mAudioStream->requestStart();
    if (result != Result::OK){
        LOGD("Failed to request start");
        mGameState = GameState::FailedToLoad;
        return;
    }

    mGameState = GameState::Playing;
}

bool SoundGame::setupAudioSources() {
    LOGD("setting the audio up");

    AudioProperties targetProperties {
            .channelCount = mAudioStream->getChannelCount(),
            .sampleRate = mAudioStream->getSampleRate()
    };

    std::shared_ptr<AAssetDataSource> mClapSource {
            AAssetDataSource::newFromCompressedAsset(mAssetManager, "CLAP.mp3", &targetProperties)
    };

    LOGD("Audio properly setup from compressed asset");
    if(mClapSource == nullptr) {
        LOGE("Clap source is null");
        return false;
    }

    mClap = std::make_unique<Player>(mClapSource);

    std::shared_ptr<AAssetDataSource> backingTrackSource {
            AAssetDataSource::newFromCompressedAsset(mAssetManager, "FUNKY_HOUSE.mp3", &targetProperties)
    };

    if (backingTrackSource == nullptr){
        LOGE("Could not load source data for backing track");
        return false;
    }
    mBackingTrack = std::make_unique<Player>(backingTrackSource);
    mBackingTrack->setPlaying(true);
    mBackingTrack->setLooping(true);
    // Add both players to a mixer
    mixer.addTrack(mClap.get());
    mixer.addTrack(mBackingTrack.get());

    return true;
}

bool SoundGame::openStream() {
    AudioStreamBuilder builder;
    builder.setFormat(AudioFormat::Float);
    builder.setPerformanceMode(PerformanceMode::LowLatency);
    builder.setSharingMode(SharingMode::Exclusive);
    builder.setSampleRate(48000);
    builder.setSampleRateConversionQuality(
            SampleRateConversionQuality::Medium);
    builder.setChannelCount(2);

    builder.setCallback(this);

    Result result = builder.openManagedStream(mAudioStream);
    mixer.setChannelCount(mAudioStream->getChannelCount());

    return result == Result::OK;
}

DataCallbackResult SoundGame::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    float *outputBuffer = static_cast<float *>(audioData);
    int64_t nextClapEventMs;

    for (int i = 0; i < numFrames; ++i) {

        mSongPositionMs = convertFramesToMillis(
                mCurrentFrame,
                mAudioStream->getSampleRate());

        if (mClapEvents.peek(nextClapEventMs) && mSongPositionMs >= nextClapEventMs){
            mClap->setPlaying(true);
            mClapEvents.pop(nextClapEventMs);
        }
        mixer.renderAudio(outputBuffer+(oboeStream->getChannelCount()*i), 1);
        mCurrentFrame++;
    }

    return DataCallbackResult::Continue;
}