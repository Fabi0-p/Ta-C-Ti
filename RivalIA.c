#ifndef RIVAL_IA_C
#define RIVAL_IA_C

void initTablaLineas(short int tab[3][8]){
    int count = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tab[i][j] = count;
            count++;
        }
    }
    count = 0;
    for(int i = 3; i < 6; i++){
        for(int j = 0; j < 3; j++){
            tab[j][i] = count;
            count++;
        }
    }
    tab[0][6] = 0;
    tab[1][6] = 4;
    tab[2][6] = 8;
    tab[0][7] = 2;
    tab[1][7] = 4;
    tab[2][7] = 6;
}




#endif
