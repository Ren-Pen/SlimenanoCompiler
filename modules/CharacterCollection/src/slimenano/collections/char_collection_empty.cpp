//
// Created by xzy54 on 2025/5/3.
//
#include <slimenano/collections/char_collection_empty.hpp>

namespace slimenano {

    auto char_collection_empty::contains(const uint32_t& character) const -> bool {
        UNUSED(character);
        return false;
    }

}