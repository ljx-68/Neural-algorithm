#include <stdio.h>
#include <string.h>
#include "type.h"
#include <time.h>
#include <stdlib.h>
int main(void){
    srand((unsigned)time(NULL));
    const char *text[] = {"今天", "很", "好"};
    int vocab_size = 3;
    TextFeatureExtractor ext = {0};
    if (tfe_extractor_init(&ext, text, vocab_size) != TFE_SUCCESS){
        fprintf(stderr, "extractor init failed\n");
        return 1;
    }
    printf("%d", ext.vocab_size);
    return 0;

}