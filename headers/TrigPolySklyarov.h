struct TrigPoly
{
    int n;
    double alpha;
    double *a;
    double *b;
};

// Операції над поліномами

double value(struct TrigPoly p, double x); // функція, яка рахує значення поліному p в точці alpha

struct TrigPoly add_poly(struct TrigPoly p1, struct TrigPoly p2); // функція, яка додає поліноми р1 та р2

struct TrigPoly subtract_poly(struct TrigPoly p1, struct TrigPoly p2); // функція, яка віднімає від полінома р1 поліном р2

struct TrigPoly derivative(struct TrigPoly p); // функція, чка знаходить похідну від полінома р

struct TrigPoly integral(struct TrigPoly p, double C); // функція, яка знаходить невизначений інтеграл від полінома

double integrate(struct TrigPoly p, double a, double b); // функція, яка рахує визначений інтеграл від полінома

struct TrigPoly mul_poly(struct TrigPoly p1, struct TrigPoly p2); // функція, яка перемножає два полінома

struct TrigPoly div_poly(struct TrigPoly p1, struct TrigPoly p2); // функція, яка ділить один поліном на інший

// Введення і виведення поліномів

void input_poly(struct TrigPoly *p); // введення полінома по коефіцієнтам через scanf

void input_text_file(struct TrigPoly *p); // зчитування полінома з текстового файлу

void string_to_poly(struct TrigPoly *p, char *s); // функція, яка введений рядок перетворює на поліном

void print_poly(struct TrigPoly p); // функція, яка виводить поліном на екран

void print_integral_poly(struct TrigPoly p, double C); // функція виводить поліном після інтергування. Я створив додаткову функцію для виведення
                                                       // оскільки при інтегруванні з'явиться ще один доданок

void write_poly_to_file(struct TrigPoly p); // запис поліномa у файл

void write_to_binary_file(struct TrigPoly p); // запис у бінарний файл

void write_res_to_file(double res); // запис результатa в файл ( значення поліному в точці або визначений інтеграл)

void write_res_binary(double res); // запис результатa в бінарний файл ( значення поліному в точці або визначений інтеграл)

// Інші функції

char* add_char(char *c1, char c2); // функція, яка до рядка додає символ

void destroy(struct TrigPoly *p); // видалення поліному

double setAlpha(); // повертає введене користувачем значення alpha




