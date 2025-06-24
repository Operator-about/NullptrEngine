package com.cubevertex.nullptrengine

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Surface
import android.widget.TextView
import com.cubevertex.nullptrengine.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        VkStartup();
    }

    /**
     * A native method that is implemented by the 'nullptrengine' native library,
     * which is packaged with this application.
     */
    external fun VkStartup(): Unit
    companion object {
        // Used to load the 'nullptrengine' library on application startup.
        init {
            System.loadLibrary("nullptrengine")
        }
    }
}