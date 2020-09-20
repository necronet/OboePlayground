package info.necronet.oboeplayground

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.util.AttributeSet
import android.util.Log
import android.view.View

const val LINE_WIDTH : Int = 1
const val LINE_SCALE : Float = .5f

class LiveAudioView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0) : View(context, attrs, defStyleAttr) {

    private val paint = Paint()
    private lateinit var amplitudes : MutableList<Float>
    private var maxSize : Int = 0

    init {
        paint.color = Color.GREEN
        paint.strokeWidth = 100F
    }

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        super.onSizeChanged(w, h, oldw, oldh)
        amplitudes = mutableListOf()
        maxSize = width / LINE_WIDTH
    }

    fun clear() {
        amplitudes.clear()
    }

    fun addAmplitude(amplitude : Float) {
        //Log.d("LiveAudioView", "Getting ammplitude ${amplitude*1000}")
        amplitudes.add(amplitude * 100)

        if (amplitudes.size * LINE_WIDTH >= width) {
            amplitudes.removeAt(0)
        }
    }

    override fun onDraw(canvas: Canvas?) {
        Log.d("LiveAudioView", "onDraw ${amplitudes.size}")
        super.onDraw(canvas)
        val middle = height / 2
        var curx = 0f

        amplitudes.forEach { amp ->
            val scaleHeight = amp / LINE_SCALE
            curx += LINE_WIDTH
            canvas?.drawLine(curx, middle + scaleHeight / 2, curx, middle - scaleHeight / 2, paint)
        }

    }

}