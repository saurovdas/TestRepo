#include <stdio.h>
#include <string.h>

#define NTP_CONFIG_PATH_FILENAME "ntp.conf"
#define MAX_LINE_SIZE 1000

void SetDefaultNtpServerConfig ()
{
	FILE	*FPtr ;
	char	Buffer [4000] ;
	char	Line [MAX_LINE_SIZE] ;
	char	*BuffPtr ;
	char	*Ptr ;
		
	BuffPtr = Buffer ;
	if ((FPtr = fopen (NTP_CONFIG_PATH_FILENAME, "r")) != NULL)
	{
		while (((fgets (Line, MAX_LINE_SIZE, FPtr)) != NULL))
		{
			if ((Line [0] != '#') && (strncmp (Line, "server", 6) == 0))
				continue ;

			if (strncmp (Line, "#server", 7) == 0)
			{
				Ptr = Line + 1 ;
				BuffPtr += sprintf (BuffPtr, "%s", Ptr) ;
			}
			else
				BuffPtr += sprintf (BuffPtr, "%s", Line) ;
		}

		fclose (FPtr) ;
	}
	
	if ((FPtr = fopen (NTP_CONFIG_PATH_FILENAME, "w")) != NULL)
	{
		fwrite (Buffer, sizeof (char), strlen (Buffer), FPtr) ;
		fclose (FPtr) ;
	}
}

void UpdateNtpServerConfig (char *CustomNtpServer)
{
	FILE	*FPtr ;
	char	Buffer [4000] ;
	char	Line [MAX_LINE_SIZE] ;
	char	*BuffPtr ;
	char	*Ptr ;
	char	Flag = 0 ;
		
	BuffPtr = Buffer ;
	if ((FPtr = fopen (NTP_CONFIG_PATH_FILENAME, "r")) != NULL)
	{
		while (((fgets (Line, MAX_LINE_SIZE, FPtr)) != NULL))
		{
			if ((Line [0] != '#') && (strncmp (Line, "server", 6) == 0))
			{
				if (! Flag)
				{
					BuffPtr += sprintf (BuffPtr, "server %s\n", CustomNtpServer) ;
					Flag = 1 ;
				}
			}
			else
				BuffPtr += sprintf (BuffPtr, "%s", Line) ;
		}

		fclose (FPtr) ;
	}
	
	if ((FPtr = fopen (NTP_CONFIG_PATH_FILENAME, "w")) != NULL)
	{
		fwrite (Buffer, sizeof (char), strlen (Buffer), FPtr) ;
		fclose (FPtr) ;
	}
}

void main ()
{
	UpdateNtpServerConfig ("saurov.ntp.org") ;
//	SetDefaultNtpServerConfig () ;
}
