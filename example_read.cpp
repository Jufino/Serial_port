#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
#include <serial.h>

struct GPGGA_struct{
	char UTCTime[9];
	float Latitude;
	char NSIndicator;
	float Longitude;
	char EWindicator;
	int PositionFixIndictor;
	int SatellitesUsed;
	float HDOP;
	float MSLAltitude;
	char Units1;
	int GeoidSeparation; 
	char Units2;
	int AgeofDifferentialCorrections;
	int DiffRefereceCorrections;
	char Checksum[3];
};
struct GPGLL_struct{
	float Latitude;
	char NSIndicator;
	float Longitude;
	char EWIndicator;
	char UTCTime[9];
	char Status;
	char ModeIndicator;
	char Checksum[3];
};
struct GPGSA_struct{
	char ModeChar;
	int ModeInt;
	int SatellitesUsedCH1;
	int SatellitesUsedCH2;
	int SatellitesUsedCH3;
        int SatellitesUsedCH4;
	int SatellitesUsedCH5;
        int SatellitesUsedCH6;
	int SatellitesUsedCH7;
        int SatellitesUsedCH8;
	int SatellitesUsedCH9;
        int SatellitesUsedCH10;
	int SatellitesUsedCH11;
        int SatellitesUsedCH12;
	float PDOP;
	float HDOP;
	float VDOP;
	char Checksum[3];
};
struct GPGSV_struct{
	int NumberOfMessages;
	int MessageNumber;
	int SatellitesInView;
	int SatelliteId1;
	int Elevation1;
	int Azimuth1;
	int SNR1;
	int SatelliteId2;
        int Elevation2;
        int Azimuth2;
        int SNR2;
	int SatelliteId3;
        int Elevation3;
        int Azimuth3;
        int SNR3;
	int SatelliteId4;
        int Elevation4;
        int Azimuth4;
        int SNR4;
	char Checksum[3];
};
struct GPRMC_struct{
	char UTCTime[9];
	char Status;
	float Latitude;
	char NSIndicator;
	float Longitude;
	char EWIndicator;
	float SpeedOverGround;
	float CourseOverGround;
	char Date[6];
	char Mode;
	char Checksum[3];
};
struct GPVTG_struct{
	float CourseTrue;
	char ReferenceTrue;
	float CourseMagnetic;
	char ReferenceMagnetic;
	float SpeedKnots;
	float SpeedKmh;
	char UnitsKnots;
	char UnitsKmh;
	char Mode;
	char Checksum[3];
};

GPGGA_struct GPGGA;
GPGLL_struct GPGLL;
GPRMC_struct GPRMC;
GPGSA_struct GPGSA;
GPGSV_struct GPGSV;
GPVTG_struct GPVTG;


