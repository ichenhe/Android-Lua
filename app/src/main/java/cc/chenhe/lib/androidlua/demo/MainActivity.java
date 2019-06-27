package cc.chenhe.lib.androidlua.demo;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import org.keplerproject.luajava.LuaState;
import org.keplerproject.luajava.LuaStateFactory;

import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

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

        findViewById(R.id.btnGetV1).setOnClickListener(this);
        findViewById(R.id.btnSetV2).setOnClickListener(this);
        findViewById(R.id.btnGetV2).setOnClickListener(this);
        findViewById(R.id.btnInjectJavaFun).setOnClickListener(this);
        findViewById(R.id.btnCallInjectedFun).setOnClickListener(this);
        findViewById(R.id.btnGetLuaTable).setOnClickListener(this);
        findViewById(R.id.btnSetLuaTable).setOnClickListener(this);
        findViewById(R.id.btnCallLua).setOnClickListener(this);
        findViewById(R.id.btnInjectJavaObj).setOnClickListener(this);

    }

    @Override
    public void onClick(View view) {
        StringBuilder s = new StringBuilder();
        switch (view.getId()) {
            case R.id.btnGetV1:
                lua.getGlobal("v1");
                textView.setText(lua.toString(-1));
                lua.pop(1);
                break;
            case R.id.btnSetV2:
                lua.pushString("value from java");
                lua.setGlobal("v2");
                break;
            case R.id.btnGetV2:
                lua.getGlobal("v2");
                textView.setText(lua.toString(-1));
                lua.pop(1);
                break;
            case R.id.btnInjectJavaFun:
                new MyJavaFunction(lua).register();
                break;
            case R.id.btnCallInjectedFun:
                lua.LdoString("return getTime(' - passing by lua')");
                textView.setText(lua.toString(-1));
                lua.pop(1);
                break;
            case R.id.btnGetLuaTable:
                lua.getGlobal("table");
                s.delete(0, s.length());
                if (lua.isTable(-1)) {
                    lua.pushNil();
                    while (lua.next(-2) != 0) {
                        s.append(lua.toString(-2)).append(" = ")
                                .append(lua.toString(-1)).append("\n");
                        lua.pop(1);
                    }
                    lua.pop(1);
                    textView.setText(s.toString());
                }
                break;
            case R.id.btnSetLuaTable:
                lua.newTable();
                lua.pushString("from");
                lua.pushString("java");
                lua.setTable(-3);
                lua.pushString("value");
                lua.pushString("Hello lua");
                lua.setTable(-3);
                lua.setGlobal("table");
                break;
            case R.id.btnCallLua:
                s.delete(0, s.length());
                lua.getGlobal("extreme");
                lua.pushNumber(15.6);
                lua.pushNumber(0.8);
                lua.pushNumber(189);
                lua.pcall(3, 2, 0);
                s.append("max:").append(lua.toString(-2)).append(" min:").append(lua.toString(-1));
                textView.setText(s.toString());
                lua.pop(2);
                break;
            case R.id.btnInjectJavaObj:
                lua.pushJavaObject(textView);
                lua.setGlobal("textView");
                lua.pushInteger(Color.RED);
                lua.setGlobal("red");
                lua.LdoString("textView:setTextColor(red)");
                break;
        }
        Log.i("LuaStack", lua.dumpStack());
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
