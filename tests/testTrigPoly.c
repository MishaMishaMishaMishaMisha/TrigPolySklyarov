#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <Windows.h>
#include "../headers/TrigPolySklyarov.h"
//#include "TrigPolySklyarov.h"
int main()
{
    SetConsoleCP(1251);       // відображення в консолі
    SetConsoleOutputCP(1251); // російських літер
    struct TrigPoly p, p1, p_res;
    double a, b, C, ress; //  а і b - межі інтегрування у визначеному інтегр, С - використовується у невизначеному інтегралі

    printf("Весь результат зберігається у файлі resl.txt та бінарному файлі resl_binary.dat\n");
    printf("Тест 1. Поліноми вводяться як таблиця через пробіли (перше число - alpha, друге - вільний член, всі інші - коеф.)\n");
    string_to_poly(&p, "33 -1 5.034 0 3 4");
    string_to_poly(&p1, "33 1.4 -17 3 1.43 0 -56.743 5");
    printf("Перший поліном\n");
    printf("введений рядок: 2.56 -1 5.034 0 3 4\n");
    printf("отриманий поліном: ");
    print_poly(p);
    printf("\n");
    printf("Другий поліном\n");
    printf("введений рядок: 33 1.4 -17 3 1.43 0 -56.743 5\n");
    printf("отриманий поліном: ");
    print_poly(p1);
    printf("\n");

    C = 5;
    a = -4;
    b = 7;

    printf("\n");
    ress = value(p, p.alpha);
    printf("значення першого поліному в точці: %lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    ress = value(p1, p1.alpha);
    printf("значення другого поліному в точці: %lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    printf("сума двох поліномів: ");
    p_res = add_poly(p, p1);
    print_poly(p_res);
    printf("\n");
    write_poly_to_file(p_res);
    write_to_binary_file(p_res);

    printf("різниця двох поліномів: ");
    p_res = subtract_poly(p, p1);
    print_poly(p_res);
    printf("\n");
    write_poly_to_file(p_res);
    write_to_binary_file(p_res);

    printf("функції множення і ділення двох поліномів не реалізовані!!! \n");

    printf("похідна від першого поліному: ");
    print_poly(derivative(p));
    printf("\n");
    write_poly_to_file(derivative(p));
    write_to_binary_file(derivative(p));

    printf("похідна від другого поліному: ");
    print_poly(derivative(p1));
    printf("\n");
    write_poly_to_file(derivative(p1));
    write_to_binary_file(derivative(p1));

    printf("невизначений інтеграл від першого поліному: ");
    p_res = integral(p, C);
    print_integral_poly(p_res, C);
    printf("\n");

    printf("невизначений інтеграл від другого поліному: ");
    p_res = integral(p1, C);
    print_integral_poly(p_res, C);
    printf("\n");

    printf("визначений інтеграл від першого поліному: ");
    ress = integrate(p, a, b);
    printf("%lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    printf("визначений інтеграл від другого поліному: ");
    ress = integrate(p1, a, b);
    printf("%lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    destroy(&p);
    destroy(&p1);


    printf("\n");
    printf("\n");
    printf("\n");


    printf("Тест 2. Поліноми вводяться як рядки довільної довжини\n");
    string_to_poly(&p, "34.5^-34^3.34^0^23.551^-8");
    string_to_poly(&p1, "34.5^0^98.334^6");
    printf("Перший поліном\n");
    printf("введений рядок: 34.5^-34^3.34^0^23.551^-8\n");
    printf("отриманий поліном: ");
    print_poly(p);
    printf("\n");
    printf("Другий поліном\n");
    printf("введений рядок: 34.5^0^98.334^6\n");
    printf("отриманий поліном: ");
    print_poly(p1);
    printf("\n");

    C = -12.5;
    a = -43.123;
    b = 35.56;

    printf("\n");
    ress = value(p, p.alpha);
    printf("значення першого поліному в точці: %lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    ress = value(p1, p1.alpha);
    printf("значення другого поліному в точці: %lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    printf("сума двох поліномів: ");
    p_res = add_poly(p, p1);
    print_poly(p_res);
    printf("\n");
    write_poly_to_file(p_res);
    write_to_binary_file(p_res);

    printf("різниця двох поліномів: ");
    p_res = subtract_poly(p, p1);
    print_poly(p_res);
    printf("\n");
    write_poly_to_file(p_res);
    write_to_binary_file(p_res);

    printf("функції множення і ділення двох поліномів не реалізовані!!! \n");

    printf("похідна від першого поліному: ");
    print_poly(derivative(p));
    printf("\n");
    write_poly_to_file(derivative(p));
    write_to_binary_file(derivative(p));

    printf("похідна від другого поліному: ");
    print_poly(derivative(p1));
    printf("\n");
    write_poly_to_file(derivative(p1));
    write_to_binary_file(derivative(p1));

    printf("невизначений інтеграл від першого поліному: ");
    p_res = integral(p, C);
    print_integral_poly(p_res, C);
    printf("\n");

    printf("невизначений інтеграл від другого поліному: ");
    p_res = integral(p1, C);
    print_integral_poly(p_res, C);
    printf("\n");

    printf("визначений інтеграл від першого поліному: ");
    ress = integrate(p, a, b);
    printf("%lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    printf("визначений інтеграл від другого поліному: ");
    ress = integrate(p1, a, b);
    printf("%lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    destroy(&p);
    destroy(&p1);


    printf("\n");
    printf("\n");
    printf("\n");


    printf("Тест 3. Користувач сам вводить поліноми по коефіцієнтам через scanf\n");
    printf("Перший поліном\n");
    input_poly(&p);
    printf("отриманий поліном: ");
    print_poly(p);
    printf("\n");
    printf("Другий поліном\n");
    input_poly(&p1);
    printf("отриманий поліном: ");
    print_poly(p1);
    printf("\n");

    printf("Значення C = ");
    scanf("%lf", &C);
    printf("Межі інтегрування:\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);

    printf("\n");
    ress = value(p, p.alpha);
    printf("значення першого поліному в точці: %lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    ress = value(p1, p1.alpha);
    printf("значення другого поліному в точці х: %lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    printf("сума двох поліномів: ");
    p_res = add_poly(p, p1);
    print_poly(p_res);
    printf("\n");
    write_poly_to_file(p_res);
    write_to_binary_file(p_res);

    printf("різниця двох поліномів: ");
    p_res = subtract_poly(p, p1);
    print_poly(p_res);
    printf("\n");
    write_poly_to_file(p_res);
    write_to_binary_file(p_res);

    printf("функції множення і ділення двох поліномів не реалізовані!!! \n");

    printf("похідна від першого поліному: ");
    print_poly(derivative(p));
    printf("\n");
    write_poly_to_file(derivative(p));
    write_to_binary_file(derivative(p));

    printf("похідна від другого поліному: ");
    print_poly(derivative(p1));
    printf("\n");
    write_poly_to_file(derivative(p1));
    write_to_binary_file(derivative(p1));

    printf("невизначений інтеграл від першого поліному: ");
    p_res = integral(p, C);
    print_integral_poly(p_res, C);
    printf("\n");

    printf("невизначений інтеграл від другого поліному: ");
    p_res = integral(p1, C);
    print_integral_poly(p_res, C);
    printf("\n");

    printf("визначений інтеграл від першого поліному: ");
    ress = integrate(p, a, b);
    printf("%lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    printf("визначений інтеграл від другого поліному: ");
    ress = integrate(p1, a, b);
    printf("%lf", ress);
    printf("\n");
    write_res_to_file(ress);
    write_res_binary(ress);

    destroy(&p);
    destroy(&p1);
}

