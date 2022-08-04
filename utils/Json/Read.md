1. json 模块只测试出将一个字符串做了一个解析
2. 还需要 json 的拼接，例如：
    1. json_value["app"] = "ab"; --> {"app":"s"}
    2. json_value.push{"test":"123"} --> {"app":"s", "test":"123"};
3. 还需要一个取出操作
    1. string s = json_value["app"] --> s = "s"