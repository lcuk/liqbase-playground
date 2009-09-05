
#include <liqbase/liqbase.h>
#include <liqbase/liqapp_prefs.h>
#include <liqbase/liqcell.h>
#include <liqbase/liqcell_prop.h>
#include <liqbase/liqcell_easyrun.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/stat.h>


#include <curl/curl.h>

#ifndef CURLOPT_COPYPOSTFIELDS
#define CURLOPT_COPYPOSTFIELDS 10165
#endif

struct curl_memorybuffer
{
	char *memory;
	size_t size;
};


static size_t curl_memorybuffer(void *ptr, size_t size, size_t nmemb, void *data)
{
	struct curl_memorybuffer *mem = (struct curl_memorybuffer *)data;
	int realsize = size * nmemb;

	mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory)
	{
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}




/**	
 * send a tweet to the settings stored in liqbase prefs
 */	


int liqtwit_sendtweet(char *twitmessage)
{

	//#################################################
	liqapp_log("liqtwit: looking up twituser credentials");
	char *twitname = liqapp_pref_getvalue("twitname");
	char *twitpass = liqapp_pref_getvalue("twitpass");
	if(twitname && *twitname  && twitpass && *twitpass)
	{
		// ok
	}
	else
	{
		liqapp_log("liqtwit: twitname and twitpass liqbase preference required");
		return -1;
	}
	
	//#################################################
	liqapp_log("liqtwit: constructing auth string for '%s'",twitname);
	char twitauth[256]={0};
	snprintf(twitauth,sizeof(twitauth)-1,"%s:%s",twitname,twitpass);

	//#################################################
	liqapp_log("liqtwit: building status post message");
	char twitpostfields[512]={0};
	snprintf(twitpostfields,sizeof(twitpostfields)-1,"status=%s",twitmessage);

	//#################################################
	liqapp_log("liqtwit: starting libcurl");
	CURL* easyhandle = curl_easy_init();	
	if(!easyhandle)
	{
		liqapp_log("liqtwit: curl_easy_init() failed ");
		return -1;
	}
	

	struct curl_memorybuffer resultchunk = {NULL,0};
	
	//#################################################
	liqapp_log("liqtwit: preparing curl parameters");
	
	curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, curl_memorybuffer);
	curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, (void *)&resultchunk);		
	curl_easy_setopt(easyhandle, CURLOPT_URL, "http://twitter.com/statuses/update.xml");
	curl_easy_setopt(easyhandle, CURLOPT_USERPWD,twitauth);
	curl_easy_setopt(easyhandle, CURLOPT_POST,1);
	curl_easy_setopt(easyhandle, CURLOPT_COPYPOSTFIELDS,twitpostfields);
			
			
			
	
			
	//#################################################
	liqapp_log("liqtwit: setting up easyheaderlist (fix for vdvsx bug '417 Expectation Failed')");
	static const char easyheaderlist_buf[] = "Expect:";
	struct curl_slist *easyheaderlist = NULL;
	easyheaderlist = curl_slist_append(easyheaderlist, easyheaderlist_buf);
	if(!easyheaderlist)
	{
		liqapp_log("liqtwit: could not alloc easyheaderlist");
		curl_easy_cleanup(easyhandle);
		return -1;
	}
	
	//#################################################
	liqapp_log("liqtwit: setting up timeout");
	curl_easy_setopt(easyhandle,  CURLOPT_CONNECTTIMEOUT, 5L);
	curl_easy_setopt(easyhandle,  CURLOPT_TIMEOUT,        15L);
	curl_easy_setopt(easyhandle,  CURLOPT_NOSIGNAL,       1);


	
	//#################################################
	liqapp_log("liqtwit: assigning HTTP headers");
	curl_easy_setopt(easyhandle, CURLOPT_HTTPHEADER, easyheaderlist);
	
	
	//#################################################
	liqapp_log("liqtwit: executing curl query");
	int curlerr = curl_easy_perform(easyhandle);

	//#################################################
	liqapp_log("liqtwit: curl preform returned: %i, isnull(resmem)=%i",curlerr, (resultchunk.memory==NULL));

	if(curlerr==0 && resultchunk.memory)
	{
		// w00t!
		liqapp_log("liqtwit: result data: %s",resultchunk.memory);
		// parse the result.  numeric code and returnid expected
		// the numeric code should indicate ok!
		// the returnid is contained within the 2nd line
	}
	
	//#################################################
	liqapp_log("liqtwit: cleanup");
	curl_easy_cleanup(easyhandle);
	curl_slist_free_all(easyheaderlist);
	
	if(resultchunk.memory)
	{
		liqapp_log("liqtwit: releasing chunk memory");
		free(resultchunk.memory);
	}
	liqapp_log("liqtwit: complete");
	return curlerr;

}




/*
00:33:39 #################################### liqcell easyrun (800,480) :: ctrlonemessage1
00:33:40 click test 'ctrlonemessage1.cmdsubmit'
00:33:40 click run 'cmdsubmit'
00:33:40 liqtwit: looking up twituser credentials
00:33:40 liqtwit: constructing auth string
00:33:40 liqtwit: building status post message
00:33:40 liqtwit: starting libcurl
00:33:40 liqtwit: preparing curl parameters
00:33:40 liqtwit: executing curl query
00:33:41 liqtwit: curl result: 0, isnull(resmem)=0
00:33:41 liqtwit: res: <?xml version="1.0" encoding="UTF-8"?>
<status>
  <created_at>Thu Aug 06 23:36:12 +0000 2009</created_at>
  <id>3171025187</id>
  <text>hello world!  1.0</text>
  <source>&lt;a href="http://apiwiki.twitter.com/"&gt;API&lt;/a&gt;</source>
  <truncated>false</truncated>
  <in_reply_to_status_id></in_reply_to_status_id>
  <in_reply_to_user_id></in_reply_to_user_id>
  <favorited>false</favorited>
  <in_reply_to_screen_name></in_reply_to_screen_name>
  <user>
    <id>17063182</id>
    <name>Gary Birkett</name>
    <screen_name>lcuk</screen_name>
    <location></location>
    <description></description>
    <profile_image_url>http://s3.amazonaws.com/twitter_production/profile_images/106703019/lcuk_avatar_normal.jpg</profile_image_url>
    <url></url>
    <protected>false</protected>
    <followers_count>34</followers_count>
    <profile_background_color>9ae4e8</profile_background_color>
    <profile_text_color>000000</profile_text_color>
    <profile_link_color>0000ff</profile_link_color>
    <profile_sidebar_fill_color>e0ff92</profile_sidebar_fill_color>
    <profile_sidebar_border_color>87bc44</profile_sidebar_border_color>
    <friends_count>17</friends_count>
    <created_at>Thu Oct 30 11:00:16 +0000 2008</created_at>
    <favourites_count>0</favourites_count>
    <utc_offset></utc_offset>
    <time_zone></time_zone>
    <profile_background_image_url>http://static.twitter.com/images/themes/theme1/bg.gif</profile_background_image_url>
    <profile_background_tile>false</profile_background_tile>
    <statuses_count>94</statuses_count>
    <notifications>false</notifications>
    <verified>false</verified>
    <following>false</following>
  </user>
</status>

00:33:41 liqtwit: complete
00:33:51 Waking!...-230262011,-230252000
00:34:01 Waking!...-230251989,-230241977




*/
