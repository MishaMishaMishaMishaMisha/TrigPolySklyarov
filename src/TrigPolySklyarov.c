#include "../headers/TrigPolySklyarov.h"
//#include "TrigPolySklyarov.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// інші функції та змінні, якими будуть користуватися функції для роботи з поліномами


char* add_char(char *c1, char c2)
{
    size_t len = strlen(c1);
    char *str2 = malloc(len + 1 + 1);
    strcpy(str2, c1);
    str2[len] = c2;
    str2[len + 1] = '\0';
    return str2;
}

int is_file_new = 0; // якщо ця змінна = 0, то текстовий файл, куди записується результат, треба очистити, інакше - просто записуємо результат на наступний рядок
                     // це треба, щоб при повторному запуску програми стиралися попередні результати програми
int is_binary_new = 0; // те саме для бінарного файлу

void destroy(struct TrigPoly *p)
{
    p->n = 0;
    p->alpha = 0;
    free(p->a);
    free(p->b);
}

double setAlpha()
{
    double alpha;
    printf("Введіть значення alpha = ");
    scanf("%lf", &alpha);
    return alpha;
}


// Введення\виведення


void input_poly(struct TrigPoly *p)
{
    printf("alpha = ");
    scanf("%lf", &p->alpha);
    printf("n = ");
    scanf("%d", &p->n);
    p->a = (double *)malloc((p->n + 1) * sizeof(double));
    p->b = (double *)malloc((p->n + 1)* sizeof(double));
    for (int k = 0; k < p->n + 1; k++)
    {
        if (k == 0)
        {
            printf("a%d = ", k);
            scanf("%lf", &p->a[k]);
            p->b[k] = 0;
            continue;
        }
        printf("a%d = ", k);
        scanf("%lf", &p->a[k]);
        printf("b%d = ", k);
        scanf("%lf", &p->b[k]);
    }
}

void string_to_poly(struct TrigPoly *p, char *s)
{
    int m = 0;
    int n = 0;
    // знаходимо кількість коефіцієнтів
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '^' || s[i] == ' ')
        {
            n++;
        }
    }
    n = n/2 - 1/2;
    // створимо новий масив символів, куди будемо записувати вже готові коефіцієенти
    double coef[2*n + 2];
    char *c = "";
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] != '^' && s[i] != ' ')
        {
            c = add_char(c, s[i]);
        }
        else if (s[i] == '^' || s[i] == ' ')
        {
            coef[m] = atof(c);
            m++;
            memset(c, 0, sizeof c);
        }
    }
    coef[m] = atof(c);
    // після зчитування, ми маємо масив коефіцієнтів
    // і тепер можна створити поліном
    p->n = n;
    p->alpha = coef[0];
    int x = 1;
    p->a = (double *)malloc((p->n + 1)* sizeof(double));
    p->b = (double *)malloc((p->n +1)* sizeof(double));
    p->a[0] = coef[1];
    p->b[0] = 0;
    for (int k = 2; k < 2*n + 2; k += 2)
    {
        p->a[x] = coef[k];
        x++;
    }
    x = 1;
    for (int k = 3; k < 2*n + 2; k += 2)
    {
        p->b[x] = coef[k];
        x++;
    }
    free(s);
    s = NULL;
};

void print_poly(struct TrigPoly p)
{
    printf("%lf, ", p.alpha);
    printf("%lf", p.a[0]/2);
    for (int k = 1; k <= p.n; k++)
    {
        printf(" + (%lf)*cos(%d*x) + (%lf)*sin(%d*x)", p.a[k], k, p.b[k], k);
    }
}

void write_poly_to_file(struct TrigPoly p)
{
    FILE *resl = NULL;
    resl = fopen("resl.txt", "a");
    // якщо файл містить попередній результат роботи програми, то очищаємо його
    if (is_file_new == 0)
    {
        fclose(resl);
        fopen("resl.txt", "w");
    }

    fprintf(resl, "%lf, ", p.alpha);
    fprintf(resl, "%lf ", p.a[0]/2);
    for (int k = 1; k <= p.n; k++)
    {
        fprintf(resl, " + (%lf)*cos(%d*x) + (%lf)*sin(%d*x)", p.a[k], k, p.b[k], k);
    }
    fprintf(resl, "\n");
    fclose(resl);
    is_file_new = 1;
}

void write_res_to_file(double res)
{
    FILE *resl = NULL;
    resl = fopen("resl.txt", "a");

    if (is_file_new == 0)
    {
        fclose(resl);
        fopen("resl.txt", "w");
    }

    fprintf(resl, "%lf\n", res);
    fclose(resl);
    is_file_new = 1;
}

