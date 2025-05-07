//
// Created by xzy54 on 2025/5/3.
//
#pragma once
#ifndef SLIMENANO_CHARACTER_COLLECTION_SRC_CHAR_COLLECTION_HPP_
#define SLIMENANO_CHARACTER_COLLECTION_SRC_CHAR_COLLECTION_HPP_
#include <cstdint>
#include "slimenano/slimenano_api.hpp"

namespace slimenano{

    // A character collection interface
    class SLIMENANO_API_ char_collection {
    public:
        char_collection() = default;
        char_collection(const char_collection &other) = delete;
        char_collection(char_collection &&other) noexcept = delete;
        char_collection & operator=(const char_collection &other) = delete;
        char_collection & operator=(char_collection &&other) noexcept = delete;
        virtual ~char_collection() = default;
        virtual bool contains(const uint32_t&) const = 0;
    };

}

#endif //SLIMENANO_CHARACTER_COLLECTION_SRC_CHAR_COLLECTION_HPP_
