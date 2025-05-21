#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>


// struct Pixel
struct Pixel {
    int R, G, B;
};

// Struct para imagem 
struct Imagem {
    char tipo[3];
    int linhas;
    int colunas;
    int valorMax;
    struct Pixel **matriz;
};

// Função para abrir e ler a imagem
struct Imagem aberturaFile(const char* nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    struct Imagem img;

    // Lê o cabeçalho
    fscanf(fp, "%s", img.tipo);
    fscanf(fp, "%d %d", &img.colunas, &img.linhas);
    fscanf(fp, "%d", &img.valorMax);

    // Aloca a matriz
    img.matriz = (struct Pixel **)malloc(img.linhas * sizeof(struct Pixel *));
    for (int i = 0; i < img.linhas; i++) {
        img.matriz[i] = (struct Pixel *)malloc(img.colunas * sizeof(struct Pixel));
    }

    // Lê os valores RGB
    for (int i = 0; i < img.linhas; i++) {
        for (int j = 0; j < img.colunas; j++) {
            fscanf(fp, "%d %d %d", &img.matriz[i][j].R, &img.matriz[i][j].G, &img.matriz[i][j].B);
        }
    }

    fclose(fp);
    return img;
}

// Função para gerar imagem em tons de cinza
void imagemCinza(struct Imagem img) {
    FILE* fp_novo = fopen("imagemCinza.ppm", "w");
    if (fp_novo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    // Escreve cabeçalho
    fprintf(fp_novo, "%s\n", img.tipo);
    fprintf(fp_novo, "%d %d\n", img.colunas, img.linhas);
    fprintf(fp_novo, "%d\n", img.valorMax);

    //altera os pixels rgb
    for (int i = 0; i < img.linhas; i++) {
        for (int j = 0; j < img.colunas; j++) {

            int r = img.matriz[i][j].R;
            int g = img.matriz[i][j].G;
            int b = img.matriz[i][j].B;

            int cinza = (int)(r * 0.299 + g * 0.587 + b * 0.114);

            fprintf(fp_novo, "%d %d %d ", cinza, cinza, cinza);
        }
        fprintf(fp_novo, "\n");
    }

    fclose(fp_novo);

    // Chama o ImageMagick para converter o .ppm para .png
    system("\"C:\\Program Files\\ImageMagick-7.1.1-Q16-HDRI\\magick.exe\" imagemCinza.ppm imagemCinza.png");

    // Libera memória
    for (int i = 0; i < img.linhas; i++) {
        free(img.matriz[i]);
    }
    free(img.matriz);
}

// Função para gerar imagem em tons negativos
void imagemNegativa(struct Imagem img){
    
    FILE* fp_novo = fopen("imagemNegativa.ppm", "w");
    if (fp_novo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    // Escreve cabeçalho
    fprintf(fp_novo, "%s\n", img.tipo);
    fprintf(fp_novo, "%d %d\n", img.colunas, img.linhas);
    fprintf(fp_novo, "%d\n", img.valorMax);

    //altera os pixels rgb
    for (int i = 0; i < img.linhas; i++) {
        for (int j = 0; j < img.colunas; j++) {

            int r_novo = 255 - img.matriz[i][j].R;
            int g_novo = 255 - img.matriz[i][j].G;
            int b_novo = 255 - img.matriz[i][j].B;

            fprintf(fp_novo, "%d %d %d ", r_novo, g_novo, b_novo);
        }
        fprintf(fp_novo, "\n");
    }

    fclose(fp_novo);

    // Chama o ImageMagick para converter o .ppm para .png
    system("\"C:\\Program Files\\ImageMagick-7.1.1-Q16-HDRI\\magick.exe\" imagemNegativa.ppm imagemNegativa.png");

    // Libera memória
    for (int i = 0; i < img.linhas; i++) {
        free(img.matriz[i]);
    }
    free(img.matriz);

}

// Função para gerar imagem em raio x
void imagemRaioX(struct Imagem img) {
    FILE* fp_novo = fopen("imagemRaioX.ppm", "w");
    if (fp_novo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    // Escreve cabeçalho
    fprintf(fp_novo, "%s\n", img.tipo);
    fprintf(fp_novo, "%d %d\n", img.colunas, img.linhas);
    fprintf(fp_novo, "%d\n", img.valorMax);

    //altera os pixels rgb
    for (int i = 0; i < img.linhas; i++) {
        for (int j = 0; j < img.colunas; j++) {
            int r = img.matriz[i][j].R;
            int g = img.matriz[i][j].G;
            int b = img.matriz[i][j].B;

            int cinza = (int)(0.299 * r + 0.587 * g + 0.114 * b);
            int raioX = img.valorMax - cinza;

            fprintf(fp_novo, "%d %d %d ", raioX, raioX, raioX);
        }
        fprintf(fp_novo, "\n");
    }

    fclose(fp_novo);

    // Converte para PNG
    system("\"C:\\Program Files\\ImageMagick-7.1.1-Q16-HDRI\\magick.exe\" imagemRaioX.ppm imagemRaioX.png");

    // Libera memória
    for (int i = 0; i < img.linhas; i++) {
        free(img.matriz[i]);
    }
    free(img.matriz);
}


// Função para gerar imagem envelhecida (Ajuste para tom sépia/bege)
void imagemEnvelhecida(struct Imagem img) {
    FILE* fp_novo = fopen("imagemEnvelhecida.ppm", "w");
    if (fp_novo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    // Escreve o cabeçalho
    fprintf(fp_novo, "%s\n", img.tipo);
    fprintf(fp_novo, "%d %d\n", img.colunas, img.linhas);
    fprintf(fp_novo, "%d\n", img.valorMax);

    //altera os pixels rgb
    for (int i = 0; i < img.linhas; i++) {
        for (int j = 0; j < img.colunas; j++) {

            int r = img.matriz[i][j].R;
            int g = img.matriz[i][j].G;
            int b = img.matriz[i][j].B;

            // Aplica filtro sépia
            int novoR = (int)(0.393 * r + 0.769 * g + 0.189 * b);
            int novoG = (int)(0.349 * r + 0.686 * g + 0.168 * b);
            int novoB = (int)(0.272 * r + 0.534 * g + 0.131 * b);

            // Garante que os valores estejam entre 0 e valorMax
            if (novoR > img.valorMax) novoR = img.valorMax;
            if (novoG > img.valorMax) novoG = img.valorMax;
            if (novoB > img.valorMax) novoB = img.valorMax;

            fprintf(fp_novo, "%d %d %d ", novoR, novoG, novoB);
        }
        fprintf(fp_novo, "\n");
    }

    fclose(fp_novo);

    // Converte PPM para PNG com ImageMagick
    system("\"C:\\Program Files\\ImageMagick-7.1.1-Q16-HDRI\\magick.exe\" imagemEnvelhecida.ppm imagemEnvelhecida.png");

    // Libera memória
    for (int i = 0; i < img.linhas; i++) {
        free(img.matriz[i]);
    }
    free(img.matriz);
}


// Função para gerar imagem rotada 90 graus
void imagem90(struct Imagem img) {
    FILE* fp_novo = fopen("imagem90.ppm", "w");
    if (fp_novo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    // Escreve o cabeçalho com dimensões trocadas 
    fprintf(fp_novo, "%s\n", img.tipo);
    fprintf(fp_novo, "%d %d\n", img.linhas, img.colunas);  
    fprintf(fp_novo, "%d\n", img.valorMax);

    //altera os pixels rgb
    for (int j = 0; j < img.colunas; j++) {
        for (int i = img.linhas - 1; i >= 0; i--) {

            int r = img.matriz[i][j].R;
            int g = img.matriz[i][j].G;
            int b = img.matriz[i][j].B;
            
            fprintf(fp_novo, "%d %d %d ", r, g, b);
        }
        fprintf(fp_novo, "\n");
    }

    fclose(fp_novo);

    // Chama o ImageMagick para converter o .ppm para .png
    system("\"C:\\Program Files\\ImageMagick-7.1.1-Q16-HDRI\\magick.exe\" imagem90.ppm imagem90.png");

    // Libera memória
    for (int i = 0; i < img.linhas; i++) {
        free(img.matriz[i]);
    }
    free(img.matriz);
}


// Função para gerar imagem rotada 180 graus
void imagem180(struct Imagem img) {
    FILE* fp_novo = fopen("imagem180.ppm", "w");
    if (fp_novo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    fprintf(fp_novo, "%s\n", img.tipo);
    fprintf(fp_novo, "%d %d\n", img.colunas, img.linhas);
    fprintf(fp_novo, "%d\n", img.valorMax);

    //altera os pixels rgb
    for (int i = img.linhas - 1; i >= 0; i--) {
        for (int j = img.colunas - 1; j >= 0; j--) {

            int r = img.matriz[i][j].R;
            int g = img.matriz[i][j].G;
            int b = img.matriz[i][j].B;

            fprintf(fp_novo, "%d %d %d ", r, g, b);
        }
        fprintf(fp_novo, "\n");
    }

    fclose(fp_novo);

    // Chama o ImageMagick para converter o .ppm para .png
    system("\"C:\\Program Files\\ImageMagick-7.1.1-Q16-HDRI\\magick.exe\" imagem180.ppm imagem180.png");
    
    // Libera memória
    for (int i = 0; i < img.linhas; i++) {
        free(img.matriz[i]);
    }
    free(img.matriz);
}


void exibirMenu() {
    printf("\n=============================================\n");
    printf("        EDICAO DE IMAGEM - MENU PRINCIPAL     \n");
    printf("=============================================\n");
    printf(" Escolha a opcao que deseja aplicar a imagem:\n\n");
    printf("  1 - Imagem em tons de cinza\n");
    printf("  2 - Imagem negativa\n");
    printf("  3 - Imagem raio-X\n");
    printf("  4 - Imagem envelhecida\n");
    printf("  5 - Rotacionar imagem em 90 graus\n");
    printf("  6 - Rotacionar imagem em 180 graus\n");
    printf("  0 - Sair do programa\n");
    printf("=============================================\n");
    printf(" Digite o numero da opcao desejada: ");
}

int main() {
    int opcao;
    struct Imagem img; // Declara só uma vez

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("\nAplicando filtro em tons de cinza...\n");
                img = aberturaFile("imagem.ppm");
                imagemCinza(img);
                break;
            case 2:
                printf("\nAplicando filtro negativo...\n");
                img = aberturaFile("imagem.ppm");
                imagemNegativa(img);                
                break;
            case 3:
                printf("\nAplicando efeito raio-X...\n");
                img = aberturaFile("imagem.ppm");
                imagemRaioX(img);                
                break;
            case 4:
                printf("\nAplicando efeito envelhecido...\n");
                img = aberturaFile("imagem.ppm");
                imagemEnvelhecida(img);                
                break;
            case 5:
                printf("\nRotacionando imagem em 90 graus...\n");
                img = aberturaFile("imagem.ppm");
                imagem90(img);                
                break;
            case 6:
                printf("\nRotacionando imagem em 180 graus...\n");
                img = aberturaFile("imagem.ppm");
                imagem180(img);                
                break;
            case 0:
                printf("\nEncerrando o programa.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}


