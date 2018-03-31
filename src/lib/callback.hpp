#ifndef UTIL_CALLBACK_HPP
#define UTIL_CALLBACK_HPP

#define UTIL_GET_CALLBACK_FACTORY_BIND_FREE(freeFuncPtr) \
    (util::GetCallbackFactory(freeFuncPtr).Bind<freeFuncPtr>())
#define BIND_FREE_CB UTIL_GET_CALLBACK_FACTORY_BIND_FREE

#define UTIL_GET_CALLBACK_FACTORY_BIND_MEMBER(memFuncPtr, instancePtr) \
    (util::GetCallbackFactory(memFuncPtr).Bind<memFuncPtr>(instancePtr))
#define BIND_MEM_CB UTIL_GET_CALLBACK_FACTORY_BIND_MEMBER

namespace util
{

template <typename FuncSignature>
class Callback;

struct NullCallback
{
};

// 0 parameter version

template <typename R>
class Callback<R()>
{
  public:
    static const int Arity = 0;
    typedef R ReturnType;

    Callback() : func(0), obj(0) {}
    Callback(NullCallback) : func(0), obj(0) {}
    Callback(const Callback &rhs) : func(rhs.func), obj(rhs.obj) {}
    ~Callback() {}

    Callback &operator=(NullCallback)
    {
        obj = 0;
        func = 0;
        return *this;
    }
    Callback &operator=(const Callback &rhs)
    {
        obj = rhs.obj;
        func = rhs.func;
        return *this;
    }

    inline R operator()() const
    {
        return (*func)(obj);
    }

  private:
    typedef const void *Callback::*SafeBoolType;

  public:
    inline operator SafeBoolType() const
    {
        return func != 0 ? &Callback::obj : 0;
    }
    inline bool operator!() const
    {
        return func == 0;
    }

  private:
    typedef R (*FuncType)(const void *);
    Callback(FuncType f, const void *o) : func(f), obj(o) {}

  private:
    FuncType func;
    const void *obj;

    template <typename FR>
    friend class FreeCallbackFactory0;
    template <typename FR, class FT>
    friend class MemberCallbackFactory0;
    template <typename FR, class FT>
    friend class ConstMemberCallbackFactory0;
};

template <typename R>
void operator==(const Callback<R()> &,
                const Callback<R()> &);
template <typename R>
void operator!=(const Callback<R()> &,
                const Callback<R()> &);

template <typename R>
class FreeCallbackFactory0
{
  private:
    template <R (*Func)()>
    static R Wrapper(const void *)
    {
        return (*Func)();
    }

  public:
    template <R (*Func)()>
    inline static Callback<R()> Bind()
    {
        return Callback<R()>(&FreeCallbackFactory0::Wrapper<Func>, 0);
    }
};

template <typename R>
inline FreeCallbackFactory0<R>
    GetCallbackFactory(R (*)())
{
    return FreeCallbackFactory0<R>();
}

template <typename R, class T>
class MemberCallbackFactory0
{
  private:
    template <R (T::*Func)()>
    static R Wrapper(const void *o)
    {
        T *obj = const_cast<T *>(static_cast<const T *>(o));
        return (obj->*Func)();
    }

  public:
    template <R (T::*Func)()>
    inline static Callback<R()> Bind(T *o)
    {
        return Callback<R()>(&MemberCallbackFactory0::Wrapper<Func>,
                             static_cast<const void *>(o));
    }
};

template <typename R, class T>
inline MemberCallbackFactory0<R, T>
    GetCallbackFactory(R (T::*)())
{
    return MemberCallbackFactory0<R, T>();
}

template <typename R, class T>
class ConstMemberCallbackFactory0
{
  private:
    template <R (T::*Func)() const>
    static R Wrapper(const void *o)
    {
        const T *obj = static_cast<const T *>(o);
        return (obj->*Func)();
    }

  public:
    template <R (T::*Func)() const>
    inline static Callback<R()> Bind(const T *o)
    {
        return Callback<R()>(&ConstMemberCallbackFactory0::Wrapper<Func>,
                             static_cast<const void *>(o));
    }
};

template <typename R, class T>
inline ConstMemberCallbackFactory0<R, T>
GetCallbackFactory(R (T::*)() const)
{
    return ConstMemberCallbackFactory0<R, T>();
}

// 1 parameter version

template <typename R, typename P1>
class Callback<R(P1)>
{
  public:
    static const int Arity = 1;
    typedef R ReturnType;
    typedef P1 Param1Type;

