/*
 * Copyright (C) 2021 V. Javier Fdez.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <iostream>
#include <string>
#include <iomanip> // Set precision
#include <limits>
#include <tuple>
#include <math.h>  // pow
#include <cstdlib> // EXIT_SUCCESS and EXIT_FAILURE

using namespace std;

// El IMC constituye la medida poblacional más útil del sobrepeso y la obesidad, 
// pues la forma de calcularlo no varía en función del sexo ni de la edad en la 
// población adulta. No obstante, debe considerarse como una guía aproximativa, 
// pues puede no corresponder al mismo grado de gordura en diferentes individuos.
//
// ¿Cómo se mide el IMC?
//
// La fórmula del IMC es el peso en kilógramos dividido por el cuadrado de la 
// altura en metros (kg/m2).
//
// IMC = peso / (altura x altura) = peso / altura^2
// 
// Por ejemplo, para un individuo de 1,75 m de altura y un peso de 72 kg, el IMC 
// será: 72/(1,75x1,75) = 23,5
//
// En el año 2013, investigadores de la Universidad de Oxford desarrollaron una 
// nueva fórmula del IMC, a saber:
//
// IMC (Oxford 2013) = 1,3 x peso / altura^2,5
//
// Por ejemplo, para un individuo de 1,75 m de altura y un peso de 72 kg, el IMC 
// será: 1,3 x 72/1,75^2,5 = 23,1
//
// Se puede ver de inmediato como el IMC es ligeramente inferior.
// Tanto el nuevo IMC, como el antiguo IMC, es solo un número, y ningún número 
// puede capturar la complejidad de nuestros cuerpos y los problemas de salud 
// asociados.
//
// Interpretación del IMC:
// <15.5        Delgadez severa (anorexia severa)	 	
// 15,5 - 17,49 Peso insuficiente (anorexia moderada)	
// 17,5	- 18,49 Ligera falta de peso
// 18,5 - 24,9  Peso ideal (normal)
// 25 - 29,9    Sobrepeso
// 30 - 34,9    Obesidad tipo I
// 35 - 39,9    Obesidad tipo II
// >40          Obesidad tipo III

const float IDEAL_WEIGHT_MIN_BMI = 18.5f;
const float IDEAL_WEIGHT_MAX_BMI = 24.9f;

void clear() {
    #if defined(_WIN32)
        system("cls");
    #elif defined(_linux)
        system("clear");
    #endif
}

void ignoreLine()
{
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

unsigned short int getHeight() {
    while (true) // Loop until user enters a valid input
    {
        cout << "Your height (centimeters): ";
        unsigned short int x;
        cin >> x;

        // Check for failed extraction
        if (cin.fail()) // has a previous extraction failed?
        {
            // yep, so let's handle the failure
            cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
            cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            ignoreLine(); // remove any extraneous input
            return x;
        }
    }
}

unsigned short int getWeight() {
        while (true) // Loop until user enters a valid input
    {
        cout << "Your weight (kilograms): ";
        unsigned short int x;
        cin >> x;

        // Check for failed extraction
        if (cin.fail()) // has a previous extraction failed?
        {
            // yep, so let's handle the failure
            cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
            cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            ignoreLine(); // remove any extraneous input
            return x;
        }
    }
}

float getBMI(unsigned short int height, unsigned short int weight) {
    return 1.3f * static_cast<float>(weight) / pow(static_cast<float>(height) / 100, 2.5f);
}

std::string getSituation(float BMI) {
    if (BMI < 16.0f ) {
        return "Severe thinness (severe anorexia)";
    } else if (BMI >= 16.0f && BMI < 17.0f) {
        return "Insufficient weight (moderate anorexia)";
    } else if (BMI >= 17.0f && BMI < 18.5f) {
        return "Slight underweight";
    } else if (BMI >= 18.5f && BMI < 25.0f) {
        return "Ideal weight (normal)";
    } else if (BMI >= 25.0f && BMI < 30.0f) {
        return "Overweight";
    } else if (BMI >= 30.0f && BMI < 35.0f) {
        return "Obesity type I";
    } else if (BMI >= 35.0f && BMI < 40.0f) {
        return "Obesity type II";
    } else if (BMI >= 40.0f && BMI <= 45.0f) {
        return "Obesity type III";
    } else {
        return "Hypermorbid Obesity type IV";
    }
}

std::tuple<float, float> getIdealWeight(unsigned short int height) {
    float minWeight = IDEAL_WEIGHT_MIN_BMI * pow(static_cast<float>(height) / 100, 2.5f) / 1.3f;
    float maxWeight = IDEAL_WEIGHT_MAX_BMI * pow(static_cast<float>(height) / 100, 2.5f) / 1.3f;

    return {minWeight, maxWeight};
}

int main() {
    cout << fixed << setprecision(2);
    clear();
    
    unsigned short int height { getHeight() };
    unsigned short int weight { getWeight() };
    
    float BMI = getBMI(height, weight);
    
    cout << endl;
    cout << "Your Body Mass Index (BMI) is " << BMI  << "(*)" << endl;
    cout << "You have " << getSituation(BMI) << endl;

    auto [minIdealWeight, maxIdealWeight] = getIdealWeight(height);
    
    cout << "Your ideal weight is between " << minIdealWeight << " and " << maxIdealWeight << " kg." << endl;
    cout << endl;
    cout << "(*) BMI (Oxford 2013) = 1,3 x weight / height ^ 2,5" << endl;
    cout << "https://people.maths.ox.ac.uk/trefethen/bmi.html" << endl;
    return EXIT_SUCCESS;    
}