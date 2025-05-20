//
// Created by xzy54 on 2025/5/5.
//
#pragma once
#ifndef SLIMENANO_CHARACTER_COLLECTION_SRC_COLLECTIONS_CHAR_COLLECTION_SET_HPP_
#define SLIMENANO_CHARACTER_COLLECTION_SRC_COLLECTIONS_CHAR_COLLECTION_SET_HPP_

#include "slimenano/slimenano_api.hpp"
#include "slimenano/char_collection.hpp"

namespace slimenano {

    class SLIMENANO_API_ char_collection_set final : public char_collection {

    public:
        char_collection_set();
        char_collection_set(const uint32_t* charset, size_t size);
        ~char_collection_set() override = default;

        auto contains(const uint32_t& character) const -> bool override;
    private:

    };


}

#endif //SLIMENANO_CHARACTER_COLLECTION_SRC_COLLECTIONS_CHAR_COLLECTION_SET_HPP_