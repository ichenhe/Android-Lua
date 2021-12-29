package cc.chenhe.lib.androidlua.demo;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import org.keplerproject.luajava.LuaState;
import org.keplerproject.luajava.LuaStateFactory;

import java.io.IOException;
import java.io.InputStream;

@SuppressLint("SetTextI18n")
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

        StringBuilder s = new StringBuilder();
        findViewById(R.id.btnGetV1).setOnClickListener(view -> {
            lua.getGlobal("v1");
            textView.setText(lua.toString(-1));
            lua.pop(1);
        });
        findViewById(R.id.btnSetV2).setOnClickListener(view -> {
            lua.pushString("value from java");
            lua.setGlobal("v2");
        });
        findViewById(R.id.btnGetV2).setOnClickListener(view -> {
            lua.getGlobal("v2");
            textView.setText(lua.toString(-1));
            lua.pop(1);
        });
        findViewById(R.id.btnInjectJavaFun).setOnClickListener(view -> new MyJavaFunction(lua).register());
        findViewById(R.id.btnCallInjectedFun).setOnClickListener(view -> {
            lua.LdoString("return getTime(' - passing by lua')");
            textView.setText(lua.toString(-1));
            lua.pop(1);
        });
        findViewById(R.id.btnGetLuaTable).setOnClickListener(view -> {
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
        });
        findViewById(R.id.btnSetLuaTable).setOnClickListener(view -> {
            lua.newTable();
            lua.pushString("from");
            lua.pushString("java");
            lua.setTable(-3);
            lua.pushString("value");
            lua.pushString("Hello lua");
            lua.setTable(-3);
            lua.setGlobal("table");
        });
        findViewById(R.id.btnCallLua).setOnClickListener(view -> {
            s.delete(0, s.length());
            lua.getGlobal("extreme");
            lua.pushNumber(15.6);
            lua.pushNumber(0.8);
            lua.pushNumber(189);
            lua.pcall(3, 2, 0);
            s.append("max:").append(lua.toString(-2)).append(" min:").append(lua.toString(-1));
            textView.setText(s.toString());
            lua.pop(2);
        });
        findViewById(R.id.btnInjectJavaObj).setOnClickListener(view -> {
            lua.pushJavaObject(textView);
            lua.setGlobal("textView");
            lua.pushInteger(Color.RED);
            lua.setGlobal("red");
            lua.LdoString("textView:setTextColor(red)");
        });
        findViewById(R.id.btnLuaCallback).setOnClickListener(view -> {
            textView.setText("Loading...");
            new AsyncJavaFunction(lua).register();
            lua.getGlobal("luaCallback");
            lua.pushJavaObject(textView);
            lua.pcall(1, 0, 0);
        });

    }

    public static String readAssetsTxt(Context context, String fileName) {
        try {
            InputStream is = context.getAssets().open(fileName);
            int size = is.available();
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();
            return new String(buffer, "utf-8");
        } catch (IOException e) {
            e.printStackTrace();
        }
        return "err";
    }
}
