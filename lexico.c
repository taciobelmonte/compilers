/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Tacio
 *
 * Created on 23 de Junho de 2017, 18:31
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
    
    char input[100], output[100];
    FILE *file;
    
    //Recupera argumentos passados
    strcpy(input, argv[1]);
    strcpy(output, argv[2]);
    
    //Abre arquivo de entrada
    file = fopen(input, "r");
    
    if(file == NULL){
        printf("erro ao abrir arquivo\n");
        exit(0);
    }else{
        printf("abriu arquivo\n");
    }
    return (EXIT_SUCCESS);
}

