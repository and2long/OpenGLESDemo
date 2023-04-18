package com.example.openglesdemo.cver

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import com.example.openglesdemo.R

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        findViewById<Button>(R.id.btn_simple_triangle).setOnClickListener {
            val intent = Intent(this, DetailActivity::class.java)
            intent.putExtra("param", PARAM_SIMPLE_TRIANGLE)
            startActivity(intent)
        }
        findViewById<Button>(R.id.btn_simple_cube).setOnClickListener {
            val intent = Intent(this, DetailActivity::class.java)
            intent.putExtra("param", PARAM_SIMPLE_CUBE)
            startActivity(intent)
        }
    }
}