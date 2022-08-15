#ifndef _JSON_VALUE_H__
#define _JSON_VALUE_H__

#include<map>
#include<vector>

class JsonObject;
class JsonArray;
class JsonValue;

enum class JsonValueType {
    Null = 0,
    LongLong,
    Double,
    String,
    Boolean,
    Array,
    Object
};

class JsonValue
{
public:
    JsonValue();
    JsonValue(const std::string &value);
    JsonValue(const char* str);
    JsonValue(const std::string::const_iterator &begin, const std::string::const_iterator &end);
    JsonValue(long long value);
    JsonValue(int value);
    JsonValue(bool value);
    JsonValue(double value);
    JsonValue(const JsonObject &value);
    JsonValue(const JsonArray &value);
    
    JsonValueType type() const;
    double ToDouble() const;
    long long toLongLong() const;
    std::string toString() const;
    bool toBoolean() const;
    JsonArray toArray() const;
    JsonObject toObject() const;

    JsonValue(const JsonValue& other);
    JsonValue& operator=(const JsonValue& other);
    // ~JsonValue();
private:
    void swap(JsonValue& other);
    void setType(JsonValueType type);
    JsonValueType _type;

    union{
        double _real;
        long long _number;
        bool _bool;
        std::string *_string;
        JsonObject *_object;
        JsonArray *_array;
    }_value;
};

class JsonArray
{
private:
    std::vector<JsonValue> _array;
public:
    JsonArray();
    ~JsonArray();
    void append(const JsonValue& value);
    const JsonValue &operator[](size_t index) const;
    std::vector<JsonValue>::const_iterator begin() const;
    std::vector<JsonValue>::const_iterator end() const;
};



class JsonObject
{
private:
    std::map<std::string,JsonValue> _object;
public:
    // JsonObject(/* args */);
    // ~JsonObject();

    void insert(const std::string &key, const JsonValue& value);
    bool contains(const std::string& key) const;
    const JsonValue &operator[](const std::string &key) const;
    std::map<std::string, JsonValue>::const_iterator begin() const;
    std::map<std::string, JsonValue>::const_iterator end() const;

};


#endif