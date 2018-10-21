package cc.chenhe.lib.androidlua.demo;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import org.keplerproject.luajava.LuaState;
import org.keplerproject.luajava.LuaStateFactory;

import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    private LuaState lua = null;
    private TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = findViewById(R.id.text_view);

        lua = LuaStateFactory.newLuaState();
        if (lua == null) {
            textView.setText("newLuaState false");
            return;
        }
        lua.openLibs();
        lua.LdoString(readAssetsTxt(this, "test.lua"));

        new MyJavaFunction(lua).register();

        lua.getGlobal("setText");
        lua.pushJavaObject(textView);
        lua.pushString("\nHello Lua");

        lua.pcall(2, 0, 0);

    }

    public static String readAssetsTxt(Context context, String fileName) {
        try {
            InputStream is = context.getAssets().open(fileName);
            int size = is.available();
            // Read the entire asset into a local byte buffer.
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();
            // Convert the buffer into a string.
            String text = new String(buffer, "utf-8");
            // Finally stick the string into the text view.
            return text;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return "err";
    }

}
