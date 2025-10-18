#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global değişkenler
int width, lenght;

// Fonksiyon prototipleri
void get_values();
char* prep_game(int width, int lenght, int *gameint_ptr, int **gamein_ptr, int **gameout_ptr); 
void launch_game(char* dizi, int width, int lenght, int gameint, int *gamein);
void createhead(char* dizi, int gameint, int *gamein);

// Global değişkenler kullanılmaya devam ediliyor
void get_values() {
    printf("Welcome our snake game...\n");
    printf("Enter your width:");
    scanf("%d", &width);
    
    printf("\nEnter your lenght:");
    scanf("%d", &lenght);
}

// prep_game: Haritayı ve indeks dizilerini hazırlar.
char* prep_game(int width, int lenght, int *gameint_ptr, int **gamein_ptr, int **gameout_ptr) {
    if (width <= 2 || lenght <= 2) return NULL; 

    char* dizi = (char*)malloc(width * lenght * sizeof(char));
    if (dizi == NULL) return NULL;

    // Oyun alanı boyutunu hesapla ve gameint_ptr'ye ata
    *gameint_ptr = (width - 2) * (lenght - 2); 
    int gameouint = (width * lenght) - *gameint_ptr; 

    // Bellek ayırma
    int* gamein = (int*)malloc(*gameint_ptr * sizeof(int));
    int* gameout = (int*)malloc(gameouint * sizeof(int)); 

    if (gamein == NULL || gameout == NULL) {
        free(dizi);
        if (gamein) free(gamein);
        if (gameout) free(gameout);
        return NULL;
    }
    
    // İşaretçileri main'deki değişkenlere ata
    *gamein_ptr = gamein;
    *gameout_ptr = gameout;

    int k_in = 0; // İç alan indeksi sayacı
    int k_out = 0; // Dış alan indeksi sayacı

    // Haritayı oluştur ve dizinleri doldur
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < lenght; j++) {
            int index = i * lenght + j;
            
            if (i == 0 || j == 0 || j == lenght - 1 || i == width - 1) {
                // Sınırlar (Duvarlar)
                dizi[index] = '#';
                gameout[k_out++] = index;
            } else {
                // Oyun Alanı
                dizi[index] = '.';
                gamein[k_in++] = index;
            }
        }
    }
    
    return dizi; // Harita dizisini döndür
}

// launch_game: Yılan başını oluşturur ve haritayı SADECE BİR KEZ ekrana basar.
void launch_game(char* dizi, int width, int lenght, int gameint, int *gamein) {
    // 1. Yılan başını oluştur
    createhead(dizi, gameint, gamein); 

    // 2. Haritayı ekrana bas
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < lenght; j++) {
            printf("%c", dizi[i * lenght + j]);
        }
        printf("\n");
    }
}

void createhead(char* dizi, int gameint, int *gamein) {
    if (gameint <= 0) return;

    int randhead = rand() % gameint; 
    
    // Seçilen bu rastgele indeksin haritadaki karşılığı (dizin)
    dizi[gamein[randhead]] = '*';
}

int main() {
    // Rastgelelik çekirdeğini programın başında bir kez başlat
    srand(time(NULL));
    
    int gameint_size = 0;
    int *gamein_indices = NULL;
    int *gameout_indices = NULL; 

    // 1. Boyutları al
    get_values();
    
    // 2. Oyunu hazırla
    char* dizi = prep_game(width, lenght, &gameint_size, &gamein_indices, &gameout_indices);
    
    if (dizi == NULL || gamein_indices == NULL || gameout_indices == NULL) {
        fprintf(stderr, "Hata: Bellek tahsisi başarısız oldu veya geçersiz boyutlar.\n");
        return 1;
    }

    // 3. Oyunu başlat ve haritayı bastır (Sadece yılan başlı harita basılacak)
    launch_game(dizi, width, lenght, gameint_size, gamein_indices);
    
    // 4. Tahsis edilen tüm dinamik bellekleri serbest bırak!
    free(dizi);
    free(gamein_indices);
    free(gameout_indices);
    
    return 0;
}