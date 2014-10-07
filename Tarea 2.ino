#include <SdFat.h>					// Import SD card Lib
#include <SdFatUtil.h>				
#include <SFEMP3Shield.h>
#include <SPI.h>


uint8_t track_num = 0;
uint8_t last_track = 0;
uint32_t t_pos = 0;
uint8_t orden = 0;
bool coincide = false;
String artista = "";

SdFat sd;	
const int chipSelect = 9;								
SFEMP3Shield MP3player;	

void setup(){
	Serial.begin(115200);
	sd.begin(chipSelect,SPI_HALF_SPEED);	
	MP3player.begin();
	
}



String preguntar_artista(){
	Serial.println("Cual de los siguientes artistas desea escuchar?");
	Serial.println("50cent");
	Serial.println("Akon");
	Serial.println("Nelly");
	Serial.println("si desea cambiar el artista escriba (parar) en cualquier momento");
	//String artista = "";
	while(artista == ""){
    artista = leer_respuesta();// statement
}
return artista;
}


String leer_respuesta()
{
	String respuestausuario = "";
	while(Serial.available())                        
	{                    
	   respuestausuario.concat(char(Serial.read()));                   // statement
	   delay(10);
	}
	return respuestausuario;
}

boolean rep_aleatoria(){
	Serial.println("Desea una reproduccion aleatoria (si/no)");
	bool aleatorio = false;
	String respuesta = "";
	while(respuesta == ""){
		respuesta = leer_respuesta();
	}
	if(respuesta == "si"){
		aleatorio = true;
	}
	else if (respuesta == "no"){
		aleatorio = false;
	}
	return aleatorio;
}


void canciones_artista(){
	Serial.print('\n');
	Serial.println("Las canciones disponibles del artista seleccionado son: ");
    Serial.print('\n');
	if(artista == "50 Cent"){
	    Serial.println("track 1");
	    Serial.println("track 2");
	    Serial.println("track 3");
	   
	}

	if(artista == "Akon"){
	    Serial.println("track 4");
	    Serial.println("track 5");
	    Serial.println("track 6");
	  
	}

	if(artista == "Nelly"){
	    Serial.println("track 7");
	    Serial.println("track 8");
	    Serial.println("track 9");
	   
	}
}

uint8_t verificar_artista(uint8_t last_track){

bool rep = false;


while(artista == ""){
    artista = preguntar_artista();
}

while(coincide == false){
	randomSeed(millis());
	track_num = random(1,8.99);

	while(track_num == last_track){
	    track_num = random(1,8.99);// statement
	}

	char buffer[16];
	MP3player.playTrack(track_num);
    MP3player.trackArtist(buffer);
    MP3player.stopTrack();

    if(String (buffer) == String (artista)){
    	rep = true;
        coincide = true; 
    }
}

	while(rep == true){
        MP3player.playTrack(track_num);
        canciones_artista();
        char buffer [16];
        MP3player.trackTitle(buffer);
        Serial.print("track ");
        Serial.print(track_num);
        Serial.print(":  ");
        Serial.println(buffer);
        

	while(MP3player.isPlaying()){
	    String ordenu = leer_respuesta();// statement

	    if(ordenu == "cambiar artista"){
	    	rep = false;
	    	artista = "";
	    	coincide = false;
	    	MP3player.stopTrack();
	    }

	    if(ordenu == "siguiente"){
	    	rep = false;
	    	coincide = false;
	    	last_track = track_num;
	    	MP3player.stopTrack(); 	
	    }
        
        if(ordenu == "pausar"){
	    	MP3player.pauseMusic();
	    }

	    if(ordenu == "parar"){
	    	rep = false;
	    	MP3player.stopTrack();
	    }

	    if(ordenu == "continuar"){
	    	MP3player.resumeMusic();
	    }

	}
}

}



//String artista = "";

void loop()
{
 


verificar_artista(last_track);



}




/*bool intervenir(String ordenu,bool rep){

	   
	    if(ordenu == "pausar"){
	    	MP3player.pauseMusic();
	    }

	    if(ordenu == "parar"){
	    	MP3player.stopTrack();
	    	rep = false;
	    }

	    if(ordenu == "continuar"){
	    	MP3player.resumeMusic();
	    }
	    return rep;
	}*/


