#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>

#define MAX_BUF_SIZE 200

std::string getURL(float lattitude, float longitude){
	// Assume that we have lattitude and longitude variables as follows
	
	// The buffer to store the final URL with lattitude and longitude filled in
	char finalURLBuff[MAX_BUF_SIZE];	

	// snprintf will replace the fist %f (representing the floating point place holder for a floating point value
	// that should be taken from the third argument of snprintf and converted into string), and similarly will replace the
	// the second %f with the fourth argument of snprintf().
	
	// This function will take the third argument (i.e., the formatting string), will replace the formatting directives
	// (i.e., %f) with the arguments lattitude and longitude, respectively and store the resulting string in the finalURLBuff
	// MAX_BUF_SIZE tells the function to stop if the resulting string exceeds the MAMAX_BUF_SIZE (don't want to go out of bounds
	// of the finalURLBuff)
	// For more information in snprintf() please check
	// https://www.geeksforgeeks.org/snprintf-c-library/ 
	snprintf(finalURLBuff, MAX_BUF_SIZE, "https://api.open-meteo.com/v1/forecast?latitude=%f&longitude=%f&current_weather=True", lattitude, longitude); 
	
	//fprintf(stderr, "The final URL is %s\n", finalURLBuff);

	return finalURLBuff;
}



int main(){
	//Initialization
	std::string url;
	float lattitude;
	float longitude;
    std::string placeholder;

	//File Creation
	std::string fileName;
	std::string fileNamePrefix = "file";
	int fileNum = 1;

	//Fork
	pid_t pid;
	int waitReturn;
	int childEventInfo;
	int execlpRetVal;

	//Read in file
    std::ifstream file("input.txt");
    std::string str; 

    while (std::getline(file, str)){
        std::istringstream iss(str);

		//Get lattitude and longitude
		std::getline(iss, placeholder, ' ');
        lattitude = std::stof(placeholder);

        std::getline(iss, placeholder, ' ');
        longitude = std::stof(placeholder);

		//Create url
		url = getURL(lattitude, longitude);
		//Create file name
		fileName = fileNamePrefix + std::to_string(fileNum) + ".json";

		//Spagetti
		pid = fork();

		if(pid < 0){
			perror("fork");
			exit(1);
		}

        if(pid == 0){
			execlpRetVal = execlp("/usr/bin/curl", "/usr/bin/curl", "-o", fileName.c_str(), url.c_str() , NULL);
			// This code is unreachable unless execlp has failed 
			if(execlpRetVal < 0){
				perror("execlp");
				exit(1);
			}
		} else {
			/*** TODO: If I am a parent, I will do the following ***?
			Wait for the child process to terminate */
			waitReturn = wait(&childEventInfo);
				// Sanity checks -- wait failed?
			if(waitReturn < 0){
				perror("wait");
				exit(1);
			}
		}
		fileNum++;
    }
}