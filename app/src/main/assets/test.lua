
function setText(tv,con)
    -- testJava() 由 Java 注入。 Injected by Java.
    tv:setText(testJava(con));
    tv:setTextSize(50);
end