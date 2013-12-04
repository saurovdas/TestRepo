#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static void time_convert(time_t t0, char const *tz_value)
{
    char old_tz[1164];
    char buffer[1164];
    char new_tz[1164];
    struct tm *lt ;
    strcpy(old_tz, getenv("TZ"));
    setenv("TZ", tz_value, 1);
    tzset();

    strcpy(new_tz, getenv("TZ"));

	lt = localtime(&t0);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", lt);
    setenv("TZ", old_tz, 1);
    tzset();
    printf("%ld = %s (TZ=%s)\n", (long)t0, buffer, new_tz);
}

void ParseDateTime (char *UnixTime, char *Date, char *Time)
{
	time_t			ScheduledTime = 0 ;
	struct tm 		*Newtime ;
	char			Buffer [32] ;

	memset (Buffer, 0, sizeof (Buffer)) ;

	ScheduledTime = atol (UnixTime) ;
	Newtime = localtime (&ScheduledTime) ;

	strftime (Buffer, 32, "%Y-%m-%d", Newtime) ;
	Buffer [31] = '\0' ;
	strcpy (Date, Buffer) ;
	printf ("\nLocal: %s %s\n", Date, Buffer) ;

	strftime(Buffer, 32, "%H:%M:%S", Newtime) ;
	Buffer [31] = '\0' ;
	strcpy (Time, Buffer) ;
}

int main(void)
{
	char	SchdDate [32] ;
	char	SchdTime [8] ;
		char	Buffer [64] = "1386112080" ;
		printf ("\nUnix date : %s\n", Buffer) ;
		ParseDateTime (Buffer, SchdDate, SchdTime) ;

		printf ("\ndate : %s, %s, %s\n", Buffer, SchdDate, SchdTime) ;
//    time_convert(t0, "UTC0");
//    time_convert(t0, "IST-5:30");
 //   time_convert(t0, "EST5");
 //   time_convert(t0, "EST5EDT");
 //   time_convert(t0, "PST8");
 //   time_convert(t0, "PST8PDT");
}

#if 0
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main() {
 // tzset();
  printf("%lu, %d, %s, %s\n", timezone, daylight, tzname[0], tzname[1]);
 tzset();
  printf("%lu, %d, %s, %s\n", timezone, daylight, tzname[0], tzname[1]);
setenv("TZ", "MST7MDT", 1);
 tzset();
  printf("%lu, %d, %s, %s\n", timezone, daylight, tzname[0], tzname[1]);

  return 0;
}


int main()
{
   struct timeval tv;
	struct timezone tz;

   gettimeofday(&tv, &tz);

	printf ("Time dst: %d, %d\n", tz.tz_dsttime, tz.tz_minuteswest) ;
   // add 3 hours (3 * 60 mins * 60 secs) to current time

  // settimeofday(&tv, 0);

   return 0;
}



int main(void)
{
    time_t t;
    struct tm *tm;
    char buf[BUFSIZ];

    int offset = 360; /* slightly bizarre, just to test this - an hour
                        * and 23 minutes ahead of UTC */

    t = time(NULL);
    tm = localtime(&t);

    strftime(buf, BUFSIZ, "%FT %T %z", tm);
    printf("before: %s\n", buf);

    /* since we're not telling localtime anything different,
     * compensate here (by subtracting applied offset, and adding
     * desired one): */
    t += offset - tm->tm_gmtoff;
    tm = localtime(&t);

    tm->tm_zone = "XYZ"; // not used -- but it was in an earlier version
    tm->tm_gmtoff = offset;

    // on macos, I used to also have %+, which referenced tm_zone
    strftime(buf, BUFSIZ, "%FT %T %z", tm);
    printf("after:  %s\n", buf);

    return 0;
}
#endif
