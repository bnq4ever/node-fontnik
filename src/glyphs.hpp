#pragma once

#include <node.h>

#include "glyphs.pb.h"
#include "vector_tile.pb.h"

class Glyphs : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    static bool HasInstance(v8::Handle<v8::Value> val);
protected:
    Glyphs();
    Glyphs(const char *data, size_t length, bool isTile);
    ~Glyphs();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> Serialize(const v8::Arguments& args);
    static v8::Handle<v8::Value> SerializeTile(const v8::Arguments& args);

    static v8::Handle<v8::Value> Range(const v8::Arguments& args);
    static void AsyncRange(uv_work_t* req);
    static void RangeAfter(uv_work_t* req);

    static v8::Handle<v8::Value> Shape(const v8::Arguments& args);
    static void AsyncShape(uv_work_t* req);
    static void ShapeAfter(uv_work_t* req);
public:
    llmr::glyphs::glyphs glyphs;
    llmr::vector::tile tile;
};
