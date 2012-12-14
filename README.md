# V8U[tilities]<br/><small>Sugar for your Node C++ addons</small>

Have you ever written a C/C++ addon for Node.JS?  
If you have, you probably are tired of writing so much
code for just having the skeleton of it.  
Sure, the V8 syntax is very **verbose** and repetitive.

With V8U, that will change.  
V8U has a special emphasis on **speed**, **simplicity** and **flexibility**.

**Note:** if you come from CCV8 (now called v8-juice) or are worried  
about performace, be sure to checkout [this wiki page](https://github.com/jmendeth/v8u/wiki/Performance-and-CCV8) to  
know which one to use.

## Enough talking, show me code!

Here we have a simple module which exposes _one_ class `Hello`, with _one_ method, `world`.  
It takes _one_ string as argument, and just returns it untouched.

#### Without V8U

```C++
class Hello : public ObjectWrap {
public:
  //The constructor
  static Handle<Value> NewInstance(const Arguments& args) {
    HandleScope scope;
    if (!args.IsConstructCall())
      return ThrowException(Exception::Error(String::New("Not called as constructor!")));
    Hello* instance = new Hello;
    instance->Wrap(args.This());
    return args.This();
  }

  //The world() method
  static Handle<Value> World(const Arguments& args) {
    HandleScope scope;
    if (!args[0]->IsString())
      return ThrowException(Exception::TypeError(String::New("Arg must be a string!")));
    return scope.Close(args[0]);
  }
};

extern "C" {
  static void initHello(Handle<Object> target) {
    HandleScope scope;
    Local<FunctionTemplate> protL = FunctionTemplate::New(Hello::NewInstance);
    Persistent<FunctionTemplate> prot = Persistent<FunctionTemplate>::New(protL);
    prot->InstanceTemplate()->SetInternalFieldCount(1);
    prot->SetClassName(String::NewSymbol("Hello"));
    NODE_SET_PROTOTYPE_METHOD(prot, "world", Hello::World);
    target->Set(String::NewSymbol("Hello"), prot->GetFunction();
  }
  NODE_MODULE(simpleaddon, initHello);
};
```

#### With V8U

```C++
class Hello : public ObjectWrap {
public:
  //The constructor
  V8_CTOR(Hello) {
    V8_WRAP(new Hello);
  } V8_CTOR_END()

  //The world() method
  static V8_CB(World) {
    if (!args[0]->IsString()) V8_THROW(TypeErr("Arg must be a string!"));
    V8_RET(args[0]);
  } V8_CB_END()
  
  NODE_DEF_TYPE("Hello") {
    NODE_DEF_CB("world", World);
  } NODE_DEF_TYPE_END()
};

NODE_DEF_MAIN() {
  Hello::init(target);
} NODE_DEF_MAIN_END(simpleaddon)
```

And that's just scratching the surface of what V8U provides.  
What's more, V8U cares about exception wrapping, persistent handles, and other
things for you!

## How to use

To use V8U, simply copy `v8u.hpp` into your project.  
Then include it:

```C++
#include "v8u.hpp"
using namespace v8;
using namespace v8u;
using namespace node;
```

The `using` lines are optional, see [the discussion](https://github.com/jmendeth/v8u/wiki/to-use-or-not-to-use).  
Now, **let the fun begin!**  
See the [tutorial](https://github.com/jmendeth/v8u/wiki/tutorial) to get started.