    Callback() : func(0), obj(0) {}
    Callback(NullCallback) : func(0), obj(0) {}
    Callback(const Callback &rhs) : func(rhs.func), obj(rhs.obj) {}
    ~Callback() {}

    Callback &operator=(NullCallback)
    {
        obj = 0;
        func = 0;
        return *this;
    }
    Callback &operator=(const Callback &rhs)
    {
        obj = rhs.obj;
        func = rhs.func;
        return *this;
    }

    inline R operator()(P1 a1) const
    {
        return (*func)(obj, a1);
    }

  private:
    typedef const void *Callback::*SafeBoolType;

  public:
    inline operator SafeBoolType() const
    {
        return func != 0 ? &Callback::obj : 0;
    }
    inline bool operator!() const
    {
        return func == 0;
    }

  private:
    typedef R (*FuncType)(const void *, P1);
    Callback(FuncType f, const void *o) : func(f), obj(o) {}

  private:
    FuncType func;
    const void *obj;

    template <typename FR, typename FP1>
    friend class FreeCallbackFactory1;
    template <typename FR, class FT, typename FP1>
    friend class MemberCallbackFactory1;
    template <typename FR, class FT, typename FP1>
    friend class ConstMemberCallbackFactory1;
};

template <typename R, typename P1>
void operator==(const Callback<R(P1)> &,
                const Callback<R(P1)> &);
template <typename R, typename P1>
void operator!=(const Callback<R(P1)> &,
                const Callback<R(P1)> &);

template <typename R, typename P1>
class FreeCallbackFactory1
{
  private:
    template <R (*Func)(P1)>
    static R Wrapper(const void *, P1 a1)
    {
        return (*Func)(a1);
    }

  public:
    template <R (*Func)(P1)>
    inline static Callback<R(P1)> Bind()
    {
        return Callback<R(P1)>(&FreeCallbackFactory1::Wrapper<Func>, 0);
    }
};

template <typename R, typename P1>
inline FreeCallbackFactory1<R, P1>
    GetCallbackFactory(R (*)(P1))
{
    return FreeCallbackFactory1<R, P1>();
}

template <typename R, class T, typename P1>
class MemberCallbackFactory1
{
  private:
    template <R (T::*Func)(P1)>
    static R Wrapper(const void *o, P1 a1)
    {
        T *obj = const_cast<T *>(static_cast<const T *>(o));
        return (obj->*Func)(a1);
    }

  public:
    template <R (T::*Func)(P1)>
    inline static Callback<R(P1)> Bind(T *o)
    {
        return Callback<R(P1)>(&MemberCallbackFactory1::Wrapper<Func>,
                               static_cast<const void *>(o));
    }
};

template <typename R, class T, typename P1>
inline MemberCallbackFactory1<R, T, P1>
    GetCallbackFactory(R (T::*)(P1))
{
    return MemberCallbackFactory1<R, T, P1>();
}

template <typename R, class T, typename P1>
class ConstMemberCallbackFactory1
{
  private:
    template <R (T::*Func)(P1) const>
    static R Wrapper(const void *o, P1 a1)
    {
        const T *obj = static_cast<const T *>(o);
        return (obj->*Func)(a1);
    }

  public:
    template <R (T::*Func)(P1) const>
    inline static Callback<R(P1)> Bind(const T *o)
    {
        return Callback<R(P1)>(&ConstMemberCallbackFactory1::Wrapper<Func>,
                               static_cast<const void *>(o));
    }
};

template <typename R, class T, typename P1>
inline ConstMemberCallbackFactory1<R, T, P1>
GetCallbackFactory(R (T::*)(P1) const)
{
    return ConstMemberCallbackFactory1<R, T, P1>();
}

// 2 parameter version

template <typename R, typename P1, typename P2>
class Callback<R(P1, P2)>
{
  public:
    static const int Arity = 2;
    typedef R ReturnType;
    typedef P1 Param1Type;
    typedef P2 Param2Type;

