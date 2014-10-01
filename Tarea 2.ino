#include <SdFat.h>					// Import SD card Lib
#include <SdFatUtil.h>				
#include <SFEMP3Shield.h>
#include <SPI.h>


uint8_t track_num = 0;
uint8_t last_track = 0;
uint32_t t_pos = 0;
const int chipSelect = 9;
SdFat sd;									
SFEMP3Shield MP3;	

void setup(){
	Serial.begin(115200);
	sd.begin(chipSelect,SPI_HALF_SPEED);	
	MP3.begin();
	String artista = "";
}



String preguntar_artista(){
	Serial.println("Cual de los siguientes artistas desea escuchar?");
	Serial.println("tpain");
	Serial.println("neyo");
	Serial.println("50cent");
	Serial.println("si desea cambiar el artista escriba (parar) en cualquier momento")
	String artista = "";
	while(artista = ""){
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
	while(respuesta = ""){
		respuesta = leer_respuesta();
	}
	if(respuesta == "si"){
		aleatorio = true;
	}
	else{
		aleatorio = false;
	}
	return aleatorio;
}


String orden_usuario(orden){
switch (orden) {
    case 1:
      artista = "";// do something
      break;

    case 2:
      t_pos = MP3player.currentPosition();	//guarda la posicion actual
      MP3player.Track();// do something
      break;

}
}


void canciones_artista(){
	Serial.print('\n');
	Serial.println("Las canciones disponibles del artista seleccionado son: ");
    Serial.print('\n');
	if(artista == "50cent"){
	    Serial.println("track 1");
	    Serial.println("track 2");
	    Serial.println("track 3");
	    Serial.println("track 4");
	    Serial.println("track 5");
	}

	if(artista == "neyo"){
	    Serial.println("track 6");
	    Serial.println("track 7");
	    Serial.println("track 8");
	    Serial.println("track 9");
	    Serial.println("track 10");
	}

	if(artista == "tpain"){
	    Serial.println("track 11");
	    Serial.println("track 12");
	    Serial.println("track 13");
	    Serial.println("track 14");
	    Serial.println("track 15");
	}
}


void loop(){


	while(artista = ""){
	 	preguntar_artista();   // statement
	 }

	 canciones_artista();
	 rep_aleatoria();


	 if(artista == "50cent" && aleatorio == true){
	 	track_num = random(1,5); 
	 }	

	 if (track_num != last_track && aleatorio == true){
	 	last_track = track_num;
	 	MP3player.playTrack(track_num);	
	 }

	 else if(artista == "50cent" && aleatorio == false){
	 	track_num = 0;
	 	track_num = track_num + 1;;
	 	MP3player.playTrack(track_num);
	 }


	 if(artista == "tpain" && aleatorio == true){
	 	track_num = random(6,10); 
	 }	

	 if (track_num != last_track && aleatorio == true){
	 	last_track = track_num;
	 	MP3player.playTrack(track_num);	
	 }

	 else if(artista == "tpain" && aleatorio == false){
	 	track_num = 5;
	 	track_num = track_num + 1;;
	 	MP3player.playTrack(track_num);
	 }


	 if(artista == "neyo" && aleatorio == true){
	 	track_num = random(6,10); 
	 }	

	 if (track_num != last_track && aleatorio == true){
	 	last_track = track_num;
	 	MP3player.playTrack(track_num);	
	 }

	 else if(artista == "neyo" && aleatorio == false){
	 	track_num = 5;
	 	track_num = track_num + 1;;
	 	MP3player.playTrack(track_num);
	 }

	 if (Serial.available()){
	    String ordenu = ""; // statement
	    ordenu.concat(char(Serial.read()));                   // statement
	    delay(10);
	    uint8_t orden = 0;

	    if(ordenu == "cambiar"){
	    	orden = 1;
	    }

	    if(ordenu == "pusar"){
	    	orden = 2;
	    }

	    if(ordenu == "parar"){
	    	orden = 3;
	    }

	    if(ordenu == "parar"){
	    	orden = 4;
	    }

	    if(ordenu == "parar"){
	    	orden = 5;
	    }
	}

	orden_usuario();

}




