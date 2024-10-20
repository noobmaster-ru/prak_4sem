struct cmd_inf {
	char ** argv; // список из имени команды и аргументов
	char *infile; // переназначенный файл стандартного ввода
	char *outfile; // переназначенный файл стандартного вывода
	int doublegr; //>>
	int backgrnd; // =1, если команда подлежит выполнению в фоновом режиме cmd_inf* psubcmd; // команды для запуска в дочернем shell
	struct cmd_inf* pipe; // следующая команда после “|”
	struct cmd_inf* next; // следующая после “;” (или после “&&”)
};
typedef struct cmd_inf * tree;

enum type_of_next{
    NXT, AND, OR   // виды связей соседних команд в списке команд
};

typedef struct cmd_inf node;

void print_tree(tree, int);

tree make_cmd();
void make_bgrrnd(tree t);
void add_arg();
int ind; //index
char * curw; //current word 

int len_f; //длина имен файлов для in out

tree build_tree();
void cleartree(tree t);

int count_b;
