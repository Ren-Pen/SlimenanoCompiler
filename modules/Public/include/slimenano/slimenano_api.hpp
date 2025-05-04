//
// Created by xzy54 on 2025/5/3.
//
#pragma once
#ifndef SLIMENANO_PUBLIC_INCLUDE_SLIMENANO_API_HPP_
#define SLIMENANO_PUBLIC_INCLUDE_SLIMENANO_API_HPP_

#    ifdef _MSC_VER
#        ifdef SLIMENANO_LIBRARY_
#            define SLIMENANO_API_ __declspec(dllexport)
#        else
#            define SLIMENANO_API_ __declspec(dllimport)
#        endif //SLIMENANO_LIBRARY_
#    elif __GNUC__
#        ifdef SLIMENANO_LIBRARY_
#            define SLIMENANO_API_ __attribute__((visibility("default")))
#        else
#            define SLIMENANO_API_
#        endif //SLIMENANO_LIBRARY_
#    else
#        define SLIMENANO_API
#        pragma warning Unknown dynamic link import / export semantics.
#    endif

#define UNUSED(X) (void)(X)

#endif //SLIMENANO_PUBLIC_INCLUDE_SLIMENANO_API_HPP_
