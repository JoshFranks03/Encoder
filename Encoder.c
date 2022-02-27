//This program is made to encode and decode secret messages written in all caps using a keyword
//Special characters and lowercase letters do not get encoded
//Spaces are allowed but are removed after going through the decoder
//To decode messages take the scrambled message and the same keyword and run the program
//Code still contains minor bugs, but they are being fixed

#include <stdio.h>
#include <string.h>
int main() {
    //Variable declaration
    char keyWord[50];
    char secretMessage[50];
    char keyWordUse[50];
    int difference;
    char message[50];
    char codedMessage[50];
    int j=0;

    printf("Enter keyword in all caps (Ex. HELLO): ");
    fgets(keyWord, 50, stdin);

    while(1){
        for(int i = 0; i< strlen(keyWord);i++){
            if (keyWord[i]==' '||keyWord[i]>='[' && keyWord[i] <= '~' || keyWord[i]<= '@' && keyWord[i]>='!'||keyWord[i]<= 'z' && keyWord[i]>='a'){
                printf("\nOnly capital letters. No spaces or special characters allowed. Enter keyword: ");
                fgets(keyWord, 50, stdin);
            }
        }
        break;
    }


    if (keyWord[strlen(keyWord)-1]=='\n'){
        keyWord[strlen(keyWord)-1]='\0';
    }
    strcpy(keyWordUse,keyWord);

    //Prompt user for message
    printf("Enter secret message:");
    fgets(secretMessage, 50, stdin);


    //check if null character needs to be switched back
    if (secretMessage[strlen(secretMessage)-1]=='\n'){
        secretMessage[strlen(secretMessage)-1]='\0';
    }
    //Take spaces out of the message entered
    int counter = 0;
    for (int i = 0; i< strlen(secretMessage);i++){
        if (secretMessage[i]!=' ') {
            secretMessage[counter] = secretMessage[i];
            counter++;
        }
    }
    //set last character to null character
    secretMessage[counter]='\0';

    //make copies secretMessage into message (fixes error that changed secretMessage value)
    int length = strlen(secretMessage);
    strcpy(message,secretMessage);

    //concatenate the keyword onto itself until it is longer than the secret message
    if (strlen(secretMessage)> strlen(keyWord)){
        for(int j = length ;j > strlen(keyWord);j-= strlen(keyWord)) {
            strcat(keyWordUse, keyWord);
        }
    }

    //Start to code message if the letters in the message are capital letters
    for (int i = 0; i<strlen(message);i++){
        if (message[i]>='A' && message[i]<='Z'){
            difference = message[i]-keyWordUse[j];
            //use different counter to only increment when a capital is used
            codedMessage[i]=keyWordUse[j]-difference;
            j++;
            //Make sure letters that are not capitals do not get coded
        }else if(message[i]<'A'||message[i]>'Z') {
            codedMessage[i] = message[i];
        }
        //make sure that special characters aren't coded
        if(message[i]>='[' && message[i] <= '~' || message[i]<= '@' && message[i]>='!') {
            codedMessage[i] = message[i];
            //loop back to Z if codedMessage[i] is smaller than the char A
        }else if (codedMessage[i]<'A'){
            codedMessage[i]=codedMessage[i]+26;
            //loop back to A if codedMessage[i] is greater than char Z
        }else if(codedMessage[i]>'Z') {
            codedMessage[i] = codedMessage[i] - 26;
        }
        //Fixed bug that added random characters at the end of the message due to keyWordUse being longer than codedMessage
        //by subtracting the overlap of letters from codedMessage[] and then setting that char to the null char
        if (strlen(codedMessage)> strlen(message)){
            codedMessage[strlen(codedMessage)-(strlen(codedMessage)- strlen(message))]='\0';
        }


    }
    //print output
    printf("*BEGIN_MESSAGE*\n%s\n*END_MESSAGE*",codedMessage);
}