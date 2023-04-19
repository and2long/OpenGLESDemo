package com.example.openglesdemo.cver

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import com.example.openglesdemo.R

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        findViewById<Button>(R.id.btn_simple_triangle).setOnClickListener {
            goToDetailActivity(PARAM_SIMPLE_TRIANGLE)
        }
        findViewById<Button>(R.id.btn_simple_cube).setOnClickListener {
            goToDetailActivity(PARAM_SIMPLE_CUBE)
        }
        findViewById<Button>(R.id.btn_texture_cube).setOnClickListener {
            goToDetailActivity(PARAM_TEXTURE_CUBE)
        }
        findViewById<Button>(R.id.btn_lighting).setOnClickListener {
            goToDetailActivity(PARAM_LIGHTING)
        }
    }

    private fun goToDetailActivity(param: String) {
        val intent = Intent(this, DetailActivity::class.java)
        intent.putExtra("param", param)
        startActivity(intent)
    }
}