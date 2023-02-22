#ifndef WRAPPER
#define WRAPPER

#include <napi.h> // 必要なヘッダ


class Wrapper : public Napi::ObjectWrap<Wrapper> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Object NewInstance(Napi::Env env, const Napi::CallbackInfo& info);

    Wrapper(const Napi::CallbackInfo& info);
    ~Wrapper();

    Napi::Value getNum(const Napi::CallbackInfo& info);

private:
    double m_value;
};

#endif