int main()
{
	int portHandle = SerialOpen("/dev/ttyAMA0",B9600);	//Open port, device="/dev/ttyUSB0", baundrate=115200
	while(1){
	
	while(strcmp(SerialRead(portHandle,1),"$") != 0);
		char *dataCMD = SerialRead(portHandle,5);
//		printf("%s",dataCMD);
		int i = 0;
		int x = 0;
		char buffer[20];
		if(!strcmp(dataCMD,"GPVTG")){
			char data[] = {' '};
                        while(data[0] != '\n'){
                                char *datas = SerialRead(portHandle,1);
                                data[0] = datas[0];
                                if(data[0] == ','){
                                        buffer[x]='\0';
                                        switch(i++){
                                                case 1:  GPVTG.CourseTrue = atof(buffer);       break;
                                                case 3:  GPVTG.CourseMagnetic = atof(buffer);   break;
                                                case 5:  GPVTG.SpeedKnots = atoi(buffer);       break;
                                                case 7:  GPVTG.SpeedKmh = atof(buffer);          break;
                                        }
                                        x = 0;
                                }
                                else{
                                        switch(i){
                                                case 1:
						case 3:
						case 5: 
						case 7:  buffer[x++] = data[0];                 break;
                                                case 2:  GPVTG.ReferenceTrue = data[0];         break;
                                                case 4:  GPVTG.ReferenceMagnetic = data[0];     break;
                                                case 6:  GPVTG.UnitsKnots = data[0];           	break;
                                                case 8:  GPVTG.UnitsKmh = data[0];           	break;
                                                case 9:  GPVTG.Mode = data[0];   		break;
                                                case 10: GPVTG.Checksum[x++] = data[0];         break;

                                        }
                                }
                        }
		}
		else if(!strcmp(dataCMD,"GPGGA")){
			char data[] = {' '};
                        while(data[0] != '\n'){
                                char *datas = SerialRead(portHandle,1);
                                data[0] = datas[0];
				if(data[0] == ','){
					buffer[x]='\0';
					switch(i++){
                                                case 2:  GPGGA.Latitude = atof(buffer);			break;
                                                case 4:  GPGGA.Longitude = atof(buffer);  		break;
                                                case 7:  GPGGA.SatellitesUsed = atoi(buffer); 		break;
						case 8:  GPGGA.HDOP = atof(buffer); 			break;
                                                case 9:  GPGGA.MSLAltitude = atof(buffer); 		break;
                                                case 10: GPGGA.GeoidSeparation = atoi(buffer); 		break;
                                                case 12: GPGGA.AgeofDifferentialCorrections = atoi(buffer);break;                                                 
                                        }
                                        x = 0;
                                }
                                else{
                                        switch(i){
                                                case 1:  GPGGA.UTCTime[x++] = data[0];         break;
                                                case 2:
                                                case 7:
                                                case 8:
                                                case 9:
						case 4:  buffer[x++] = data[0];                 break;
						case 10: GPGGA.Units1 = data[0];		break;
						case 12: GPGGA.Units2 = data[0];		break;
                                                case 3:  GPGGA.NSIndicator = data[0];          	break;
                                                case 5:  GPGGA.EWindicator = data[0];           break;
                                                case 6:  GPGGA.PositionFixIndictor = data[0];  	break;
						case 13: GPGGA.Checksum[x++] = data[0];		break; 

                                        }
                                }
                        }
                }
		else if(!strcmp(dataCMD,"GPGSA")){
			char data[] = {' '};
                        while(data[0] != '\n'){
                                char *datas = SerialRead(portHandle,1);
                                data[0] = datas[0];
                                if(data[0] == ','){
                                        buffer[x]='\0';
                                        switch(i++){
                                                case 3:  GPGSA.SatellitesUsedCH1 = atoi(buffer); break;
						case 4:  GPGSA.SatellitesUsedCH2 = atoi(buffer); break;
						case 5:  GPGSA.SatellitesUsedCH3 = atoi(buffer); break;
						case 6:  GPGSA.SatellitesUsedCH4 = atoi(buffer); break;
						case 7:  GPGSA.SatellitesUsedCH5 = atoi(buffer); break;
						case 8:  GPGSA.SatellitesUsedCH6 = atoi(buffer); break;
						case 9:  GPGSA.SatellitesUsedCH7 = atoi(buffer); break;
						case 10:  GPGSA.SatellitesUsedCH8 = atoi(buffer); break;
						case 11:  GPGSA.SatellitesUsedCH9 = atoi(buffer); break;
						case 12:  GPGSA.SatellitesUsedCH10 = atoi(buffer); break;
						case 13:  GPGSA.SatellitesUsedCH11 = atoi(buffer); break;
						case 14:  GPGSA.SatellitesUsedCH12 = atoi(buffer); break;
						case 15:  GPGSA.PDOP = atof(buffer); break;
						case 16:  GPGSA.HDOP = atof(buffer); break;
						case 17:  GPGSA.VDOP = atof(buffer); break;
                                        }
                                        x = 0;
                                }
                                else{
                                        switch(i){
                                                case 1:	 GPGSA.ModeChar = data[0];	break;
                                                case 2:  GPGSA.ModeInt = data[0];      	break;
                                                case 3:	 
                                                case 4:  
						case 5:
						case 6:
						case 7:
						case 8:
						case 9:
						case 10:
						case 11:
						case 12:
						case 13:
						case 14:
						case 15:
						case 16:
						case 17:  buffer[x++] = data[0];         break;
                                                case 18:  GPGSA.Checksum[x++] = data[0]; break;
                                        }
                                }
                        }
                }
		else if(!strcmp(dataCMD,"GPGLL")){
			char data[] = {' '};
                        while(data[0] != '\n'){
                                char *datas = SerialRead(portHandle,1);
                                data[0] = datas[0];
                                if(data[0] == ','){
                                        buffer[x]='\0';
                                        switch(i++){
                                                case 1:  GPGLL.Latitude = atof(buffer);                 break;
                                                case 3:  GPGLL.Longitude = atof(buffer);                break;
                                        }
                                        x = 0;
                                }
                                else{
                                        switch(i){
                                                case 1:
						case 3:	 buffer[x++] = data[0];         break;
                                                case 2:  GPGLL.NSIndicator = data[0];	break;
						case 4:  GPGLL.EWIndicator = data[0];   break;
						case 5:  GPGLL.UTCTime[x++] = data[0];  break;
						case 6:  GPGLL.Status = data[0];  	break;
						case 7:  GPGLL.ModeIndicator = data[0]; break;
						case 8:  GPGLL.Checksum[x++] = data[0]; break;
                                        }
                                }
                        }
                }
		else if(!strcmp(dataCMD,"GPRMC")){
			char data[] = {' '};
                        while(data[0] != '\n'){
                                char *datas = SerialRead(portHandle,1);
                                data[0] = datas[0];
                                if(data[0] == ','){
                                        buffer[x]='\0';
                                        switch(i++){
                                                case 3:  GPRMC.Latitude = atof(buffer); break;
						case 5:  GPRMC.Longitude = atof(buffer); break;
						case 7:  GPRMC.SpeedOverGround = atof(buffer); break;
						case 8:  GPRMC.CourseOverGround = atof(buffer); break;
                                        }
                                        x = 0;
                                }
                                else{
                                        switch(i){
                                                case 1:  GPRMC.UTCTime[x++] = data[0];  break;
						case 2:  GPRMC.Status = data[0];        break;
						case 9:  GPRMC.Date[x++] = data[0];	break;
						case 5:
						case 7:
						case 8:
						case 3:  buffer[x++] = data[0];         break;
						case 10: GPRMC.Mode = data[0];		break;
						case 4:  GPRMC.NSIndicator = data[0];   break;
						case 6:  GPRMC.EWIndicator = data[0];   break;
						case 11: GPRMC.Checksum[x++] = data[0]; break;
                                        }
                                }
                        }
                }
		else if(!strcmp(dataCMD,"GPGSV")){
                        char data[] = {' '};
                        while(data[0] != '\n'){
                                char *datas = SerialRead(portHandle,1);
                                data[0] = datas[0];
                                if(data[0] == ','){
                                        buffer[x]='\0';
                                        switch(i++){
                                                case 1:  GPGSV.NumberOfMessages = atoi(buffer);	break;
                                                case 2:  GPGSV.MessageNumber = atoi(buffer);    break;
						case 3:  GPGSV.SatellitesInView = atoi(buffer); break;
						case 4:  GPGSV.SatelliteId1 = atoi(buffer);     break;
						case 5:  GPGSV.Elevation1 = atoi(buffer);    	break;
						case 6:  GPGSV.Azimuth1 = atoi(buffer);    	break;
						case 7:  GPGSV.SNR1 = atoi(buffer);    		break;
						case 8:  GPGSV.SatelliteId2 = atoi(buffer);    	break;
                                                case 9:  GPGSV.Elevation2 = atoi(buffer);    	break;
                                                case 10: GPGSV.Azimuth2 = atoi(buffer);    	break;
                                                case 11: GPGSV.SNR2 = atoi(buffer);    		break;
						case 12: GPGSV.SatelliteId3 = atoi(buffer);    	break;
                                                case 13: GPGSV.Elevation3 = atoi(buffer);    	break;
                                                case 14: GPGSV.Azimuth3 = atoi(buffer);    	break;
                                                case 15: GPGSV.SNR3 = atoi(buffer);    		break;
						case 16: GPGSV.SatelliteId4 = atoi(buffer);    	break;
                                                case 17: GPGSV.Elevation4 = atoi(buffer);    	break;
                                                case 18: GPGSV.Azimuth4 = atoi(buffer);    	break;
                                                case 19: GPGSV.SNR4 = atoi(buffer);    		break;
                                        }
                                        x = 0;
                                }
                                else{
                                        switch(i){
                                                case 1:
						case 2:
						case 3:
				  		case 4:
						case 5:
						case 6:
						case 7:
						case 8:
						case 9:
						case 10:
						case 11:
						case 12:
						case 13:
						case 14:
						case 15:
						case 16:
						case 17:
						case 18:
						case 19:  buffer[x++] = data[0];         break;
                                                case 20:  GPGSV.Checksum[x++] = data[0]; break;
                                        }
                                }
                        }
                }
		printf("%d\n",GPGSA.SatellitesUsedCH1);
	}
	SerialClose(portHandle);				//close port
}
