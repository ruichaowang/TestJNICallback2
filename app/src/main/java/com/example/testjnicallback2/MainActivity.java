package com.example.testjnicallback2;

import androidx.annotation.Keep;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.example.testjnicallback2.databinding.ActivityMainBinding;

/** JNI callback example
 * 需求：native 运行一个长耗时的操作，不断地返回进度
 * 实现：1 个 JNI function 调起一个操作，这个操作开启一个线程进行运行，运行结束后回调 Java 的方法
 *
 * 备注，google 的 NDK samples 有更全面的介绍
 * @reference: https://blog.csdn.net/tkwxty/article/details/103814984
 */
public class MainActivity extends AppCompatActivity {
    private static final String TAG = "Java_thread";

    // Used to load the 'testjnicallback2' library on application startup.
    static {
        System.loadLibrary("testjnicallback2");
    }

    private ActivityMainBinding binding;
    TextView ProgressView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        ProgressView =  (TextView) findViewById(R.id.sample_text);
    }

    @Override
    protected void onStart() {
        super.onStart();

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        ((TextView)findViewById(R.id.sample_text)).setText("Native 未运行");
        StartProgress();
        UpdateProgress(20);
    }

    /**
     * A function calling from JNI to update display info,
     * @param progress_percentage 完成的进度百分比
     */
    @Keep
    private void UpdateProgress(int progress_percentage) {
        Log.i(TAG, "onNativeCallBack : " + progress_percentage);
        MainActivity.this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                String progress_percentage_string;
                if (100 == progress_percentage) {
                    progress_percentage_string =  "完成进度";
                } else {
                    progress_percentage_string = progress_percentage + "%";
                }
                ((TextView)findViewById(R.id.sample_text)).setText(progress_percentage_string);
            }
        });
    }


    public native void StartProgress();
}