package com.aim.lock;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    // Load the native library on application start
    static {
        System.loadLibrary("aimlock");
    }

    // Declare the native method matching C++ signature
    public native void nativeExecute(long localPtr, long targetPtr, int count);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Simple layout initialization
        // Note: You can create a basic activity_main.xml or just let it run
    }
}
