/* Use the newer ALSA API */
#define ALSA_PCM_NEW_HW_PARAMS_API

#include <liqbase/liqbase.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>
#include <liqbase/liqcell_easyhandler.h>

extern int liqcell_easyrun_fingerpressed;

#define ABS(x)  ((x)<0 ? -(x) : (x))

#include <alsa/asoundlib.h>





void filter(signed short *buffer, int size,liqcell *liqmic_run) {
	int i, out=0;
	static signed short a[64];
	
	static signed int gb[64]={0};

	int na=0;
	for(i = 0 ; i < 128 ; i++)
		na += ABS(buffer[i]);
		
	na/=128;
		
	
	for(i = 0 ; i < 128 ; i++)
		if(ABS(buffer[i])<30) gb[i%64] += buffer[i];
		
	
	for(i = 0 ; i < 64 ; i++)
		out += ABS(gb[i]) / 64;
		

/*
	//liqapp_log("hello aaa, %i",size);

	if(size!=128) {
		fprintf(stderr, "size %d\n", size);
		return;
	}
	


	
	//for(i = 0 ; i < 128 ; i++)
	//	a[i%32] += buffer[i]/32;

	for(i = 0 ; i < 32 ; i++)
		out += (a[i] > 0) ? a[i] : -a[i];
	
	
*/
	
	out *=400; //79;
	out /= (0x7fff) * 32;
	
	out=400-out;
	
	
//	out = 240 + (((int)a[0] * 480  / 65535));

	liqcell *title = liqcell_child_lookup(liqmic_run, "title");

	liqcell *backplane = liqcell_child_lookup(liqmic_run, "backplane");
		liqcell *canvas = liqcell_child_lookup(backplane, "canvas");
		
		
	liqsketch *sketch = liqcell_getsketch(canvas);
		
	unsigned long 	mt=liqapp_GetTicks();
	
	
	//int aax = rand() % 480;
	int aax = out;

    liqstroke *stroke;
	
	#define ssss 2
	
	
	
	liqcell_setcaption_printf(title,"%-4i %i",out,buffer[0]);
	
	
	sketch->pixelheight+=ssss;
    
    //#################################
    stroke = sketch->strokefirst;
    if(!stroke)
    {
		//liqapp_log("starting stroke %i,%i",canvas->w,aax);
			stroke = liqstroke_new();
			stroke->pen_y = 255;
			stroke->pen_u = 128;
			stroke->pen_v = 128;
            liqstroke_start(stroke,canvas->w,aax,100,mt);
            liqsketch_strokeinsert(sketch,stroke);
    }
    else
    {
		//liqapp_log("extending stroke %i,%i",canvas->w,aax);
            liqstroke_extend(stroke,canvas->w,aax,100,mt);
			liqsketch_strokeupdate(sketch,stroke);
    }


    //#################################
	
	int arg = 200 + (buffer[0] * 400 / 65535) + (((canvas->w % 32) == 0) ? 100 : 0);
    stroke = stroke->linknext;
    if(!stroke)
    {
			stroke = liqstroke_new();
			stroke->pen_y = 255;
			stroke->pen_u = 30;
			stroke->pen_v = 128;
            liqstroke_start(stroke,canvas->w,arg,100,mt);
            liqsketch_strokeinsert(sketch,stroke);
    }
    else
    {
            liqstroke_extend(stroke,canvas->w,arg,100,mt);
			liqsketch_strokeupdate(sketch,stroke);
    }
	
    //#################################
	
	na = na * 400 / 65535;
    stroke = stroke->linknext;
    if(!stroke)
    {
			stroke = liqstroke_new();
			stroke->pen_y = 255;
			stroke->pen_u = 30;
			stroke->pen_v = 128;
            liqstroke_start(stroke,canvas->w,na,100,mt);
            liqsketch_strokeinsert(sketch,stroke);
    }
    else
    {
            liqstroke_extend(stroke,canvas->w,na,100,mt);
			liqsketch_strokeupdate(sketch,stroke);
    }   


    if( liqcell_easyrun_fingerpressed || canvas->kineticx)
	{
		
         
	}
	else
	{
		if((canvas->x + canvas->w) == backplane->w)
		{
			canvas->x-=ssss;
		}
	}
    canvas->w+=ssss;
    
    
    
    liqcell_setdirty(canvas,1);

//	fprintf(stderr, "  ------------                                                                        \r", out);
	//for(i = 0 ; i < out ; i++)
	//	fprintf(stderr, "#", out);
	//fprintf(stderr, "\n", out);

}

int listen_main(liqcell *liqmic_run) {
  long loops;
  int rc;
  int size;
  snd_pcm_t *handle;
  snd_pcm_hw_params_t *params;
  unsigned int val;
  int dir;
  snd_pcm_uframes_t frames;
  char *buffer;

  /* Open PCM device for recording (capture). */
  rc = snd_pcm_open(&handle, "default",
                    SND_PCM_STREAM_CAPTURE, 0);
  if (rc < 0) {
    fprintf(stderr,
            "unable to open pcm device: %s\n",
            snd_strerror(rc));
    exit(1);
  }

  /* Allocate a hardware parameters object. */
  snd_pcm_hw_params_alloca(&params);

  /* Fill it in with default values. */
  snd_pcm_hw_params_any(handle, params);

  /* Set the desired hardware parameters. */

  /* Interleaved mode */
  snd_pcm_hw_params_set_access(handle, params,
                      SND_PCM_ACCESS_RW_INTERLEAVED);

  /* Signed 16-bit little-endian format */
  snd_pcm_hw_params_set_format(handle, params,
                              SND_PCM_FORMAT_S16_LE);

  /* Two channels (stereo) */
  snd_pcm_hw_params_set_channels(handle, params, 1);

  /* 44100 bits/second sampling rate (CD quality) */
  val = 44100;
  snd_pcm_hw_params_set_rate_near(handle, params,
                                  &val, &dir);

  /* Set period size to 32 frames. */
  frames = 32;
  snd_pcm_hw_params_set_period_size_near(handle,
                              params, &frames, &dir);

  /* Write the parameters to the driver */
  rc = snd_pcm_hw_params(handle, params);
  if (rc < 0) {
    fprintf(stderr,
            "unable to set hw parameters: %s\n",
            snd_strerror(rc));
    exit(1);
  }

  /* Use a buffer large enough to hold one period */
  snd_pcm_hw_params_get_period_size(params,
                                      &frames, &dir);
  size = frames * 4; /* 2 bytes/sample, 2 channels */
  buffer = (char *) malloc(size);

  /* We want to loop for 5 seconds */
  snd_pcm_hw_params_get_period_time(params,
                                         &val, &dir);
  loops = 5000000 / val;

  while (loops > 0) {
//    loops--;
    rc = snd_pcm_readi(handle, buffer, frames);
	
    if (rc == -EPIPE) {
      /* EPIPE means overrun */
      //fprintf(stderr, "overrun occurred\n");
      snd_pcm_prepare(handle);
    } else if (rc < 0) {
      //fprintf(stderr,
      //        "error from read: %s\n",
      //        snd_strerror(rc));
    } else if (rc != (int)frames) {
      //fprintf(stderr, "short read, read %d frames\n", rc);
    }
	
	
	filter((signed short *)buffer, size>>1,liqmic_run);
	
    //rc = write(1, buffer, size);
    //if (rc != size)
    //  fprintf(stderr,
    //          "short write: wrote %d bytes\n", rc);
  }

  snd_pcm_drain(handle);
  snd_pcm_close(handle);
  free(buffer);

  return 0;
}

