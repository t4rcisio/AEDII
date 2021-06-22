/*
ALGORÍTIMO DE ÁRVORE BINÁRIA
AUTOR: Tarcísio Batista Prates

https://github.com/t4rcisio


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



struct Node//Configuração do nó
{
    int          id;      // Grava a posição no vetor
    int          content; // O valor do nó
    struct Node* above;   // Nó acima
    struct Node* left;    // Nó à esquerda
    struct Node* right;   // Nó à direita 
    
};

typedef struct //Configuração da árvore
{
    int          head;    // Primeiro nó
    struct Node* node;    // Lista de nós da árvore
    int          last;    // Último nó

}Tree;

void nodeConstruc(struct Node *node){// inicializa o nó com valores default
    node->id      = 0000;            // Devido a limitações da linguagem C, não é possível
    node->above   = NULL;            // inicializar "id" e "content" com valor NULL
    node->left    = NULL;
    node->right   = NULL;
    node->content = 0000; 
}

void treeCosntruc(Tree *tree){ // Inicializa a árvore

    tree->node = (struct Node*)malloc(1*sizeof(struct Node));
    tree->head = 0; 
    tree->last = 0;
    struct Node defaultNode;
    nodeConstruc(&defaultNode);
    tree->node[0] = defaultNode; // Insere um nó default na árvore
}

void allocNode(Tree *tree){//Aumenta em 1 unidade o tamanho do vetor de Nodes
    tree->node = (struct Node*)realloc(tree->node,(tree->last+1)*sizeof(struct Node));
}

int insertNode(Tree *tree, struct Node* node, int content){//Realiza a inserção dos nós
    
    if(node->content == 0){//Tratamento para o nó raíz
        int id = tree->last;
        tree->node[id].content = content;
        tree->node[id].id = id;
        tree->last = 1;
    }else{
        if(node->content == content){//caso o valor do nó já exista
            printf("This node already exist!\n");
            return 0;
        }else{
            if(node->content > content){//Se menor
                if(node->left != NULL){//Verifica se o nó à esquerda está vazio
                    insertNode(tree,node->left,content);//Avança para o nó à esquerda
    
                }else{
                    allocNode(tree);//Abre espaço no vetor de Nodes
                    struct Node defaultNode;
                    nodeConstruc(&defaultNode);//Inicializa o node como default
                    int id = tree->last;//recupera a última posiçao do vetor
                    tree->node[id] = defaultNode;//insere o node na memória do vetor
                    tree->node[id].id = id;
                    tree->node[node->id].left = &tree->node[id]; // Associa o "left" do nó de origem com o nó recém-criado
                    tree->node[id].above = &tree->node[node->id];//Faz a conexão com nó de origem no ponteiro "above"
                    tree->node[id].content = content; //Grava o valor do nó
                    tree->last = tree->last+1;
                    return 1;
                }
            }
            if(node->content < content){
                if(node->right != NULL){
                insertNode(tree,node->right,content);//Avança para o nó à direita
                }else{
                    allocNode(tree);//Abre espaço no vetor de Nodes
                    struct Node defaultNode;
                    nodeConstruc(&defaultNode);//Inicializa o node como default
                    int id = tree->last;//recupera a última posiçao do vetor
                    tree->node[id] = defaultNode;//insere o node na memória do vetor
                    tree->node[id].id = id;
                    tree->node[node->id].right = &tree->node[id]; // Associa o "right" do nó de origem com o nó recém-criado
                    tree->node[id].above = &tree->node[node->id];//Faz a conexão com nó de origem no ponteiro "above"
                    tree->node[id].content = content; //Grava o valor do nó
                    tree->last = tree->last+1;
                    return 1;
                }
            }
        }
    }
}

int findNode(struct Node* node, int content, int *it){//Procura e descreve o caminho do nó, caso exista.
    *it = *it+1;
    if(node->content == content){//caso o valor seja encontrado, ele é exibido
        printf("This node already exist!\n");
        printf("%d ", content);
        return 1;
    }else{
        if(node->content > content){//Se menor
            if(node->left != NULL){//Verifica se o nó à esquerda está vazio
                if(findNode(node->left,content, it)){//Avança para o nó à esquerda
                    printf("%d ", node->content);
                    return 1;
                }else{
                    return 0;
                }

            }else{
                printf("This node( %d ) does't exist!\n", content);
                return 0;
            }
        }
        if(node->content < content){
            if(node->right != NULL){
                if(findNode(node->right,content, it)){//Avança para o nó à direita
                    printf("%d ", node->content);
                    return 1;
                }else{
                    return 0;
                }
            }else{
                printf("This node( %d ) does't exist!\n", content);
                return 0;
            }
        }
    }
}


int main(){

    Tree tree;
    int numeros[9] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
    int tam = (int)(sizeof(numeros)/sizeof(numeros[0]));
    treeCosntruc(&tree);//Inicializa a árvore
    int it = 0;
    int no;
    for(int i = 0; i <10; i++){
        insertNode(&tree,tree.node,numeros[i]);
    }
    printf("Infome o valor do nó: ");
    scanf("%d",&no);
    clock_t begin = clock();
    findNode(&tree.node[0], no, &it);
    clock_t end = clock();
    double time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nNúmero de comparações relizadas : %2d\nTempo de pesquisa: %lf segundos\n",it, time);

}