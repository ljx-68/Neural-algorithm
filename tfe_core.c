#include "type.h"
#include <string.h>
#include <stdlib.h>

#define TFE_VAD_DIM 3

ErrorCode tfe_network_init(
    NeuralNetwork *net,
    int in_dim
    )
{
    if (net == NULL) return TFE_ERR_NULL_POINTER;
    if (in_dim <= 0) return TFE_ERR_INVALID_ARG;
    
    const int out_dim = TFE_VAD_DIM;
    double *W = (double*)calloc((size_t)in_dim * (size_t)out_dim, sizeof(double));

    if (W == NULL) return TFE_ERR_OUT_OF_MEMORY;

    for (int i = 0; i < in_dim * out_dim; i++){
        W[i] = ((double)rand() / RAND_MAX - 0.5) * 0.02;
    }

    net->W = W;
    net->in_dim = in_dim;
    net->out_dim = out_dim;

    memset(net->B, 0, sizeof(net->B));
    memset(net->Y, 0, sizeof(net->Y));
    return TFE_SUCCESS;
}

void tfe_network_free(NeuralNetwork *net)
{
    if (net == NULL) return;
    free(net->W);
    net->W = NULL;
    net->in_dim  = 0;
    net->out_dim = 0;
}

ErrorCode tfe_sample_init(Sample *s, const char *text_address, const double *vad){
    if (s == NULL || text_address == NULL || vad == NULL) return TFE_ERR_NULL_POINTER;
    char *copy = (char*)malloc(strlen(text_address) + 1);
    if (copy == NULL) 
        return TFE_ERR_OUT_OF_MEMORY;
    strcpy(copy, text_address);

    s->text = copy;
    memcpy(s->VAD, vad, sizeof(s->VAD));
    return TFE_SUCCESS;
}

void tfe_sample_free(Sample *s){
    if (s == NULL) return;
    free((void *)s->text);
    s->text = NULL;
    memset(s->VAD, 0, sizeof(s->VAD));
}

ErrorCode tfe_extractor_init(TextFeatureExtractor *T, const char **vocad, int vocad_size){
    if (T == NULL || vocad == NULL) return TFE_ERR_NULL_POINTER;
    if (vocad_size <= 0) return TFE_ERR_INVALID_ARG;
    const char **v = (const char**)malloc(sizeof(const char *) * vocad_size);
    if (v == NULL)return TFE_ERR_OUT_OF_MEMORY;

    for (int i = 0; i < vocad_size; i++){
        if (vocad[i] == NULL){
            free((void *)v);
            return TFE_ERR_INVALID_TEXT;
        }
        v[i] = vocad[i];
    }

    double *x = (double*)calloc(vocad_size, sizeof(double));
    if (x == NULL){
        free((void*)v);
        return TFE_ERR_OUT_OF_MEMORY;
    }

    T->vocab = v;
    T->vocab_size = vocad_size;
    T->X = x;
    return TFE_SUCCESS;
}

void tfe_extractor_free(TextFeatureExtractor *T){
    if (T == NULL)return;
    free((void *)T->vocab);
    free(T->X);
    
    T->vocab = NULL;
    T->vocab_size = 0;
    T->X = NULL;
}