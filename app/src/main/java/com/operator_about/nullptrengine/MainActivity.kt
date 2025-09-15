package com.operator_about.nullptrengine

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Surface
import android.view.SurfaceView
import android.widget.TextView
import com.operator_about.nullptrengine.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        StartupNullptrEngine(binding.Viewport.holder.surface)
        binding.Properties.text = GetDataNullptrEngine()
    }

    override fun onDestroy() {
        super.onDestroy()
        ShutdownNullptrEngine()
    }


    external fun StartupNullptrEngine(surface: Surface): Unit
    external fun GetDataNullptrEngine(): String
    external fun ShutdownNullptrEngine(): Unit


    companion object {
        // Used to load the 'nullptrengine' library on application startup.
        init {
            System.loadLibrary("nullptrengine")
        }
    }
}