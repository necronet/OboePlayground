package info.necronet.oboeplayground

import android.content.Intent
import android.os.Bundle
import android.os.PersistableBundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        button_hello.setOnClickListener {
            startActivity(Intent(this@MainActivity, OboeHelloPlayground::class.java))
        }

        sound_playing.setOnClickListener{
            startActivity(Intent(this@MainActivity, OboeSoundPlaying::class.java))
        }
    }

}