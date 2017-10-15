package com.cfryan.ndkhelloworld;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example calls to a native method
        findViewById(R.id.sample_text_static1).setOnClickListener(this);

        findViewById(R.id.sample_text_static2).setOnClickListener(this);

        findViewById(R.id.sample_text_dynamic).setOnClickListener(this);

        findViewById(R.id.sample_text_dynamic_param).setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
        int id = v.getId();
        switch (id) {
            case R.id.sample_text_static1:
                Toast.makeText(this, new NativeUtils().getString(), Toast.LENGTH_LONG).show();
                break;
            case R.id.sample_text_static2:
                Toast.makeText(this, NativeUtils.staticGetString(), Toast.LENGTH_LONG).show();
                break;
            case R.id.sample_text_dynamic:
                Toast.makeText(this, NativeUtils.dynamicGetString(), Toast.LENGTH_LONG).show();
                break;
            case R.id.sample_text_dynamic_param:
                Toast.makeText(this, NativeUtils.dynamicGetStringWithParam(" have params"), Toast.LENGTH_LONG).show();
                break;
        }
    }
}
