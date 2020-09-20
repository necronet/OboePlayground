package info.necronet.oboeplayground

import android.content.Context
import android.content.res.AssetManager
import android.media.AudioManager
import android.os.Build
import android.os.Bundle
import android.view.WindowManager
import androidx.appcompat.app.AppCompatActivity


class OboeSoundPlaying : AppCompatActivity() {

    companion object {
        init {
            System.loadLibrary("sound-playing")
        }
    }


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.sound_playing)
        window?.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        setDefaultStreamValues(this);
    }


    override fun onResume() {
        super.onResume()
        native_onStart(assets)
    }

    override fun onPause() {
        super.onPause()
        native_onStop()
    }

    fun setDefaultStreamValues(context: Context) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
            val myAudioMgr = context.getSystemService(Context.AUDIO_SERVICE) as AudioManager
            val sampleRateStr = myAudioMgr.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE)
            val defaultSampleRate = sampleRateStr.toInt()
            val framesPerBurstStr =
                myAudioMgr.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER)
            val defaultFramesPerBurst = framesPerBurstStr.toInt()
            native_setDefaultStreamValues(defaultSampleRate, defaultFramesPerBurst)
        }
    }

    private external fun native_onStart(assetManager: AssetManager)
    private external fun native_onStop()
    private external fun native_setDefaultStreamValues(
        defaultSampleRate: Int,
        defaultFramesPerBurst: Int
    )

}