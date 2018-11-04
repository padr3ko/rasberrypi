/*
Author: Patrick Furbert
Date: Sat Nov  3 10:37:30 EDT 2018
Problem: rasberrypi
*/

#include<iostream> //for input output
#include<unistd.h> //for sleep function sleep()
#include<algorithm> //for std::transform
#include<string> //for std::string
#include<stdio.h>
#include<SFML/Audio.hpp> //for playing sounds


std::string translate(std::string);


/*app for translating english text into morse code and plays sounds*/


//main
int main(int argc, char *argv[]){

	//string variables for the text to translate and the returned result
	std::string textToTranslate, translatedText; 

	//welcome the user
	std::cout << "Welcome to our International Morse Code translator\n";
	std::cout << "Enter text that you would like to be translated:\n";

	//store users input into variable
	std::cin >> textToTranslate;


	//converts to lowercase
	std::transform(textToTranslate.begin(), textToTranslate.end(), textToTranslate.begin(), ::tolower);

	//print out result of translation to user
	std::cout << "Morse Code Translation: " <<translate(textToTranslate) <<"\n";

	//create soundbuffer variables for short and long soudns
	sf::SoundBuffer longFartBuffer, quickFartBuffer;

	//load each wav file into the buffers, but exit main if fails
	if(!longFartBuffer.loadFromFile("longFart.wav")){
		return -1;
	}

	if(!quickFartBuffer.loadFromFile("quickFart.wav")){
		return -1;
	}

	//create sound variables
	sf::Sound longFart, quickFart;

	//load the buffers into the sounds variables
	longFart.setBuffer(longFartBuffer);
	quickFart.setBuffer(quickFartBuffer);

	//max volume
	longFart.setVolume(100);
	quickFart.setVolume(100);


	//store translation into string
	translatedText = translate(textToTranslate);

	/*this is a for loop that plays the sound of long 
	or short in the correct order. However, the  sf::sound.play
	is an asyncronous mehtod, meaning that it plays on a 
	seperate thread than the main thread. This means that the 
	main thread can finish before the other threads(even before they start).
	What happens in this program is actually all of the other threads
	get started almost simultanously - which doesn't allow the sounds to 
	come out. Therefore, to get the sounds to play in sequence
	the main thread needs to go to sleep when the sounds are playing.
	So when a sound plays, we go straight into a while loop, where the 
	condition for execution is while the status of the sound is "playing".
	If that is true, we sleep the main thread for 250 ms at a time. When the 
	thread wakes up it checks again if the soudn is playing. When it is no longer
	playing, the while loop won't execute, hence the main thread doesn't sleep and 
	continues execution to play the next soudns*/

	for(int i = 0; i<translatedText.size(); i++){
		//*
		if(translatedText[i] == 42){
			quickFart.play();
			while(quickFart.getStatus() == sf::Sound::Playing){
				sf::sleep(sf::milliseconds(250));
			}
		}

		if(translatedText[i] == 45){
			longFart.play();
			while(longFart.getStatus() == sf::Sound::Playing){
				sf::sleep(sf::milliseconds(250));
			}
		} 

	}

	std::cout << "finished\n"; //print out that we are finished

	return 0;
}//end main


//translate method, returns a std::string and takes a std::string argument
//dependence #include<strings>
std::string translate(std::string translate){


	std::string result; //create a string variable for translations


	//for loop that iterates through the text the users enters
	//and appends the appropriate morse code to the result
	for(int i = 0; i<translate.size(); i++){

		//build result, via switch statement
		switch(translate[i]){
			//a
			case 97 :
				result.append("*-");
				break;
			//b
			case 98 :
				result.append("-***");
				break;
			//c
			case 99 :
				result.append("-*-*");
				break;
			//d
			case 100 :
				result.append("-**");
				break;
			//e
			case 101:
				result.append("*");
				break;
			//f
			case 102:
				result.append("**-*");
				break;
			//g
			case 103 :
				result.append("--*");
				break;			
			//h
			case 104 :
				result.append("****");
				break;
			//i
			case 105 :
				result.append("**");
				break;
			//j
			case 106 :
				result.append("*---");
				break;
			//k
			case 107 :
				result.append("-*-");
				break;
			//l
			case 108 :
				result.append("*-**");
				break;
			//m
			case 109 :
				result.append("--");
				break;
			//n
			case 110 :
				result.append("-*");
				break;
			//o
			case 111 :
				result.append("---");
				break;
			//p
			case 112 :
				result.append("*--*");
				break;
			//q
			case 113 :
				result.append("--*-");
				break;
			//r
			case 114 :
				result.append("*-*");
				break;
			//s
			case 115 :
				result.append("***");
				break;
			//t
			case 116 :
				result.append("-");
				break;
			//u
			case 117 :
				result.append("**-");
				break;					
			//v
			case 118 :
				result.append("***-");
				break;		
			//w
			case 119 :
				result.append("*--");
				break;
			//x
			case 120 :
				result.append("-**-");
				break;
			//y
			case 121 :
				result.append("-*--");
				break;
			//z
			case 122 :
				result.append("--**");
				break;
			//0
			case 48 :
				result.append("-----");
				break; 
			//1
			case 49 :
				result.append("*----");
				break; 
			//2
			case 50 :
				result.append("**---");
				break; 
			//3
			case 51 :
				result.append("***--");
				break; 
			//4
			case 52 :
				result.append("****-");
				break; 
			//5
			case 53 :
				result.append("*****");
				break; 
			//6
			case 54 :
				result.append("-*****");
				break; 
			//7
			case 55 :
				result.append("--***");
				break; 
			//8
			case 56 :
				result.append("---**");
				break; 
			//9
			case 57 :
				result.append("----*");
				break; 
			//space
			case 32 :
				result.append(" ");
				break; 

			}//end switch
		}//end for loop



	return result;
} //end method

