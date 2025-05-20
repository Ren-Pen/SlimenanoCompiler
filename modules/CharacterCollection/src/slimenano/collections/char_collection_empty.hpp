//
// Created by xzy54 on 2025/5/3.
//
#pragma once
#ifndef SLIMENANO_CHARACTER_COLLECTION_SRC_COLLECTIONS_CHAR_COLLECTION_EMPTY_HPP_
#define SLIMENANO_CHARACTER_COLLECTION_SRC_COLLECTIONS_CHAR_COLLECTION_EMPTY_HPP_
#include "slimenano/slimenano_api.hpp"
#include "slimenano/char_collection.hpp"

namespace slimenano {

    class SLIMENANO_API_ char_collection_empty final : public char_collection {
    public:
        char_collection_empty() = default;
        ~char_collection_empty() override = default;

        auto contains(const uint32_t& character) const -> bool override;
    };


}


#endif //SLIMENANO_CHARACTER_COLLECTION_SRC_COLLECTIONS_CHAR_COLLECTION_EMPTY_HPP_