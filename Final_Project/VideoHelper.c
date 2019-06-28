#include <allegro5/allegro_video.h>
#include <memory>
#include "VideoHelper.hpp"
#include "LOG.hpp"
#include "Resources.hpp"

ALLEGRO_SAMPLE_ID VideoHelper::PlayVideo(const std::string& video) {
	// Not a safe way, however we only free while change scene, so it's fine.
	ALLEGRO_VIDEO* sample = *al_open_video(video);
	al_init_video_addon(void);
	ALLEGRO_SAMPLE_ID id;
	if (!al_start_video(sample, ))
		Engine::LOG(Engine::INFO) << "failed to play audio (once)";
	else
		Engine::LOG(Engine::VERBOSE) << "played audio (once)";
	return id;
}

