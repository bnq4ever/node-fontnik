/*****************************************************************************
 *
 * Copyright (C) 2014 Mapbox
 *
 * This file is part of Fontnik.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef FONTNIK_PARAMS_HPP
#define FONTNIK_PARAMS_HPP

// variant
#include <variant/variant.hpp>

// stl
#include <vector>
#include <map>

namespace fontnik
{

enum class ParamKey {
    Fontstack = 0,
    Range = 1,
    Chars = 2,
    FontSize = 3,
    Granularity = 4
};

typedef mapbox::util::variant<std::string,
                              uint32_t,
                              std::vector<uint32_t>> ParamValue;

class Params {
public:
    inline Params() : params() {}
    inline Params(Params &&params)
        : params(std::move(params.params)) {}

    template <typename T>
    inline const T *get(ParamKey key) const {
        const auto it = params.find(key);
        if (it != params.end() && it->second.is<T>()) {
            return ::std::addressof(it->second.get<T>());
        } else {
            return nullptr;
        }
    }

    template <typename ...Args>
    inline void emplace(Args&& ...args) {
        params.emplace(::std::forward<Args>(args)...);
    }

private:
    std::map<ParamKey, ParamValue> params;
};

} // ns fontnik

#endif // FONTNIK_PARAMS_HPP
