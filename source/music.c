#include <3ds.h>

#include "music.h"

static const size_t buffSize = 44100;

Result initSound(u16 sample_rate)
{
	Result res;
	res = ndspInit();
	if (R_FAILED(res)) return res;

	ndspChnReset(0);
	ndspChnWaveBufClear(0);
	ndspSetOutputMode(NDSP_OUTPUT_STEREO);
	ndspChnSetInterp(0, NDSP_INTERP_POLYPHASE);
	ndspChnSetRate(0, sample_rate);
	ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);
	return 0;
}

int initVorbis(const char *path, OggVorbis_File *vorbisFile, vorbis_info **vi)
{
	int ov_res;
	FILE *f = fopen(path, "rb");
	if (f == NULL) return 1;

	ov_res = ov_open(f, vorbisFile, NULL, 0);
	if (ov_res < 0) {
		fclose(f);
		return ov_res;
	}

	*vi = ov_info(vorbisFile, -1);
	if (*vi == NULL) return 3;

	return 0;
}

size_t fillVorbisBuffer(int16_t *buf, size_t samples, OggVorbis_File *vorbisFile)
{
	size_t samplesRead = 0;
	int samplesToRead = samples;

	while(samplesToRead > 0)
	{
		int current_section;
		int samplesJustRead =
			ov_read(vorbisFile, (char*)buf,
					samplesToRead > 4096 ? 4096	: samplesToRead,
					&current_section);

		if(samplesJustRead < 0)
			return samplesJustRead;
		else if(samplesJustRead == 0)
			break;
			/* End of file reached. */

		samplesRead += samplesJustRead;
		samplesToRead -= samplesJustRead;
		buf += samplesJustRead / 2;
	}

	return samplesRead / sizeof(int16_t);
}

void soundThread(void *arg) {
	
	//printf("Hello from sound thread!\n");

	OggVorbis_File *vorbisFile = (OggVorbis_File*)arg;
	ndspWaveBuf waveBuf[2];
	int16_t *samplebuf;
	int cur_wvbuf = 0;
	
	samplebuf = linearAlloc(buffSize * sizeof(int16_t) * 2);
	memset(waveBuf, 0, sizeof(waveBuf));

	waveBuf[0].data_vaddr = samplebuf;
	waveBuf[1].data_vaddr = samplebuf + buffSize;

	waveBuf[0].status = NDSP_WBUF_DONE;
	waveBuf[1].status = NDSP_WBUF_DONE;
	
	//svcSleepThread(100*1000); // hack

	while(runSound) {
		while(runSound && !playSound)
			svcSleepThread(10e9 / 60);

		int16_t *cursamplebuf = (int16_t*)waveBuf[cur_wvbuf].data_vaddr;

		waveBuf[cur_wvbuf].nsamples = fillVorbisBuffer(cursamplebuf, buffSize, vorbisFile) / 2;
		if (waveBuf[cur_wvbuf].nsamples == 0) break;

		DSP_FlushDataCache(cursamplebuf, buffSize * sizeof(int16_t));
		ndspChnWaveBufAdd(0, &waveBuf[cur_wvbuf]);

		cur_wvbuf ^= 1;
		while(waveBuf[cur_wvbuf].status != NDSP_WBUF_DONE && runSound)
			svcSleepThread(10e9 / (buffSize*4));
	}

	// cleanup
	ndspChnWaveBufClear(0);
	ndspExit();
	linearFree(samplebuf);
	//printf("Bye!\n");
	runSound = 0;
	threadExit(0);
}



void threadPlayStopHook(APT_HookType hook, void *param)
{
	switch(hook) {
		case APTHOOK_ONSUSPEND:
		case APTHOOK_ONSLEEP:
			playSound = 0;
			break;

		case APTHOOK_ONRESTORE:
		case APTHOOK_ONWAKEUP:
			playSound = 1;
			break;

		case APTHOOK_ONEXIT:
			runSound = playSound = 0;
			break;

		default:
			break;
	}
}

volatile u32 runSound, playSound;

s32 main_prio;
Thread snd_thr;
aptHookCookie thr_playhook;

OggVorbis_File vorbisFile;
vorbis_info *vi;

int init_audio_1st = 0;

int i = 0;


char songs[] = {"romfs:/ff7.ogg"};

void initAudio()
{	int max = ((sizeof(songs) / sizeof(char*))-1);

	if (i > max) i=0;
	if (i < 0) i=max;

	if ((initVorbis(&songs[i], &vorbisFile, &vi)) != 0) {
		return;
	}
	initSound(vi->rate);
	if (init_audio_1st == 0) {
		svcGetThreadPriority(&main_prio, CUR_THREAD_HANDLE);
		if (main_prio < 2) svcBreak(USERBREAK_ASSERT);

		aptHook(&thr_playhook, threadPlayStopHook, NULL);

		APT_SetAppCpuTimeLimit(30);
		init_audio_1st=init_audio_1st+1;
	}

	runSound = playSound = 1;
	snd_thr = threadCreate(soundThread, &vorbisFile, 32768, main_prio, 1, true);
}

void stopAudio()
{
	runSound = playSound = 0;
	threadJoin(snd_thr, U64_MAX);
	threadDetach(snd_thr); // Fixes the crash that occurs when you switch too fast, probably because we kept adding threads over threads
	aptUnhook(&thr_playhook);
	fclose((FILE*)(vorbisFile.datasource)); /* hack */
}