package cc.chenhe.lib.androidlua.demo;


import android.os.AsyncTask;

import org.keplerproject.luajava.JavaFunction;
import org.keplerproject.luajava.LuaException;
import org.keplerproject.luajava.LuaObject;
import org.keplerproject.luajava.LuaState;

public class AsyncJavaFunction extends JavaFunction {

    // lua 回调函数
    // lua callback function
    private LuaObject callbackFun;

    public AsyncJavaFunction(LuaState L) {
        super(L);
    }

    @Override
    public int execute() {
        // 获取Lua传入的参数，注意第一个参数固定为上下文环境。
        // Getting the parameters passed in by Lua
        // Notice that the first argument is lua context.
        if (L.isFunction(2)) {
            callbackFun = L.getLuaObject(2);
            new MyAsync().execute();
        }
        return 0;
    }

    void register() {
        try {
            // 注册为 Lua 全局函数
            // Register as a Lua global function
            register("http");
        } catch (LuaException e) {
            e.printStackTrace();
        }
    }

    private class MyAsync extends AsyncTask<Integer, Integer, Integer> {

        long t;

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            t = System.currentTimeMillis();
        }

        @Override
        protected Integer doInBackground(Integer... integers) {
            try {
                // 模拟耗时操作（例如网络请求）
                // some time-consuming operations (such as http requests)
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return null;
        }

        @Override
        protected void onPostExecute(Integer integer) {
            super.onPostExecute(integer);
            if (callbackFun != null) {
                try {
                    // 2个参数，0 个返回值。
                    // two parameters given, no return.
                    callbackFun.call(new Object[]{"OK", System.currentTimeMillis() - t}, 0);
                } catch (LuaException e) {
                    e.printStackTrace();
                }
            }
        }
    }


}
