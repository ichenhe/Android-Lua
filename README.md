# Android-Lua

[ ![Download](https://img.shields.io/maven-central/v/me.chenhe/android-lua?style=flat-square) ](https://search.maven.org/artifact/me.chenhe/android-lua)

Based on [Androlua for Lua5.3.3](https://github.com/lendylongli/AndroLua), make some practical changes.

blog: https://www.jianshu.com/p/908a1ac893bb

# 依赖 Dependency

```
implementation "me.chenhe:android-lua:1.1.1"
```

⚠️ 由于 JCenter 停止维护，本 lib 已经传至 maven central，**坐标变更为 `me.chenhe:android-lua`。**

Because JCenter is read only now, this lib has published to maven central. **But the coordinate changed to `me.chenhe:android-lua`.**

# 混淆 ProGuard

如果你使用R8（Gradle 3.4.0　默认使用）则无需添加任何规则。否则请添加下述内容：

If you use R8 which is default in Gradle 3.4.0 nothing need to do. Else add the rules below:

```
-keep class org.keplerproject.luajava.**{ *; }
```

# DEMO

Demo 工程位于源码的 `app` module 下，里面演示了下面讲述的所有基础应用。

![](https://i.loli.net/2019/06/28/5d14ff8a0366027232.png)

# 使用 Usage

## 初始化

Lua 与 C 依靠一个虚拟的栈来完成数据交换。包括变量、函数、参数、返回值等在内的**一切数据**，都要放入栈中来共享。为了调用方便，这个栈并不是严格遵循栈的规则。从索引来看，栈底索引为1，往上依次递增。而栈顶索引是-1，往下依次递减。因此，正负索引都是合法的，但是0不可以。下面是栈的示意图：

![](https://i.loli.net/2019/06/28/5d14ea88107f358531.png)

所以要在 java 中使用 Lua，首先我们需要创建一个 Lua 运行环境，也就是 Lua 栈：

```java
LuaState lua = LuaStateFactory.newLuaState(); //创建栈
lua.openLibs(); //加载标准库

lua.close(); //养成良好习惯，在执行完毕后销毁Lua栈。
```

这样我们就创建了一个 Lua 运行时。每一个 `LuaState` 实例都是一个独立的运行时，你可以创建多个运行时，他们相互隔离。

> 任何时候都可以使用 `Log.i("LuaStack", lua.dumpStack());` 或通过其他你喜欢的输出方式查看 lua 栈的当前情况，以免更好地理解 c 与 Lua 的交互过程。

## 加载 Lua 脚本

使用 `lua.LdoString()` 可以轻松执行一段 Lua 代码。通过其返回值可以判断执行是否成功。`0` 表示成功否则表示不成功。若不成功则错误信息会直接入栈，我们可以通过 `lua.toString(-1)` 获取到。

同时也提供了 `lua.LdoFile()` 来直接执行 Lua 源码文件，但请注意这里只允许传入本地文件路径且具有访问权限。

> `LdoFile()` 支持加载 Lua 编译后的字节码。但请注意 Lua 原生字节码不是完全跨平台，例如32与64位就不兼容。如果有这方面需求请考虑 [Lua JIT](https://github.com/liangchenhe55/Android-LuaJIT)。

> 这里 API 没有采用标准的小驼峰规范，是因为直接原样保留了 Lua 的 C API 函数名，便于与 [Lua 官方文档](https://www.lua.org/manual/5.3/manual.html)对照。

## 获取 Lua 变量

首页要说明的是，只有全局变量（非 local）才可以读取。

lua:

```lua
v1 = "this is value from lua"
```

java:

```java
lua.getGlobal("v1"); // 请求 v1 变量的值，入栈
String s = lua.toString(-1) // 从栈中取得了值
lua.pop(1); // 及时将不用的数据出栈避免栈溢出
// 此时 s = "this is value from lua"
```

记住，`lua.toXXX()` 函数在取得值之后是不会自动出栈的。记得手动弹出以免栈溢出。`lua.pop()` 可以从栈顶弹出指定个数的元素。

## 注入 Lua 变量

有时我们需要在 android 中创建 Lua 变量，这样就可以在 Lua 中直接使用了。注意，这里创建的变量都是全局的（非 local）。

java:

```java
lua.pushString( "from java" ); //压入欲注入变量的值
lua.setGlobal("v2"); // 设置变量名
// 现在可以在 lua 脚本中使用 `v2` 变量了。
```

首先通过 `lua.pushXxx()` 将值入栈，然后使用 `lua.setGlobal()` 传递一个变量名即可。它会自动把栈顶元素弹出作为变量的值。因此这两个操作完成后栈是空的（假设没有其他元素），不需要单独 pop.

> 如果注入的变量名已经存在则会覆盖原先的值。

## 遍历 Lua 表（数组）

Lua 的表相对来说是特别灵活的，既可以作为数组，也可以作为键值数组。而且同一个 table 里，key 与 value 的数据类型都可以不同。但无论如何，在 java 中的遍历方式都是一样的。

lua:

```lua
-- 以键值数组为例
table = {}
table["name"] = "Lily"
table["age"] = 18
table["sex"] = "female"
```

java:

```java
lua.getGlobal( "table" );
StringBuilder s = new StringBuilder();
if ( lua.isTable( -1 ) )
{
	lua.pushNil(); // 压入一个空值作为初始 key 启动遍历
	while ( lua.next( -2 ) != 0 )
	{
		s.append( lua.toString( -2 ) ).append( " = " )
		.append( lua.toString( -1 ) ).append( "\n" );
		lua.pop( 1 );
	}
	lua.pop( 1 ); // 弹出 table 本身
}
// 最后 StringBuilder 里的内容是：name = Lily\nage=18\nsex=female
// 顺序可能错乱，因为 k-v 不一定是有序的。
```

类似之前，首先找到了 `table` 变量并入栈。随后通过 `lua.isTable()` 判断指定位置的元素是不是一个 table。`-1` 表示栈顶，也就是刚刚入栈的变量。

`lua.next()` 接受一个参数指明要遍历的 table 在栈中的位置，由于我们先 push 了一个 `Nil`，因此这里是`-2`。这个函数会弹出栈顶元素作为 key，将下一对 k-v 依次入栈，若没有下一个元素返回`0`。因此在执行完 `next()` 后栈中最顶上两个元素依次为 `value、key`。

取出所需数据后我们将 `value ` 弹出，保留 `key` 进行下一次 `next()` 完成遍历，最后别忘记弹出 table 本身。

## 注入 Lua 表

类似注入普通变量。

java:

```java
lua.newTable(); // 新建一个table，并压入栈。
lua.pushString( "from" );
lua.pushString( "java" );
lua.setTable( -3 ); // 设置一个元素
lua.pushString( "value" );
lua.pushString( "Hello lua" );
lua.setTable( -3 );
lua.setGlobal( "table" );
```

首先需要创建一个 table。接着将 key、value 依次入栈，随后调用 `lua.setTable()` 设置一个元素。它接受一个参数指明要设置的 table 在栈中的位置。因为我们已经压入了两个值，因此 table 的位置是`-3`。它会弹出栈顶的两个值分别作为 value、key。最后使用 `lua.setGlobal()` 弹出 table 本身并注入为变量。

上面代码运行后，等价于下面的 Lua table 定义：

```lua
table = {}
table["from"] = "java"
table["value"] = "Hello lua"
```

## Java 调用 Lua 函数

你可以将 Lua 函数理解为一个特殊的变量。因此要调用 Lua 函数，首先要像获取 Lua 变量那样获取它。

lua:

```lua
-- 这是一个获取最大值与最小值的函数
-- Lua 允许多个返回值，其实这是一个语法糖，内部使用的是 table 包装
function extreme(a, b, c)
    local max = a
    local min = a
    if(b>max) then
        max = b
    elseif(b<min) then
        min = b
    end
    if(c>max) then
        max = c
    elseif(c<min) then
        min = c
    end
    return max, min
end
```

java:

```java
StringBuilder s = new StringBuilder();
lua.getGlobal("extreme"); // 获取到函数入栈
lua.pushNumber(15.6); // 依次压入三个参数
lua.pushNumber(0.8);
lua.pushNumber(189);
lua.pcall(3, 2, 0); // 调用函数
s.append("max:").append(lua.toString(-2)).append(" min:").append(lua.toString(-1));
// 最后 StringBuilder 里的内容是：max:189 min:0.8
```

`lua.pcall()` 接受三个参数，依次是函数的参数个数、返回值的个数、错误处理函数索引。它将把栈顶的 n 个元素作为参数出栈，把第 n+1 个元素作为要调用的函数本身出栈，进行调用后将返回值依次入栈。

类似 `lua.LdoString()`，可以通过返回值判断是否执行成功，也可以直接从栈中拿到错误信息。

`错误处理函数索引` 指的是当函数发生错误时，将会自动调用一个处理错误的函数。这个函数必须提前入栈，并在这里传入它在栈中的索引。

## Lua 调用 Java 函数

Lua 调用 java 函数相对复杂，毕竟 java 不是脚本语言。我们需要将 java 函数包装成一个 `JavaFunction` 类，实例化之后注册到 Lua，这样才可以从 Lua 调用。下面看一个例子：

```java
public class MyJavaFunction extends JavaFunction {
    public MyJavaFunction(LuaState luaState) {
        super(luaState);
    }
    @Override
    public int execute() {
        // 获取Lua传入的参数，注意第一个参数固定为上下文环境。
        String str = L.toString(2);

        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        Date date = new Date(System.currentTimeMillis());
        L.pushString(simpleDateFormat.format(date) + str);
        return 1; // 返回值的个数
    }

    public void register() {
        try {
            // 注册为 Lua 全局函数
            register("getTime");
        } catch (LuaException e) {
            e.printStackTrace();
        }
    }
}

new MyJavaFunction(lua).register();
// 现在我们可以在 lua 中直接调用 `getTime(" -suffix")`，
// 得到的返回值类似 2019-06-01 23:56:49 -suffix
```

我们创建一个类继承 `JavaFunction` 并实现 `execute()` 方法，它将在被 Lua 调用时执行。前面说过，Lua 与 c 靠栈来交换数据，故调用函数所传的参数也会入栈。需要注意的是第一个元素恒为 Lua 的上下文环境，实际传入的参数索引是从2开始。在这个简单的例子中，我们取得了 Lua 传递的字符串，并将其拼接在由 java 获取的时间字符串后边一起返回给 Lua。

与传参类似，返回值也是直接入栈即可。最后我们需要返回返回值的个数，这样 Lua 就知道从栈里取出几个元素作为返回值了。这些元素会被自动出栈。这里我们利用 `L.pushString()` 将拼接后的字符串返回给 Lua，并返回 `1` 表示有1个返回值。

最后实例化刚才包装的类就可以成功注册了。现在我们可以在 Lua 中调用 `getTime(String)`，它将返回一个字符串，内容是当前的时间加上我们传入的字符串。

> Lua 语言是为嵌入而生的，因此他的标准库小的可怜，甚至没有获取当前时间的函数，更别提网络访问了。因此实际项目中我们会根据项目需要大量注册 java 函数供 Lua 使用。
>
> 为了方便管理，我们可以将函数作为元素注册到 table 里，最后将 table 注入 Lua，这样在 Lua 中可以使用类似 `System.getTime()` 的形式调用。

## 注入 java 对象

除了注入简单的 java 函数，甚至可以直接注入一个 java 对象，这样这个对象所拥有的所有成员都可以在 Lua 中直接使用。

java:

```java
TextView textView = findViewById(R.id.textView);
lua.pushJavaObject(textView);
lua.setGlobal("textView");
lua.pushInteger(Color.RED);
lua.setGlobal("red");
// 现在可以直接在 Lua 中调用 `textView:setTextColor(red)` 来将文本框设置为红色
// setTextColor() 是 TextView 的成员函数，我们没有显式注入但可以直接使用。
// 类似的，setTextSize() 也可以直接使用。
```

使用 `lua.pushJavaObject()` 可以非常轻松地注入 java 对象作为 Lua 变量。注意，在 Lua 中调用对象的成员函数需要使用冒号 `:`，这其实也是一个语法糖，`textView:setTextColor(red)` 等价于 `textView.setTextColor(self, red)`，也就是说冒号自动地传递了 `self` 参数来模拟面向对象。

> **警告：** 由于注册对象会自动注册其所有成员函数与变量，因此开销是非常大的。请谨慎使用这一特性。

## Lua 回调 （HTTP 请求）

前面讲了 Lua 调用 java 函数并可以取得返回值，这是在单线程情况下的。如果 java 需要异步执行一个耗时的操作（例如 HTTP 请求），那么就需要 Lua 提供一个回调函数。Lua 是支持闭合函数（closure）的，因此回调要比 java 定义一个接口简单不少。下面看一个例子：

java:

```java
// 简单起见省略了一些代码和必要的 try-catch
public class AsyncJavaFunction extends JavaFunction {
    // lua 回调函数
    private LuaObject callbackFun;

    @Override
    public int execute() {
        if (L.isFunction(2)) {
            callbackFun = L.getLuaObject(2); // 获取回调
            new MyAsync().execute();
        }
        return 0;
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
            Thread.sleep(2000);  // 模拟耗时操作（例如网络请求）
            return null;
        }
        @Override
        protected void onPostExecute(Integer integer) {
            super.onPostExecute(integer);
            if (callbackFun != null)
               callbackFun.call(new Object[]{"OK", System.currentTimeMillis() - t}, 0);
        }
    }
}
```

lua:

```lua
http(function(result, time)
        r = string.format("result: %s\ntime: %dms", result, time)
    end
)
-- 最后r的结果可能是：result: OK \n time: 2231ms
```

类似前面的，首先我们需要向 Lua 注入一个 java 函数并取得 Lua 传入的参数。只不过这一次有一个参数是 `Function` 类型的，它可以直接使用成员函数 `call()` 来执行，在 Lua 中表现为传入一个闭包函数作为参数。

当 java 异步任务执行完毕后，通过 `call()` 通知回调，传入一个 `Object` 数组作为参数，这里有2个成员，分别是结果与耗时。`0` 表示回调函数没有返回值，如果有会直接入栈，利用 `lua.toXXX()` 取出就行了。

> **提示：**
>
> 这里采用的是闭包回调。其实还可以使用全局函数作为回调。
>
> 只需要在 Lua 中定义好一个全局函数，然后直接把函数名(String)作为参数传给 java 即可。通过前面 `Java 调用 Lua 函数` 章节所讲的方法就可以执行这个“回调”了。
>
> 这两种方式各有优点。前者代码条理更加清晰，后者比较适合复杂且重复使用的回调。

## 更多高级用法

基础用法基本上讲完了，其实所谓的高级用法都是由基础用法拼接来的。尤其是 `table`，这在 Lua 中是一个非常强大与灵活的东西。以及 `metatable` 更是如此。如果想掌握高级应用，还得深入了解 Lua 本身的原理，这里就不再赘述了。

这个 README 只是抛砖引玉，帮助各位快速在 Android 上整合 Lua，更加深入的问题还请自行查阅 Lua API 文档或其他资料。

# 链接

[Android-LuaJIT](https://github.com/liangchenhe55/Android-LuaJIT)