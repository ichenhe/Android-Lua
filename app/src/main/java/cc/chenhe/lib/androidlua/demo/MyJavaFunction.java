package cc.chenhe.lib.androidlua.demo;


import org.keplerproject.luajava.JavaFunction;
import org.keplerproject.luajava.LuaException;
import org.keplerproject.luajava.LuaState;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 这是 Lua 调用 java 函数的 demo. 首先把要执行的函数包装成一个类，继承 {@link JavaFunction}，
 * 在 {@link #execute()} 中执行操作，可获取 Lua 传入的参数或压入返回值。
 * <p>
 * This is a demo that Lua calls the java function.
 * First wrap the function to be a class which extends {@link JavaFunction}.
 * Then do something in {@link #execute()}.
 * You can get the parameters passed in by Lua or press the return value.
 */
public class MyJavaFunction extends JavaFunction {

    public MyJavaFunction(LuaState luaState) {
        super(luaState);
    }

    @Override
    public int execute() {
        // 获取Lua传入的参数，注意第一个参数固定为上下文环境。
        // Getting the parameters passed in by Lua
        // Notice that the first argument is lua context.
        String str = L.toString(2);

        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        Date date = new Date(System.currentTimeMillis());
        L.pushString(simpleDateFormat.format(date) + str);
        return 1; // 返回值的个数 // Number of return values
    }

    public void register() {
        try {
            // 注册为 Lua 全局函数
            // Register as a Lua global function
            register("testJava");
        } catch (LuaException e) {
            e.printStackTrace();
        }
    }

}
