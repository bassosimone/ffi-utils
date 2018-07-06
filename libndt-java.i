/* Part of Measurement Kit <https://measurement-kit.github.io/>.
   Measurement Kit is free software under the BSD license. See AUTHORS
   and LICENSE for more information on the copying conditions. */

/* SWIG interface file for libndt
   ============================== */

%module(directors="1") Libndt

%{
#include <measurement_kit/cxx11.hpp>
%}

%include "stl.i"
%include "stdint.i"
%include "std_string.i"

%feature("director") Nettest;

%template(MapStringString) std::map<std::string, std::string>;
%template(VectorString) std::vector<std::string>;

%include <measurement_kit/cxx11.hpp>
