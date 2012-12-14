/*
 * V8Utilities - Sugar for your Node C++ addons
 * Copyright (c) 2012, Xavier Mendez
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef V8U_VERSION_HPP
#define	V8U_VERSION_HPP

#include <sstream>

#include "v8u.hpp"

namespace v8u {

class Version: public node::ObjectWrap {
public:
  Version(int major, int minor, int revision): major_(major), minor_(minor),
                                               revision_(revision) {}
  Version(Version& other): major_(other.major_), minor_(other.minor_),
                           revision_(other.revision_) {}
  ~Version() {}
  V8_CTOR(Version) {
    int arg0 = Int(args[0]);
    int arg1 = Int(args[1]);
    int arg2 = Int(args[2]);

    V8_WRAP(new Version(arg0, arg1, arg2));
  } V8_CTOR_END()

  int getMajor() const {return major_;}
  int getMinor() const {return minor_;}
  int getRevision() const {return revision_;}

  void setMajor(int major) {major_=major;}
  void setMinor(int minor) {minor_=minor;}
  void setRevision(int revision) {revision_=revision;}

  std::string toString() const {
    std::stringstream ret;
    ret << major_ << "." << minor_ << "." << revision_;
    return ret.str();
  }

  static V8_CB(ToString) {
    Version* inst = Unwrap(args.This());
    std::string ret = inst->toString();
    V8_RET(Str(ret.data(), ret.size()));
  } V8_CB_END()

  static V8_CB(Inspect) {
    Version* inst = Unwrap(args.This());
    std::string ret = "<Version "+inst->toString()+">";
    V8_RET(Str(ret.data(), ret.size()));
  } V8_CB_END()

  //Getters
  V8_GET(GetMajor) {
    Version* inst = Unwrap(info.Holder());
    V8_RET(Int(inst->major_));
  } V8_GET_END()
  V8_GET(GetMinor) {
    Version* inst = Unwrap(info.Holder());
    V8_RET(Int(inst->minor_));
  } V8_GET_END()
  V8_GET(GetRevision) {
    Version* inst = Unwrap(info.Holder());
    V8_RET(Int(inst->revision_));
  } V8_GET_END()

  //Setters
  V8_SET(SetMajor) {
    Version* inst = Unwrap(info.Holder());
    inst->major_ = Int(value);
  } V8_SET_END()
  V8_SET(SetMinor) {
    Version* inst = Unwrap(info.Holder());
    inst->minor_ = Int(value);
  } V8_SET_END()
  V8_SET(SetRevision) {
    Version* inst = Unwrap(info.Holder());
    inst->revision_ = Int(value);
  } V8_SET_END()

  NODE_TYPE(Version, "Version") {
    V8_DEF_ACC("major", GetMajor, SetMajor);
    V8_DEF_ACC("minor", GetMinor, SetMinor);
    V8_DEF_ACC("revision", GetRevision, SetRevision);

    V8_DEF_CB("toString", ToString);
    V8_DEF_CB("inspect", Inspect);
  } NODE_TYPE_END()
private:
  int major_, minor_, revision_;
};
V8_POST_TYPE(Version)

};

#endif	/* V8U_VERSION_HPP */

