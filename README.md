# Laboratorio 07

### Estudiante: Frank Roger Salas Ticona        CCOMP 3-1

Compilador utilizado g++ (GCC) 11.1.0.

Sistema Operativo: Archlinux 5.15.2-zen1-1-zen.

## Uso

> Compilando con g++ con libreria NTL.
        
        g++ -g -O2 -std=c++11 -pthread -march=native millerrabin.cpp -o output -lntl -lgmp -lm

> Si se usa Windows se debe agregar la extension \*.exe al momento de compilar.


> Ejecutando el programa.

        ./output
        # Si se usa Windows reemplazar el '/' con '\'.

> El programa mostrará los resultados correspondientes.

## Explicación de Miller Rabin

Miller Rabin es un algoritmo para hallar primos "probables".

Obetenemos u con,

        ZZ u = n - 1;
        while (u % 2 == 0)
            u /= 2;
        return u;

Si u es par devolvemos falso,
Iteramos las veces indicadas, haciendo la funcion witness(ZZ, ZZ).

        ZZ x = powmod(1 + NTL::RandomBnd(n - 2), u, n);
        if (x == 1 || x == n - 1)
            return false;
        else {
            for (ZZ i = u; i < n; i *= 2) {
                x = powmod(x, ZZ(2), n);
                if (x == n - 1)
                    return false;
            }
            return true;
        }

## Explicación de Generate Prime

Generamos un numero el cual posea la cantidad de bits indicada - 1.
Y hacemos la operación binaria |, con un numero cuyos bits más y menos significativos sean 1.
De esta manera el numero primo sera de la cantidad de bits indicada y sera impar.

## Nota

Si bien el trabajo esta terminado, el algoritmo de generación de claves esta modificado para p = 3 y q = 11. Se debe de descomentar una linea en el rsa.cpp para generar primos en base a un número de bits y comentar la que asigna p = 3 y q = 11.
