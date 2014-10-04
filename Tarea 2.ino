#include <SdFat.h>					// Import SD card Lib
#include <SdFatUtil.h>				
#include <SFEMP3Shield.h>
#include <SPI.h>


uint8_t track_num = 0;
uint8_t last_track = 0;
uint32_t t_pos = 0;
uint8_t orden = 0;

SdFat sd;	
const int chipSelect = 9;								
SFEMP3Shield MP3player;	

void setup(){
	Serial.begin(115200);
	sd.begin(chipSelect,SPI_HALF_SPEED);	
	MP3player.begin();
	String artista = "";
}



String preguntar_artista(){
	Serial.println("Cual de los siguientes artistas desea escuchar?");
	Serial.println("50cent");
	Serial.println("Akon");
	Serial.println("Nelly");
	Serial.println("si desea cambiar el artista escriba (parar) en cualquier momento");
	String artista = "";
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


String orden_usuario(uint8_t orden,String artista){
	
switch (orden) {
    case 1:
      artista = "";// do something
      break;

    case 2:
      MP3player.pauseMusic();// do something
      break;

    case 3:
      t_pos = MP3player.currentPosition();	//guarda la posicion actual
      MP3player.stopTrack();// do something
      break;

     case 4:
      MP3player.resumeMusic();// do something
      break;

}
}


void canciones_artista(String artista){
	Serial.print('\n');
	Serial.println("Las canciones disponibles del artista seleccionado son: ");
    Serial.print('\n');
	if(artista == "50cent"){
	    Serial.println("track 1");
	    Serial.println("track 2");
	    Serial.println("track 3");
	   
	}

	if(artista == "akon"){
	    Serial.println("track 4");
	    Serial.println("track 5");
	    Serial.println("track 6");
	  
	}

	if(artista == "nelly"){
	    Serial.println("track 7");
	    Serial.println("track 8");
	    Serial.println("track 9");
	   
	}
}

bool verificar_artista(String artista,uint8_t last_track){

bool coincide = false;
while(coincide == false){
	randomSeed(millis());
	track_num = random(1,9);

	while(track_num == last_track){
	    track_num = random(1,9);// statement
	}

	last_track = track_num;

	char buffer[16];
	MP3player.playTrack(track_num);
    MP3player.trackArtist(buffer);
    MP3player.stopTrack();

    if(String (buffer) == artista){
        coincide = true;
    }
}

return coincide;
return track_num;

}



void loop()
{
String artista = "";
while(true){
 
while(artista == ""){
    artista = preguntar_artista();
}

bool rep = verificar_artista(artista,last_track);

	while(rep == true){
        MP3player.playTrack(track_num);
        char buffer [16];
        MP3player.trackTitle(buffer);
        Serial.print("track ");
        Serial.print(track_num);
        Serial.print(":  ");
        Serial.println(buffer);
        last_track = track_num;

	while(MP3player.isPlaying()){
	    String ordenu = leer_respuesta();// statement

	    if(ordenu == "cambiar artista"){
	    	artista == "";
	    	rep = false;
	    	MP3player.stopTrack();
	    }

	    if(ordenu == "siguiente"){
	    	rep = false;
	    	MP3player.stopTrack(); 
	    }

        intervenir(ordenu);
	}
}
}
}



void intervenir(String ordenu){

	   
	    if(ordenu == "pausar"){
	    	MP3player.pauseMusic();
	    }

	    if(ordenu == "parar"){
	    	MP3player.stopTrack();
	    }

	    if(ordenu == "continuar"){
	    	MP3player.resumeMusic();
	    }
	}


