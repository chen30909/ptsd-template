#ifndef IMAGECACHE_HPP
#define IMAGECACHE_HPP

#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "Util/Image.hpp"

class ImageCache {
public:
    static std::shared_ptr<Util::Image> Get(const std::string& path) {
        if (cache.find(path) == cache.end()) {
            cache[path] = std::make_shared<Util::Image>(path);
        }
        return cache[path];
    }

    static void Clear() {
        cache.clear();
    }

private:
    static inline std::unordered_map<std::string, std::shared_ptr<Util::Image>> cache;
};

#endif // IMAGECACHE_HPP