void write_to_binary_file(struct TrigPoly p)
{
    FILE *f1 = NULL;
    f1 = fopen("resl_binary.dat", "ab");

    if (is_binary_new == 0)
    {
        fclose(f1);
        fopen("resl_binary.dat", "wb");
    }

    fwrite(&p.alpha, sizeof(double), 1, f1);
    fwrite(&p.a[0], sizeof(double), 1, f1);
    for(int i = 1; i <= p.n; i++){
        fwrite(&p.a[i], sizeof(double), 1, f1);
        fwrite(&p.b[i], sizeof(double), 1, f1);
    }
    fprintf(f1, "\n");
    fclose(f1);
    is_binary_new = 1;
}

void write_res_binary(double res)
{
    FILE *f1 = NULL;
    f1 = fopen("resl_binary.dat", "ab");

    if (is_binary_new == 0)
    {
        fclose(f1);
        fopen("resl_binary.dat", "wb");
    }

    fwrite(&res, sizeof(double), 1, f1);
    fclose(f1);
    is_binary_new = 1;
}

void print_integral_poly(struct TrigPoly p, double C)
{
    printf("%lf", C);
    for (int k = 1; k <= p.n; k++)
    {
        printf(" + (%lf)*cos(%d*x) + (%lf)*sin(%d*x)", p.a[k], k, p.b[k], k);
    }
    printf(" + %lf*x", p.a[0]/2);

    // одразу записуємо результат у файл
    FILE *resl = NULL;
    resl = fopen("resl.txt", "a");
    if (is_file_new == 0)
    {
        fclose(resl);
        fopen("resl.txt", "w");
    }
    fprintf(resl, "%lf ", C);
    for (int k = 1; k <= p.n; k++)
    {
        fprintf(resl, " + (%lf)*cos(%d*x) + (%lf)*sin(%d*x)", p.a[k], k, p.b[k], k);
    }
    fprintf(resl, " + %lf*x", p.a[0]);
    fprintf(resl, "\n");
    fclose(resl);
    is_file_new = 1;

    // одразу записуємо результат у фінарний файл
    FILE *f1 = NULL;
    f1 = fopen("resl_binary.dat", "ab");

    if (is_binary_new == 0)
    {
        fclose(f1);
        fopen("resl_binary.dat", "wb");
    }

    fwrite(&p.alpha, sizeof(double), 1, f1);
    fwrite(&C, sizeof(double), 1, f1);
    fwrite(&p.a[0], sizeof(double), 1, f1);
    for(int i = 1; i <= p.n; i++)
    {
        fwrite(&p.a[i], sizeof(double), 1, f1);
        fwrite(&p.b[i], sizeof(double), 1, f1);
    }
    fprintf(f1, "\n");
    fclose(f1);
    is_binary_new = 1;
}


// Операції над поліномами


double value(struct TrigPoly p, double x)
{
    double v = p.a[0]/2;
    for (int k = 1; k <= p.n; k++)
    {
        v += p.a[k]*cos(k*x) + p.b[k]*sin(k*x);
    }
    return v;
}

struct TrigPoly add_poly(struct TrigPoly p1, struct TrigPoly p2)
{
    struct TrigPoly pp;
    // якщо перший поліном довший або такий самий як другий,
    // то створюємо новий поліном розміру р1, коефіцієнти якого будуть сумою кофефіцієнтів р1 та р2
    if (p1.n >= p2.n)
    {
        pp.n = p1.n;
        pp.a = (double *)malloc((p1.n + 1)* sizeof(double));
        pp.b = (double *)malloc((p1.n + 1)* sizeof(double));
        for (int i = 0; i < p2.n + 1; i++)
        {
            pp.a[i] = p1.a[i] + p2.a[i];
            pp.b[i] = p1.b[i] + p2.b[i];
        }
        for (int i = p2.n + 1; i < p1.n + 1; i++)
        {
            pp.a[i] = p1.a[i];
            pp.b[i] = p1.b[i];
        }
    }

    else
    {
        pp.n = p2.n;
        pp.a = (double *)malloc((p2.n + 1)* sizeof(double));
        pp.b = (double *)malloc((p2.n + 1)* sizeof(double));

        for (int i = 0; i < p1.n + 1; i++)
        {
            pp.a[i] = p1.a[i] + p2.a[i];
            pp.b[i] = p1.b[i] + p2.b[i];
        }
        for (int i = p1.n + 1; i < p2.n + 1; i++)
        {
            pp.a[i] = p2.a[i];
            pp.b[i] = p2.b[i];
        }
    }
    // значення alpha для нового поліному
    if (p1.alpha == p2.alpha)
    {
        pp.alpha = p2.alpha;
    }
    else
    {
        pp.alpha = setAlpha();
    }
    return pp;
    destroy(&pp);
}

