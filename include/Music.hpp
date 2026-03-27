#pragma once

#include "pch.hpp"
#include "Global.hpp"
#include "Util/BGM.hpp"
#ifndef UTIL_MUSIC_HPP
#define UTIL_MUSIC_HPP


class Music : public Util::BGM {
public:
    explicit Music(const std::string& path) : BGM(path) {}

    void Playing( std::string path ) {
        this->Pause();
        this->LoadMedia( path );
        this->SetVolume( 10 );
        this->FadeIn(1000);
    }
};

#endif // UTIL_MUSIC_HPP

