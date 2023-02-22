
#include "wrapper.h"
#include <napi.h>

using namespace Napi;

// ---------------------------------------------------------- //
// ---------------------のり付け部分--------------------------- //
// ---------------------------------------------------------- //
// new() の定義
Napi::Object Wrapper::NewInstance(Napi::Env env, const Napi::CallbackInfo &info)
{
    Napi::EscapableHandleScope scope(env);
    // jsからコンストラクタに渡されるArgsは infoに配列として入っている
    const std::initializer_list<napi_value> initArgList = {info[0]};
    // ここでWrapper:::Wrapper()が呼ばれる
    Napi::Object obj = env.GetInstanceData<Napi::FunctionReference>()->New(initArgList);
    // gcにメモリ解放されないようにスコープを除外する
    return scope.Escape(napi_value(obj)).ToObject();
}

//　メンバ関数のバインド
Napi::Object Wrapper::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(
        env, "Wrapper", {
            // ここにメンバ関数を登録する
            InstanceMethod("getNum", &Wrapper::getNum),
            // InstanceMethod("jsから呼び出す際の関数名", "呼び出したいC++メンバ関数名"),
        });

    Napi::FunctionReference *constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("Wrapper", func);
    return exports;
}

// ---------------------------------------------------------- //
// --------------- Wrapperクラスの定義はこれより下 --------------- //
// ---------------------------------------------------------- //

// コンストラクタ
Wrapper::Wrapper(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<Wrapper>(info)
{
    m_value = 0.0;
};

Wrapper::~Wrapper(){};

// メンバ関数
Napi::Value Wrapper::getNum(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->m_value);
}
