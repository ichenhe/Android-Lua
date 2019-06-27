
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

function setText(tv,con)
    -- testJava() 由 Java 注入。 Injected by Java.
    tv:setText(testJava(con));
    tv:setTextSize(50);
end