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

        VkStartup(binding.Viewport.holder.surface);
    }


    external fun VkStartup(surface: Surface): Unit


    companion object {

        init {
            System.loadLibrary("nullptrengine")
        }
    }
}