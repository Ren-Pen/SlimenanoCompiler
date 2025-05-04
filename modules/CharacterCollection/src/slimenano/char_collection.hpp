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
    struct SLIMENANO_API_ char_collection {
        virtual ~char_collection() = default;
        virtual bool contains(uint32_t) = 0;
    };

}

#endif //SLIMENANO_CHARACTER_COLLECTION_SRC_CHAR_COLLECTION_HPP_
