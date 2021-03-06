package info.necronet.oboeplayground

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.MotionEvent
import android.widget.SeekBar
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.activity_playground.*
import kotlin.concurrent.thread

class OboeHelloPlayground : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_playground)

        updateFrequencyLabel()
        updateAmplitudeLabel()
        seekBarFrequency.setOnSeekBarChangeListener( object :
        SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                updateFrequencyLabel()
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })

        seekBarAmplitude.setOnSeekBarChangeListener( object :
            SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                updateAmplitudeLabel()
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })


        startEngine()

        thread {
            while(!Thread.interrupted()) {
                Thread.sleep(1000)
                if(isWaveOn()) {
                    val currentData = getCurrentData()
                    runOnUiThread {
                        currentData.forEach {
                            liveAudioView.addAmplitude(it)
                        }
                        liveAudioView.invalidate()
                    }
                }

            }
        }
    }

    fun updateFrequencyLabel() {
        frequencyLabel.text = resources.getString(R.string.frequency, seekBarFrequency.progress)
        setFrequency(seekBarFrequency.progress.toFloat())
    }

    fun updateAmplitudeLabel() {
        amplitudeLabel.text = resources.getString(R.string.amplitude, seekBarAmplitude.progress)
        setAmplitude((seekBarAmplitude.progress.toFloat()/100))
    }

    external fun startEngine(): Unit
    external fun tap(b : Boolean): Unit
    external fun setAmplitude(amplitude : Float): Unit
    external fun setFrequency(frequency : Float): Unit
    external fun getCurrentData(): FloatArray
    external fun isWaveOn(): Boolean

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        if (event?.action == MotionEvent.ACTION_DOWN) {
            tap(true);
        } else if (event?.action == MotionEvent.ACTION_UP){
            tap(false);
        }
        return super.onTouchEvent(event)
    }
}
