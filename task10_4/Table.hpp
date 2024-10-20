#if !defined(_Table_h_)
#define _Table_h_

#define MaxFieldNameLen 30 /* Максимальная длина имени поля */

enum Errors /* Перечисление возможных ошибок */
{
  OK,             /* Успех */
  CantCreateTable, /* Невозможно создать таблицу */
  CantOpenTable, /* Невозможно открыть таблицу */
  FieldNotFound, /* Поле не найдено */
  BadHandle, /* Неверный дескриптор таблицы */
  BadArgs, /* Неверные аргументы */
  CantMoveToPos, /* Невозможно установить позицию в файле */
  CantWriteData, /* Ошибка записи в файл */
  CantReadData, /* Ошибка чтения из файла */
  CorruptedData, /* Данные таблицы повреждены */
  CantCreateHandle, /* Невозможно создать дескриптор таблицы */
  ReadOnlyFile, /* Невозможно удалить или открыть файл только для чтения */
  BadFileName, /* Недопустимое имя файла */
  CantDeleteTable, /* Невозможно удалить таблицу */
  CorruptedFile, /* Данные файла повреждены */
  BadPos, /* Неверная позиция в файле */
  BadFieldType, /* Неверный тип поля */
  BadFieldLen, /* Текстовое значение превышает длину поля */
  NoEditing, /* Текущая запись не редактируется */
  BadPosition, /* Неверная позиция */
};

/* Массив текстов ошибок */
extern char* ErrorText[];

/* Описание структур, используемых в библиотеке, и тип THandle,
который используется для идентификации таблицы. Этот тип используется для всех функций библиотеки.*/

typedef struct Table * THandle;

typedef unsigned Bool; /* Булев тип */

#define TRUE 1
#define FALSE 0

/* Перечисление типов данных, которые могут храниться в полях таблицы */

enum FieldType
{
  Text,     /* Текстовое (максимум 256 символов) */
  Long,     /* Целочисленное значение */
  Logic /* Логическое значение */
};

/* Определение структуры поля */

struct FieldDef
{
  char name[MaxFieldNameLen]; /* Имя поля */
  enum FieldType type; /* Тип поля */
  unsigned len; /* Длина поля в байтах */
};

/* Определение структуры описания таблицы, которая используется для создания новых таблиц. */

struct TableStruct
{
  unsigned numOfFields; /* Количество полей в таблице */
  struct FieldDef *fieldsDef; /* Указатель на массив описаний полей,
  который должен быть предварительно заполнен - определяет поля таблицы */
};

/* Прототипы функций библиотеки */

enum Errors createTable(char *tableName, struct TableStruct *tableStruct);
/* Создает новую таблицу с заданными параметрами. Если не удается создать таблицу, возвращает соответствующую ошибку. */

enum Errors deleteTable(char *tableName);
/* Удаляет таблицу с заданным именем. */

enum Errors openTable(char *tableName, THandle *tableHandle);
/* Открывает таблицу с заданным именем. */

enum Errors closeTable(THandle tableHandle);
/* Закрывает таблицу с заданным дескриптором. */

enum Errors moveFirst(THandle tableHandle);
/* Перемещает указатель на первую запись в таблице. */

enum Errors moveLast(THandle tableHandle);
/* Перемещает указатель на последнюю запись в таблице. */

enum Errors moveNext(THandle tableHandle);
/* Перемещает указатель на следующую запись в таблице. */

enum Errors movePrevios(THandle tableHandle);
/* Перемещает указатель на предыдущую запись в таблице. */

Bool beforeFirst(THandle tableHandle);
/* Возвращает TRUE, если указатель находится перед первой записью в таблице. */

Bool afterLast(THandle tableHandle);
/* Возвращает TRUE, если указатель находится после последней записи в таблице. */

enum Errors getText(THandle tableHandle, char *fieldName, char **pvalue);
/* Получает текстовое значение поля с заданным именем. */

enum Errors getLong(THandle tableHandle, char *fieldName, long *pvalue);
/* Получает целочисленное значение поля с заданным именем. */

enum Errors startEdit(THandle tableHandle);
/* Начинает редактирование текущей записи. */

enum Errors putText(THandle tableHandle, char *fieldName,char *value);
/* Устанавливает текстовое значение для поля с заданным именем. */

enum Errors putLong(THandle tableHandle, char *fieldName,long value);
/* Устанавливает целочисленное значение для поля с заданным именем. */

enum Errors finishEdit(THandle tableHandle);
/* Завершает редактирование текущей записи. */

enum Errors createNew(THandle tableHandle);
/* Создает новую запись в таблице. */

/* Функции для работы с новыми записями. */

enum Errors putTextNew(THandle tableHandle, char *fieldName, char *value);
enum Errors putLongNew(THandle tableHandle, char *fieldName, long value);

enum Errors insertNew(THandle tableHandle);
/* Вставляет новую запись в таблицу. */

enum Errors insertaNew(THandle tableHandle);
/* Вставляет новую запись в начало таблицы. */

enum Errors insertzNew(THandle tableHandle);
/* Вставляет новую запись в конец таблицы. */

enum Errors deleteRec(THandle tableHandle);
/* Удаляет текущую запись из таблицы. */

char *getErrorString(enum Errors code);
/* Возвращает текстовое описание ошибки. */

enum Errors getFieldLen(THandle tableHandle,char*fieldName,unsigned *plen);
/* Возвращает длину поля в таблице. */

enum Errors getFieldType(THandle tableHandle, char *fieldName, enum FieldType *ptype);
/* Возвращает тип поля в таблице. */

enum Errors getFieldsNum(THandle tableHandle, unsigned *pNum);
/* Возвращает количество полей в таблице. */

enum Errors getFieldName(THandle tableHandle, unsigned index, char **pFieldName);
/* Возвращает имя поля в таблице по заданному индексу. */

#endif