struct TrigPoly subtract_poly(struct TrigPoly p1, struct TrigPoly p2)
{
    // все те саме, що й у функції add_poly
    struct TrigPoly pp;
    if (p1.n >= p2.n)
    {
        pp.n = p1.n;
        pp.a = (double *)malloc((p1.n + 1)* sizeof(double));
        pp.b = (double *)malloc((p1.n + 1)* sizeof(double));
        for (int i = 0; i < p2.n + 1; i++)
        {
            pp.a[i] = p1.a[i] - p2.a[i];
            pp.b[i] = p1.b[i] - p2.b[i];
        }
        for (int i = p2.n + 1; i < p1.n + 1; i++)
        {
            pp.a[i] = p1.a[i];
            pp.b[i] = p1.b[i];
        }
    }

    else
    {
        pp.n = p2.n;
        pp.a = (double *)malloc((p2.n + 1)* sizeof(double));
        pp.b = (double *)malloc((p2.n + 1)* sizeof(double));

        for (int i = 0; i < p1.n + 1; i++)
        {
            pp.a[i] = p1.a[i] - p2.a[i];
            pp.b[i] = p1.b[i] - p2.b[i];
        }
        for (int i = p1.n + 1; i < p2.n + 1; i++)
        {
            pp.a[i] = - p2.a[i];
            pp.b[i] = - p2.b[i];
        }
    }

    // значення alpha для нового поліному
    if (p1.alpha == p2.alpha)
    {
        pp.alpha = p2.alpha;
    }
    else
    {
        pp.alpha = setAlpha();
    }
    return pp;
    destroy(&pp);
}

struct TrigPoly derivative(struct TrigPoly p)
{
    // створюємо новий поліном, у якого вільний член = 0
    // коефіцієнти полінома р при синусах стануть коеф. при косинусах з мінусом помножені на коефіцієнт при х
    // коеф. при косинусах стануть рівними коеф. при синусах помножені на коеф. при х
    // це і буде похідна від поліному р

    struct TrigPoly pp;
    pp.n = p.n;
    pp.a = (double *)malloc((pp.n + 1)* sizeof(double));
    pp.b = (double *)malloc((pp.n + 1)* sizeof(double));
    pp.alpha = p.alpha;
    pp.a[0] = 0;
    pp.b[0] = 0;
    for (int k = 0; k < pp.n + 1; k++)
    {
        pp.a[k] = p.b[k]*k;
        pp.b[k] = - p.a[k]*k;
    }
    return pp;
    destroy(&pp);
}

struct TrigPoly integral(struct TrigPoly p, double C)
{
    // аналогічно до похідної, тільки тут вільним членом стане число С,
    // а старий вільний член помножиться на х.
    // це буде враховано у функції print_integral_poly, поки що просто цей вільний член залишимо таким самим
    struct TrigPoly pp;
    pp.n = p.n;
    pp.a = (double *)malloc((pp.n + 1)* sizeof(double));
    pp.b = (double *)malloc((pp.n + 1)* sizeof(double));
    pp.alpha = p.alpha;
    pp.a[0] = p.a[0];
    pp.b[0] = 0;

    for (int k = 1; k <= p.n; k++)
    {
        pp.a[k] = - p.b[k]/k;
        pp.b[k] = p.a[k]/k;
    }
    return pp;
    destroy(&pp);
}

double integrate(struct TrigPoly p, double a, double b)
{
    // рахуємо спочатку невизначений інтеграл (тут замість С я взяв випадкове число, оскільки воно не як не вплине на результат)
    // далі використовуємо функцію value і рахуємо визначений інтеграл за формулою Ньютона-Лейбніца

    struct TrigPoly p1 = p;
    p1 = integral(p, 2);
    return (value(p1, b) + p.alpha*b/2) - (value(p1, a) + p.alpha*a/2);
    destroy(&p1);
}





struct TrigPoly mul_poly(struct TrigPoly p1, struct TrigPoly p2)
{
    // ????
};

struct TrigPoly div_poly(struct TrigPoly p1, struct TrigPoly p2)
{
    // ????
};



void input_text_file(struct TrigPoly *p)
{
    FILE *f = fopen("poly.txt", "rt");
    int len = strlen("poly.txt");
    int t = 0;
    char *s = malloc(100);
    char c;

    while(!feof(f))
    {
        c = fgetc(f);
        if (c == '\n')
        {

            continue;
        }
        s = add_char(s, c);
        printf("%c", c);
    }

    printf("\n");


    fclose(f);
    free(s);
}





