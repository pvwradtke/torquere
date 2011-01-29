/*
 * File:   main.cpp
 * Author: pvwradtke
 *
 * Created on 4 de Janeiro de 2011, 10:58
 */

#include <stdlib.h>
#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2primitivas.h>
#include <c2d2/chienaudio2.h>

/*
 *
 */
int main(int argc, char** argv) {

    // Inicia o sistema de vídeo. Se der erro, encerra
    if(!C2D2_Inicia(1024, 600, C2D2_TELA_CHEIA
            , C2D2_DESENHO_OPENGL, "Projeto Cores"))
    {
        printf("Erro ao inicializar o vídeo. Encerrando.\n");
        exit(1);
    }
    // Inicia o áudio. Se der errado, não dá nada.
    CA2_Inicia();
    // Inicia o desenho de primitivas (para o render primário)
    C2D2P_Inicia();

    C2D2_LimpaTela();
    C2D2P_Linha(0,0,1023,599, 255, 255, 255);
    C2D2_Sincroniza(C2D2_FPS_PADRAO);
    C2D2_Pausa(5000);

    C2D2_Encerra();
    return (EXIT_SUCCESS);
}

