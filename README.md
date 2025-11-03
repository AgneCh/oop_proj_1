# oop_proj_1


# (v0.3)
Šioje versijoje (`v0.3`) buvo atliktas testavimas, siekiant palyginti `std::vector` ir `std::list` veikimo spartą.
Testavimui naudoti tie patys duomenų failai kaip ir `v0.2` versijoje.  
Kiekvienam konteineriui buvo atliekami matavimai su tokiais įrašų kiekiais (1000, 10000, 100000, 1000000, 10000000 įrašų).

## Testavimo aplinka
| Parametras |  Reikšmė                    | 
|------------|-----------------------------|
| CPU        | Intel(R) Core(TM) i7-1065G7 |
| RAM        | 8 GB                        |
| Diskas     | SSD                         |
| OS         | Ubuntu 24.04.3 LTS          |


## Rezultatai

Atsitiksinių studentų sąrašų failų kūrimas (vid.):
| Įrašų kiekis | `std::vector` (s) | `std::list` (s) |
|--------------|-------------------|-----------------|
| 1 000        | 0.0017713         | 0.001936278
| 10 000       | 0.00814588        | 0.0110534
| 100 000      | 0.05982952        | 0.06057134
| 1 000 000    | 0.4506244         | 0.4379546
| 10 000 000   | 4.3473            | 4.343814
![10 000000 įrašų kūrimas su vector](screenshots/image-1.png)
![10 000000 įrašų kūrimas su list](screenshots/image-2.png)


Duomenų nuskaitymas iš failų (vid.):
| Įrašų kiekis | `std::vector` (s) | `std::list` (s) |
|--------------|-------------------|-----------------|
| 1 000        | 0.002358702       | 0.001804468
| 10 000       | 0.01968436        | 0.01750358
| 100 000      | 0.08291886        | 0.078372
| 1 000 000    | 0.6835998         | 0.561991
| 10 000 000   | 6.60041           | 6.604486
![10 000000 duomenų nuskaitymas su vector](screenshots/image.png)
![10 000000 duomenų nuskaitymas su list](screenshots/image-3.png)

Studentų rūšiavimas į dvi kategorijas (vid.):
| Įrašų kiekis | `std::vector` (s) | `std::list` (s) |
|--------------|-------------------|-----------------|
| 1 000        | 0.000294958       | 0.000172689
| 10 000       | 0.002069002       | 0.00192168
| 100 000      | 0.01242656        | 0.01240088
| 1 000 000    | 0.1211802         | 0.10524554
| 10 000 000   | 1.192148          | 1.1188372
![10 000000 įrašų rūšiavimas į dvi kategorijas su vector ](screenshots/image-6.png)
![10 000000 įrašų rūšiavimas į dvi kategorijas su list](screenshots/image-4.png)

Surūšiuotų studentų išvedimas į du naujus failus (vid.):
| Įrašų kiekis | `std::vector` (s) | `std::list` (s) |
|--------------|-------------------|-----------------|
| 1 000        | 0.002195244       | 0.00879666
| 10 000       | 0.0164007         | 0.01603442
| 100 000      | 0.05875878        | 0.07475656
| 1 000 000    | 0.5272746         | 0.6350894
| 10 000 000   | 4.934834          | 5.80888
![10 000000 išvedimas į du naujus failus su vector](screenshots/image-7.png)
![10 000000 išvedimas į du naujus failus su list](screenshots/image-5.png)

# (v0.2)
# (v0.1)
Šiame release programa patobulinta taip, kad vartojas galetų nuskaityti studentų duomenis is txt failo.
Nuskaityti duomenys išvedami į tą pati lentelės pavidalą kaip ir v.pradine versijoje:

|Name    |Surname   |Final grade (mean)  |Final grade (median)  |
|--------|----------|--------------------|----------------------|
|Name1   |Surname1  |8.00                |8.00                  |
...

Studentų duomenys yra rušioujami pagal vardą.

Buvo sėkmingai atidaryti visi testavimo failai:
- studentai10000.txt
- studentai100000.txt 
- studentai1000000.txt


# (v.pradine)
Programa  priema studento vardą ir pavardę, namų darbų tarpinius rezultatus ir egzamino rezultatą, ir iš balų išveda galutinį balą.
Išvedama lentelė su studentų vardais ir galutiniu balu paskaičiuotu pagal varotojo pasirinkimą (Galutinis (Vid.) arba Galutinis (Med.) ar abudu). Galutiniais balais suskaičiuotais pagal formulę:
Galutinis = 0.4 * vidurkis + 0.6 * egzaminas