    Callback() : func(0), obj(0) {}
    Callback(NullCallback) : func(0), obj(0) {}
    Callback(const Callback &rhs) : func(rhs.func), obj(rhs.obj) {}
    ~Callback() {}

    Callback &operator=(NullCallback)
    {
        obj = 0;
        func = 0;
        return *this;
    }
    Callback &operator=(const Callback &rhs)
    {
        obj = rhs.obj;
        func = rhs.func;
        return *this;
    }

    inline R operator()(P1 a1, P2 a2) const
    {
        return (*func)(obj, a1, a2);
    }

  private:
    typedef const void *Callback::*SafeBoolType;

  public:
    inline operator SafeBoolType() const
    {
        return func != 0 ? &Callback::obj : 0;
    }
    inline bool operator!() const
    {
        return func == 0;
    }

  private:
    typedef R (*FuncType)(const void *, P1, P2);
    Callback(FuncType f, const void *o) : func(f), obj(o) {}

  private:
    FuncType func;
    const void *obj;

    template <typename FR, typename FP1, typename FP2>
    friend class FreeCallbackFactory2;
    template <typename FR, class FT, typename FP1, typename FP2>
    friend class MemberCallbackFactory2;
    template <typename FR, class FT, typename FP1, typename FP2>
    friend class ConstMemberCallbackFactory2;
};

template <typename R, typename P1, typename P2>
void operator==(const Callback<R(P1, P2)> &,
                const Callback<R(P1, P2)> &);
template <typename R, typename P1, typename P2>
void operator!=(const Callback<R(P1, P2)> &,
                const Callback<R(P1, P2)> &);

template <typename R, typename P1, typename P2>
class FreeCallbackFactory2
{
  private:
    template <R (*Func)(P1, P2)>
    static R Wrapper(const void *, P1 a1, P2 a2)
    {
        return (*Func)(a1, a2);
    }

  public:
    template <R (*Func)(P1, P2)>
    inline static Callback<R(P1, P2)> Bind()
    {
        return Callback<R(P1, P2)>(&FreeCallbackFactory2::Wrapper<Func>, 0);
    }
};

template <typename R, typename P1, typename P2>
inline FreeCallbackFactory2<R, P1, P2>
    GetCallbackFactory(R (*)(P1, P2))
{
    return FreeCallbackFactory2<R, P1, P2>();
}

template <typename R, class T, typename P1, typename P2>
class MemberCallbackFactory2
{
  private:
    template <R (T::*Func)(P1, P2)>
    static R Wrapper(const void *o, P1 a1, P2 a2)
    {
        T *obj = const_cast<T *>(static_cast<const T *>(o));
        return (obj->*Func)(a1, a2);
    }

  public:
    template <R (T::*Func)(P1, P2)>
    inline static Callback<R(P1, P2)> Bind(T *o)
    {
        return Callback<R(P1, P2)>(&MemberCallbackFactory2::Wrapper<Func>,
                                   static_cast<const void *>(o));
    }
};

template <typename R, class T, typename P1, typename P2>
inline MemberCallbackFactory2<R, T, P1, P2>
    GetCallbackFactory(R (T::*)(P1, P2))
{
    return MemberCallbackFactory2<R, T, P1, P2>();
}

template <typename R, class T, typename P1, typename P2>
class ConstMemberCallbackFactory2
{
  private:
    template <R (T::*Func)(P1, P2) const>
    static R Wrapper(const void *o, P1 a1, P2 a2)
    {
        const T *obj = static_cast<const T *>(o);
        return (obj->*Func)(a1, a2);
    }

  public:
    template <R (T::*Func)(P1, P2) const>
    inline static Callback<R(P1, P2)> Bind(const T *o)
    {
        return Callback<R(P1, P2)>(&ConstMemberCallbackFactory2::Wrapper<Func>,
                                   static_cast<const void *>(o));
    }
};

template <typename R, class T, typename P1, typename P2>
inline ConstMemberCallbackFactory2<R, T, P1, P2>
GetCallbackFactory(R (T::*)(P1, P2) const)
{
    return ConstMemberCallbackFactory2<R, T, P1, P2>();
}
}

#endif
