
v1 = "this is value from lua"

table = {}
table["name"] = "Lily"
table["age"] = 18
table["sex"] = "female"

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

function luaCallback(tv)
    -- http 函数是由 java `AsyncJavaFunction` 类注入的
    -- http function was injected by java `AsyncJavaFunction`
    http(function(result, time)
            tv:setText(string.format("result: %s\ntime: %dms", result, time));
        end
    )
end