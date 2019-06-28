#ifndef VIDEOHELPER_H_INCLUDED
#define VIDEOHELPER_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <string>


class AudioHelper {
private:
	VideoHelper() = default;
public:
	static ALLEGRO_SAMPLE_ID PlayVideo(const std::string& audio);
};

#endif // VIDEOHELPER_H_INCLUDED
